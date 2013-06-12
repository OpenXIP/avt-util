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

#include "SoResampleVolume.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoResampleVolume );

SoResampleVolume::SoResampleVolume(void)
{
	SO_ENGINE_CONSTRUCTOR( SoResampleVolume );

	// Inputs
	SO_ENGINE_ADD_INPUT( inputVolume, (0) );
	SO_ENGINE_ADD_INPUT( factor_x, (2) );
	SO_ENGINE_ADD_INPUT( factor_y, (2) );
	SO_ENGINE_ADD_INPUT( factor_z, (1) );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( outputVolume, SoXipSFDataImage );

	mXipImage = 0;
}

void 
SoResampleVolume::initClass()
{
	SO_ENGINE_INIT_CLASS( SoResampleVolume, SoEngine, "SoEngine" );
}

SoResampleVolume::~SoResampleVolume(void)
{
	if( mXipImage )
	{
		mXipImage->unref();
		mXipImage = 0;
	}
}

void SoResampleVolume::inputChanged (SoField* whichField)
{
}

void
SoResampleVolume::evaluate()
{	
	if (!inputVolume.getValue() || !inputVolume.getValue()->get())
	{
		if ( mXipImage )
		{
			mXipImage->unref();
			mXipImage = 0;
		}
		SO_ENGINE_OUTPUT( outputVolume, SoXipSFDataImage, setValue(0) );	
	}
	else
	{
		allocOutputVolume();
		resampleVolume();

		SO_ENGINE_OUTPUT( outputVolume, SoXipSFDataImage, setValue(mXipImage) );	
	}
}

void SoResampleVolume::allocOutputVolume()
{
	SoXipDataImage* vol = inputVolume.getValue();
	if( !vol )
	{
		SoDebugError::post(__FILE__, "input volume is NULL");
		return ;
	}

	int _factorX = factor_x.getValue();
	int _factorY = factor_y.getValue();
	int _factorZ = factor_z.getValue();
	if (_factorX*_factorY*_factorZ == 0)
	{
		SoDebugError::post(__FILE__, "input factors invalidate");
		return ;
	}

	SbXipImage* inputImage = vol->get();
	SbXipImageDimensions volDimensions = inputImage->getDimStored();

	SbMatrix volModelMatrix = inputImage->getModelMatrix();

	SbXipImageDimensions outputDimensions;
	outputDimensions[0] = volDimensions[0] / _factorX;
	outputDimensions[1] = volDimensions[1] / _factorY;
	outputDimensions[2] = volDimensions[2] / _factorZ;

	SbMatrix outputModelMatrix = volModelMatrix;

	if ( mXipImage && mXipImage->get() )
	{
		if ( (mXipImage->get()->getDimStored()   != outputDimensions) ||
			(mXipImage->get()->getModelMatrix() != outputModelMatrix) )
		{
			mXipImage->unref();
			mXipImage = 0;
		}	
	}	

	if ( !mXipImage )
	{			
		mXipImage = new SoXipDataImage();
		mXipImage->ref();

		SbXipImage* ouputImage = new SbXipImage( outputDimensions,
			SbXipImage::UNSIGNED_SHORT,
			12,
			1,								   
			SbXipImage::SEPARATE,
			SbXipImage::LUMINANCE,
			outputModelMatrix);	

		ouputImage->zero();
		mXipImage->set( ouputImage );		
	}

}
void SoResampleVolume::resampleVolume()
{
	SbXipImage* inputImage = inputVolume.getValue()->get();
	SbXipImageDimensions inputDimensions = inputImage->getDimStored();
	SbMatrix inputModelMatrix = inputImage->getModelMatrix();

	int inWidth  = inputDimensions[0];
	int inHeight = inputDimensions[1];
	int inDepth  = inputDimensions[2];

	SbXipImage* outputImage = mXipImage->get();
	SbXipImageDimensions outputDimensions = outputImage->getDimStored();
	SbMatrix outputModelMatrix = outputImage->getModelMatrix();

	unsigned short* inImagePtr	= (unsigned short*) inputImage->refBufferPtr();	
	unsigned short* outImagePtr = (unsigned short*) outputImage->refBufferPtr();

	int volWidth  = outputDimensions[0];
	int volHeight = outputDimensions[1];
	int volDepth  = outputDimensions[2];

	unsigned short _factorX = factor_x.getValue();
	unsigned short _factorY = factor_y.getValue();
	unsigned short _factorZ = factor_z.getValue();

	for (int z = 0; z < volDepth; z++)
		for (int y = 0; y < volHeight; y++)
			for (int x = 0; x < volWidth; x++)
			{
				unsigned short nValue = inImagePtr[(z*_factorZ)*inWidth*inHeight+(y*_factorY)*inWidth+(x*_factorX)];

				*outImagePtr = nValue;
				outImagePtr++;
			}

	inputImage->unrefBufferPtr();		
	outputImage->unrefBufferPtr();
	
}
