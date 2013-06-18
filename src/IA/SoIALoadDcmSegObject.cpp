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

/* author Jie Zheng */

#include "SoIALoadDcmSegObject.h"

const float EPSILON = 1e-6;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoIALoadDcmSegObject );

SoIALoadDcmSegObject::SoIALoadDcmSegObject(void)
{
	SO_ENGINE_CONSTRUCTOR( SoIALoadDcmSegObject );

	// Inputs
	SO_ENGINE_ADD_INPUT( inputDcmSeg, ("") );
	SO_ENGINE_ADD_INPUT( process, () );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( inputVolume, SoXipSFDataImage );

	mXipInputImage = 0;
}

void SoIALoadDcmSegObject::initClass()
{
	SO_ENGINE_INIT_CLASS( SoIALoadDcmSegObject, SoEngine, "SoEngine" );
}

SoIALoadDcmSegObject::~SoIALoadDcmSegObject(void)
{
	clearDataImages();
}

void SoIALoadDcmSegObject::inputChanged (SoField* whichField)
{
	if (whichField == &process)
	{
		loadVolume();
	}
}

void SoIALoadDcmSegObject::evaluate()
{	
	SO_ENGINE_OUTPUT( inputVolume, SoXipSFDataImage, setValue(mXipInputImage) );	
}

void SoIALoadDcmSegObject::clearDataImages()
{
	if( mXipInputImage )
	{
		mXipInputImage->unref();
		mXipInputImage = 0;
	}
}

void SoIALoadDcmSegObject::loadVolume()
{
	SbString inputSeg = inputDcmSeg.getValue();

	if (inputSeg.getLength() <= 0)
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

	float _input_imgPosition[3];
	float _input_imgOrientation[6];
	int	  _input_imgDimension[3];
	float _input_imgSpacing[3];
	getPositionItems(_input_dataset, _input_imgPosition, _input_imgOrientation, _input_imgDimension, _input_imgSpacing);

	createXipDataImage(&mXipInputImage, _input_imgPosition, _input_imgOrientation, _input_imgDimension, _input_imgSpacing);
	updateXipDataImage(mXipInputImage, _input_dataset, _input_imgPosition, _input_imgDimension, _input_imgSpacing);
}

void SoIALoadDcmSegObject::createXipDataImage(SoXipDataImage **mXipImage, float imgPosition[3], float imgOrientation[6], int imgDimension[3], float imgSpacing[3])
{
	SbXipImageDimensions volDimensions;
	volDimensions[0] = imgDimension[0];
	volDimensions[1] = imgDimension[1];
	volDimensions[2] = imgDimension[2];

//	SbMatrix volModelMatrix = getModelMatrixFromDICOM(dataset);
	SbVec3f dir_col(imgOrientation[0], imgOrientation[1], imgOrientation[2]);
	SbVec3f dir_row(imgOrientation[3], imgOrientation[4], imgOrientation[5]);
	SbVec3f dir_nor = dir_col.cross(dir_row);

	SbMatrix volModelMatrix;
	volModelMatrix[0][0] = imgDimension[0]*imgSpacing[0]*dir_col[0];
	volModelMatrix[0][1] = imgDimension[0]*imgSpacing[0]*dir_col[1];
	volModelMatrix[0][2] = imgDimension[0]*imgSpacing[0]*dir_col[2];
	volModelMatrix[0][3] = 0;

	volModelMatrix[1][0] = imgDimension[1]*imgSpacing[1]*dir_row[0];
	volModelMatrix[1][1] = imgDimension[1]*imgSpacing[1]*dir_row[1];
	volModelMatrix[1][2] = imgDimension[1]*imgSpacing[1]*dir_row[2];
	volModelMatrix[1][3] = 0;

	volModelMatrix[2][0] = imgDimension[2]*imgSpacing[2]*dir_nor[0];
	volModelMatrix[2][1] = imgDimension[2]*imgSpacing[2]*dir_nor[1];
	volModelMatrix[2][2] = imgDimension[2]*imgSpacing[2]*dir_nor[2];
	volModelMatrix[2][3] = 0;

	volModelMatrix[3][0] = imgPosition[0];
	volModelMatrix[3][1] = imgPosition[1];
	volModelMatrix[3][2] = imgPosition[2];
	volModelMatrix[3][3] = 1.0;

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

void SoIALoadDcmSegObject::updateXipDataImage(SoXipDataImage* mXipImage, DcmDataset *dataset, float imgPosition[3], int imgDimension[3], float imgSpacing[3])
{
	SbXipImage* outputImage = mXipImage->get();
	BYTE* outImagePtr = (BYTE*) outputImage->refBufferPtr();

	int _slice_Size = imgDimension[0]*imgDimension[1];

	const Uint8 *pixelData = NULL; 
	unsigned long count = 0; 
	if (dataset->findAndGetUint8Array(DCM_PixelData, pixelData, &count).good()) 
	{ 
		for (int i = 0; i < imgDimension[2]; i++)
		{
			BYTE *_data = outImagePtr + i*_slice_Size;
			const Uint8 *_image = pixelData + i*_slice_Size;

			memcpy(_data, _image, sizeof(BYTE)*_slice_Size);
		}
	}

	outputImage->unrefBufferPtr();
}

void SoIALoadDcmSegObject::getPositionItems(DcmDataset *dataSet, float imgPosition[3], float imgOrientation[6], int imgDimension[3], float imgSpacing[3])
{
	DcmStack stack;
	DcmElement *element;

	unsigned short height, width;

	//depth
	OFString buffer;
	dataSet->findAndGetOFString(DCM_NumberOfFrames, buffer);
	imgDimension[2] = atoi(buffer.c_str());

	// column
	dataSet->findAndGetUint16(DCM_Columns, width);
	imgDimension[0] = width;

	// row
	dataSet->findAndGetUint16(DCM_Rows, height);
	imgDimension[1] = height;

	// slice thickness
	dataSet->findAndGetOFString(DCM_SliceThickness, buffer);
	imgSpacing[2] = atof(buffer.c_str());

	// pixel spacing
	dataSet->findAndGetOFStringArray(DCM_PixelSpacing, buffer);
	sscanf(buffer.c_str(), "%f\\%f", &imgSpacing[0], &imgSpacing[1]);

	// patient position
	dataSet->findAndGetOFStringArray(DCM_ImagePositionPatient, buffer);
	sscanf(buffer.c_str(), "%f\\%f\\%f", &imgPosition[0], &imgPosition[1], &imgPosition[2]);

	// patient position
	dataSet->findAndGetOFStringArray(DCM_ImageOrientationPatient, buffer);
	sscanf(buffer.c_str(), "%f\\%f\\%f\\%f\\%f\\%f", &imgOrientation[0], &imgOrientation[1], &imgOrientation[2], &imgOrientation[3], &imgOrientation[4], &imgOrientation[5]);
}
