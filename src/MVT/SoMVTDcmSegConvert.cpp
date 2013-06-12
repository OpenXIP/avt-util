/*
Copyright (c) 2010, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "SoMVTDcmSegConvert.h"

const float EPSILON = 1e-6;

/* author Jie Zheng */

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoMVTDcmSegConvert );

SoMVTDcmSegConvert::SoMVTDcmSegConvert(void)
{
	SO_ENGINE_CONSTRUCTOR( SoMVTDcmSegConvert );

	// Inputs
	SO_ENGINE_ADD_INPUT( inputDcmSeg, ("") );
	SO_ENGINE_ADD_INPUT( refDcmSeg, ("") );
	SO_ENGINE_ADD_INPUT( process, () );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( inputVolume, SoXipSFDataImage );
	SO_ENGINE_ADD_OUTPUT( refVolume, SoXipSFDataImage );

	mXipInputImage = 0;
	mXipRefImage = 0;
}

void 
SoMVTDcmSegConvert::initClass()
{
	SO_ENGINE_INIT_CLASS( SoMVTDcmSegConvert, SoEngine, "SoEngine" );
}

SoMVTDcmSegConvert::~SoMVTDcmSegConvert(void)
{
	clearDataImages();
}

void SoMVTDcmSegConvert::inputChanged (SoField* whichField)
{
	if (whichField == &process)
	{
		resampleVolume();
	}
}

void
SoMVTDcmSegConvert::evaluate()
{	
	SO_ENGINE_OUTPUT( inputVolume, SoXipSFDataImage, setValue(mXipInputImage) );	
	SO_ENGINE_OUTPUT( refVolume, SoXipSFDataImage, setValue(mXipRefImage) );	
}

void SoMVTDcmSegConvert::clearDataImages()
{
	if( mXipInputImage )
	{
		mXipInputImage->unref();
		mXipInputImage = 0;
	}

	if( mXipRefImage )
	{
		mXipRefImage->unref();
		mXipRefImage = 0;
	}
}

void SoMVTDcmSegConvert::resampleVolume()
{
	SbString inputSeg = inputDcmSeg.getValue();
	SbString refSeg = refDcmSeg.getValue();

	if (inputSeg.getLength() <= 0 || refSeg.getLength() <= 0)
	{
		clearDataImages();
		return;
	}

	DcmFileFormat _input_fileformat;
	OFCondition status = _input_fileformat.loadFile(inputSeg.getString());
	if (!status.good())
	{
		clearDataImages();
		return;
	}
	DcmDataset *_input_dataset = _input_fileformat.getDataset();

	DcmFileFormat _ref_fileformat;
	status = _ref_fileformat.loadFile(refSeg.getString());
	if (!status.good())
	{
		clearDataImages();
		return;
	}
	DcmDataset *_ref_dataset = _ref_fileformat.getDataset();

	if (!validateDataImages(_input_dataset, _ref_dataset))
	{
		clearDataImages();
		return;
	}

	double _input_imgPosition[3];
	int	  _input_imgDimension[3];
	double _input_imgSpacing[3];
	getPositionItems(_input_dataset, _input_imgPosition, _input_imgDimension, _input_imgSpacing);
	double _input_endLocation = _input_imgPosition[2] + _input_imgDimension[2]*_input_imgSpacing[2];

	double _ref_imgPosition[3];
	int	  _ref_imgDimension[3];
	double _ref_imgSpacing[3];
	getPositionItems(_ref_dataset, _ref_imgPosition, _ref_imgDimension, _ref_imgSpacing);
	double _ref_endLocation = _ref_imgPosition[2] + _ref_imgDimension[2]*_ref_imgSpacing[2];

	//calculate the maximum border of the output volume
	double _begin_SlicePos = _input_imgPosition[2];
	if ((_begin_SlicePos - _ref_imgPosition[2]) > EPSILON)
		_begin_SlicePos = _ref_imgPosition[2];

	double _end_SlicePos = _input_endLocation;
	if ((_end_SlicePos - _ref_endLocation) < EPSILON)
		_end_SlicePos = _ref_endLocation;

	int bufDimension[3];
	bufDimension[0] = _input_imgDimension[0];
	bufDimension[1] = _input_imgDimension[1];
	bufDimension[2] = (_end_SlicePos-_begin_SlicePos)/_input_imgSpacing[2] + 1;
	
	char buffer[64];
	sprintf(buffer, "%lf\\%lf\\%lf", _input_imgPosition[0], _input_imgPosition[1], _begin_SlicePos);
	_input_dataset->remove(DCM_ImagePositionPatient);
	_input_dataset->putAndInsertString(DCM_ImagePositionPatient, buffer);
	_input_dataset->remove(DCM_NumberOfFrames);
	_input_dataset->putAndInsertUint16(DCM_NumberOfFrames, bufDimension[2]);

	_ref_dataset->remove(DCM_ImagePositionPatient);
	_ref_dataset->putAndInsertString(DCM_ImagePositionPatient, buffer);
	_ref_dataset->remove(DCM_NumberOfFrames);
	_ref_dataset->putAndInsertUint16(DCM_NumberOfFrames, bufDimension[2]);

	createXipDataImage(&mXipInputImage, _input_dataset, bufDimension);
	updateXipDataImage(mXipInputImage, _input_dataset, _begin_SlicePos, _input_imgPosition, _input_imgDimension, _input_imgSpacing);

	createXipDataImage(&mXipRefImage, _ref_dataset, bufDimension);
	updateXipDataImage(mXipRefImage, _ref_dataset, _begin_SlicePos, _ref_imgPosition, _ref_imgDimension, _ref_imgSpacing);
}

