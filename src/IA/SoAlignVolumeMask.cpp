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

#include "SoAlignVolumeMask.h"

const float EPSILON = 1e-6;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoAlignVolumeMask );

SoAlignVolumeMask::SoAlignVolumeMask(void)
{
	SO_ENGINE_CONSTRUCTOR( SoAlignVolumeMask );

	// Inputs
	SO_ENGINE_ADD_INPUT( inputMask, (NULL) );
	SO_ENGINE_ADD_INPUT( refMask, (NULL) );
	SO_ENGINE_ADD_INPUT( process, () );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( inputVolume, SoXipSFDataImage );
	SO_ENGINE_ADD_OUTPUT( refVolume, SoXipSFDataImage );

	mXipInputImage = 0;
	mXipRefImage = 0;
}

void 
SoAlignVolumeMask::initClass()
{
	SO_ENGINE_INIT_CLASS( SoAlignVolumeMask, SoEngine, "SoEngine" );
}

SoAlignVolumeMask::~SoAlignVolumeMask(void)
{
	clearDataImages();
}

void SoAlignVolumeMask::inputChanged (SoField* whichField)
{
	if (whichField == &process)
	{
		resampleVolume();
		SO_ENGINE_OUTPUT( inputVolume, SoXipSFDataImage, setValue(mXipInputImage) );	
		SO_ENGINE_OUTPUT( refVolume, SoXipSFDataImage, setValue(mXipRefImage) );	
	}
}

void
SoAlignVolumeMask::evaluate()
{	
}

void SoAlignVolumeMask::clearDataImages()
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

void SoAlignVolumeMask::resampleVolume()
{
	SoXipDataImage* maskInput = inputMask.getValue();
	if (!maskInput || !maskInput->get())
	{
		clearDataImages();
		return;
	}

	SoXipDataImage* maskRef = refMask.getValue();
	if (!maskRef || !maskRef->get())
	{
		clearDataImages();
		return;
	}

	SbXipImage *input = maskInput->get();
	SbXipImage *ref = maskRef->get();

	double _input_imgPosition[3];
	int	  _input_imgDimension[3];
	double _input_imgSpacing[3];
	getPositionItems(input, _input_imgPosition, _input_imgDimension, _input_imgSpacing);
	double _input_end_x = _input_imgPosition[0] + _input_imgDimension[0]*_input_imgSpacing[0];
	double _input_end_y = _input_imgPosition[1] + _input_imgDimension[1]*_input_imgSpacing[1];
	double _input_endLocation = _input_imgPosition[2] + _input_imgDimension[2]*_input_imgSpacing[2];

	double _ref_imgPosition[3];
	int	  _ref_imgDimension[3];
	double _ref_imgSpacing[3];
	getPositionItems(ref, _ref_imgPosition, _ref_imgDimension, _ref_imgSpacing);
	double _ref_end_x = _ref_imgPosition[0] + _ref_imgDimension[0]*_ref_imgSpacing[0];
	double _ref_end_y = _ref_imgPosition[1] + _ref_imgDimension[1]*_ref_imgSpacing[1];
	double _ref_endLocation = _ref_imgPosition[2] + _ref_imgDimension[2]*_ref_imgSpacing[2];

	double _begin_Pos[3];
	//calculate the maximum border of the output volume
	//x - direction
	double _begin_x = _input_imgPosition[0];
	if ((_begin_x - _ref_imgPosition[0]) > EPSILON)
		_begin_x = _ref_imgPosition[0];

	double _end_x = _input_end_x;
	if ((_end_x - _ref_end_x) < EPSILON)
		_end_x = _ref_end_x;

	//y - direction
	double _begin_y = _input_imgPosition[1];
	if ((_begin_y - _ref_imgPosition[1]) > EPSILON)
		_begin_y = _ref_imgPosition[1];

	double _end_y = _input_end_y;
	if ((_end_y - _ref_end_y) < EPSILON)
		_end_y = _ref_end_y;

	//z - direction
	double _begin_SlicePos = _input_imgPosition[2];
	if ((_begin_SlicePos - _ref_imgPosition[2]) > EPSILON)
		_begin_SlicePos = _ref_imgPosition[2];

	double _end_SlicePos = _input_endLocation;
	if ((_end_SlicePos - _ref_endLocation) < EPSILON)
		_end_SlicePos = _ref_endLocation;

	_begin_Pos[0] = _begin_x;
	_begin_Pos[1] = _begin_y;
	_begin_Pos[2] = _begin_SlicePos;

	int bufDimension[3];
	bufDimension[0] = (_end_x-_begin_x)/_input_imgSpacing[0] + 1;
	bufDimension[1] = (_end_y-_begin_y)/_input_imgSpacing[1] + 1;
	bufDimension[2] = (_end_SlicePos-_begin_SlicePos)/_input_imgSpacing[2] + 1;

	SbMatrix modelMatrix = SbMatrix::identity();
	SbVec3f vec0(modelMatrix[0][0], modelMatrix[0][1], modelMatrix[0][2]);
	resizeVec(vec0, bufDimension[0] * _input_imgSpacing[0]);

	modelMatrix[0][0] = vec0[0];
	modelMatrix[0][1] = vec0[1];
	modelMatrix[0][2] = vec0[2];

	SbVec3f vec1(modelMatrix[1][0], modelMatrix[1][1], modelMatrix[1][2]);
	resizeVec(vec1, bufDimension[1] * _input_imgSpacing[1]);

	modelMatrix[1][0] = vec1[0];
	modelMatrix[1][1] = vec1[1];
	modelMatrix[1][2] = vec1[2];

	SbVec3f vec2(modelMatrix[2][0], modelMatrix[2][1], modelMatrix[2][2]);
	resizeVec(vec2, bufDimension[2] * _input_imgSpacing[2]);

	modelMatrix[2][0] = vec2[0];
	modelMatrix[2][1] = vec2[1];
	modelMatrix[2][2] = vec2[2];

	modelMatrix[3][0] = _begin_x;
	modelMatrix[3][1] = _begin_y;
	modelMatrix[3][2] = _begin_SlicePos;

	createXipDataImage(&mXipInputImage, modelMatrix, bufDimension);
	updateXipDataImage(mXipInputImage, input, _begin_Pos, bufDimension, _input_imgPosition, _input_imgDimension, _input_imgSpacing);

	createXipDataImage(&mXipRefImage, modelMatrix, bufDimension);
	updateXipDataImage(mXipRefImage, ref, _begin_Pos, bufDimension, _ref_imgPosition, _ref_imgDimension, _ref_imgSpacing);
}

void SoAlignVolumeMask::createXipDataImage(SoXipDataImage **mXipImage, SbMatrix &volModelMatrix, int bufDimension[3])
{
	SbXipImageDimensions volDimensions;
	volDimensions[0] = bufDimension[0];
	volDimensions[1] = bufDimension[1];
	volDimensions[2] = bufDimension[2];

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

void SoAlignVolumeMask::updateXipDataImage(SoXipDataImage* mXipImage, SbXipImage *image, double _begin_Pos[3], int bufDimension[3], double imgPosition[3], int imgDimension[3], double imgSpacing[3])
{
	SbXipImage* outputImage = mXipImage->get();
	BYTE* outImagePtr = (BYTE*) outputImage->refBufferPtr();

	int _slice_Size = bufDimension[0]*bufDimension[1];
	int _image_Size = imgDimension[0]*imgDimension[1];

	int offset_x = (fabs(_begin_Pos[0] - imgPosition[0])) / imgSpacing[0];
	int offset_y = (fabs(_begin_Pos[1] - imgPosition[1])) / imgSpacing[1];

	BYTE *pixelData = (BYTE*) image->refBufferPtr(); 
	unsigned long count = 0; 

	int iBegin = (fabs(_begin_Pos[2]-imgPosition[2]))/imgSpacing[2];
	for (int i = 0; i < imgDimension[2]; i++)
	{
		BYTE *_data = outImagePtr + (i+iBegin)*_slice_Size;
		BYTE *_image = pixelData + i*_image_Size;

		for (int p = 0; p < imgDimension[1]; p++)
		{
			for (int q = 0; q < imgDimension[0]; q++)
			{
				_data[(offset_y+p)*bufDimension[0]+offset_x+q] = _image[p*imgDimension[0]+q];
			}
		}
	}

	image->unrefBufferPtr();
	outputImage->unrefBufferPtr();
}

void SoAlignVolumeMask::getPositionItems(SbXipImage *image, double imgPosition[3], int imgDimension[3], double imgSpacing[3])
{
	SbMatrix mat = image->getModelMatrix();
	SbXipImageDimensions dim = image->getDimStored();

	imgPosition[0] = mat[3][0];
	imgPosition[1] = mat[3][1];
	imgPosition[2] = mat[3][2];

	imgDimension[0] = dim[0];
	imgDimension[1] = dim[1];
	imgDimension[2] = dim[2];

	SbVec3f col(mat[0][0], mat[0][1], mat[0][2]);
	imgSpacing[0] = col.length() / (float)dim[0];

	SbVec3f row(mat[1][0], mat[1][1], mat[1][2]);
	imgSpacing[1] = row.length() / (float)dim[1];

	SbVec3f nor(mat[2][0], mat[2][1], mat[2][2]);
	imgSpacing[2] = nor.length() / (float)dim[2];
}

void SoAlignVolumeMask::resizeVec(SbVec3f &vec, float len)
{
	float factor = len / vec.length();
	vec *= factor;
}