void SoMVTDcmSegConvert::createXipDataImage(SoXipDataImage **mXipImage, DcmDataset *dataset, int bufDimension[3])
{
	SbXipImageDimensions volDimensions;
	volDimensions[0] = bufDimension[0];
	volDimensions[1] = bufDimension[1];
	volDimensions[2] = bufDimension[2];

	SbMatrix volModelMatrix = getModelMatrixFromDICOM(dataset);

	if ( (*mXipImage) && (*mXipImage)->get() )
	{
		if ( ((*mXipImage)->get()->getDimStored()   != volDimensions) ||
			((*mXipImage)->get()->getModelMatrix() != volModelMatrix) )
		{
			(*mXipImage)->unref();
			(*mXipImage) = 0;
		}	
	}	

	if ( !(*mXipImage) )
	{			
		(*mXipImage) = new SoXipDataImage();
		(*mXipImage)->ref();

		SbXipImage* ouputImage = new SbXipImage( volDimensions,
			SbXipImage::UNSIGNED_BYTE,
			8,
			1,								   
			SbXipImage::SEPARATE,
			SbXipImage::LUMINANCE,
			volModelMatrix);	

		ouputImage->zero();
		(*mXipImage)->set( ouputImage );	
	}
}

void SoMVTDcmSegConvert::updateXipDataImage(SoXipDataImage* mXipImage, DcmDataset *dataset, double _begin_SlicePos, double imgPosition[3], int imgDimension[3], double imgSpacing[3])
{
	SbXipImage* outputImage = mXipImage->get();
	BYTE* outImagePtr = (BYTE*) outputImage->refBufferPtr();

	int _slice_Size = imgDimension[0]*imgDimension[1];

	const Uint8 *pixelData = NULL; 
	unsigned long count = 0; 
	if (dataset->findAndGetUint8Array(DCM_PixelData, pixelData, &count).good()) 
	{ 
		int iBegin = (fabs(_begin_SlicePos-imgPosition[2]))/imgSpacing[2];
		for (int i = 0; i < imgDimension[2]; i++)
		{
			BYTE *_data = outImagePtr + (i+iBegin)*_slice_Size;
			const Uint8 *_image = pixelData + i*_slice_Size;

			memcpy(_data, _image, sizeof(BYTE)*_slice_Size);
		}
	}

	outputImage->unrefBufferPtr();
}

void SoMVTDcmSegConvert::getPositionItems(DcmDataset *dataSet, double imgPosition[3], int imgDimension[3], double imgSpacing[3])
{
	DcmStack stack;
	DcmElement *element;

	unsigned short height, width;

	// column
	dataSet->findAndGetUint16(DCM_Columns, width);
	imgDimension[0] = width;

	// row
	dataSet->findAndGetUint16(DCM_Rows, height);
	imgDimension[1] = height;

	imgDimension[2] = 1;
	if (dataSet->search(DCM_NumberOfFrames, stack) == EC_Normal)
	{
		element = OFstatic_cast(DcmElement *, stack.top());

		if (element->ident() == EVR_IS)
		{
			OFString value;
			element->getOFString(value, 0);
			imgDimension[2] = ::atoi(value.c_str());
		}
	}

	// slice thickness
	if ( dataSet->search(DCM_SliceThickness, stack) == EC_Normal )
	{
		element = OFstatic_cast(DcmElement *, stack.top());

		if (element->ident() == EVR_DS)
			element->getFloat64(imgSpacing[2]);
	}

	// pixel spacing
	if ( dataSet->search(DCM_PixelSpacing, stack) == EC_Normal )
	{
		element = OFstatic_cast(DcmElement *, stack.top());

		if (element->ident() == EVR_DS)
		{
			for (int i = 0; i < element->getVM(); i++)
				element->getFloat64(imgSpacing[i], i);
		}
	}

	// patient position
	if ( dataSet->search(DCM_ImagePositionPatient, stack) == EC_Normal )
	{
		element = OFstatic_cast(DcmElement *, stack.top());

		if (element->ident() == EVR_DS)
		{
			for (int i = 0; i < element->getVM(); i++)
				element->getFloat64(imgPosition[i], i);
		}
	}
}

bool SoMVTDcmSegConvert::validateDataImages(DcmDataset *dataset0, DcmDataset *dataset1)
{
	OFString referenceUID0;
	dataset0->findAndGetOFString(DCM_FrameOfReferenceUID, referenceUID0);

	OFString referenceUID1;
	dataset1->findAndGetOFString(DCM_FrameOfReferenceUID, referenceUID1);

	if (referenceUID0.compare(referenceUID1) == 0)
		return true;

	return false;
}
