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

/**
 * @version	April 2010
 * @author Jie Zheng
 */

#include "SoIABinaryDilate.h"
#include <math.h>
#include <cstdlib>
#include <iostream>

#include <itkRGBPixel.h>
#include <itkRGBAPixel.h>
#include <xip/inventor/itk/SoItkSFDataImage.h>
#include <Inventor/fields/SoMFShort.h>
#include <itkImage.h>
#include <itkImageRegionIterator.h>
#include "itkBinaryErodeImageFilter.h"
#include "itkBinaryDilateImageFilter.h"
#include "itkBinaryBallStructuringElement.h" 

SO_ENGINE_SOURCE(SoIABinaryDilate);

SoIABinaryDilate::SoIABinaryDilate()
{
	
	SO_ENGINE_CONSTRUCTOR(SoIABinaryDilate);

	SO_ENGINE_ADD_INPUT( Input1, (0) );
    SO_ENGINE_ADD_INPUT( Radius, (0) );
    SO_ENGINE_ADD_INPUT( DilateValue, (0) );
	SO_ENGINE_ADD_OUTPUT( Output, SoItkSFDataImage );
	mOutput = 0;

}
void SoIABinaryDilate::initClass()
{
	SO_ENGINE_INIT_CLASS(SoIABinaryDilate,SoEngine,"SoEngine")
}

SoIABinaryDilate::~SoIABinaryDilate()
{
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
	}
}
void SoIABinaryDilate::evaluate()
{
	SoItkDataImage* inputImage1= Input1.getValue();
	if (inputImage1 == NULL)
		return;

	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
	}

	typedef float PixelTypeRead;
	const unsigned int Dimension = 3;
	typedef itk::Image< PixelTypeRead, Dimension >    ImageTypeRead;

	ImageTypeRead* itkImage1=static_cast< ImageTypeRead* >( inputImage1->getPointer());

	typedef itk::BinaryBallStructuringElement< PixelTypeRead,Dimension  >             StructuringElementType;
   // typedef itk::BinaryErodeImageFilter< ImageTypeRead,ImageTypeRead,StructuringElementType >  ErodeFilterType;
    typedef itk::BinaryDilateImageFilter<ImageTypeRead, ImageTypeRead, StructuringElementType >  DilateFilterType;

	//ErodeFilterType::Pointer  binaryErode  = ErodeFilterType::New();
    DilateFilterType::Pointer binaryDilate = DilateFilterType::New();
	StructuringElementType  structuringElement;
	structuringElement.SetRadius(Radius.getValue());  // 3x3 structuring element
	structuringElement.CreateStructuringElement();
	//binaryErode->SetKernel(  structuringElement );
	binaryDilate->SetKernel( structuringElement );

	//InternalPixelType background =   0;
    //InternalPixelType foreground = 255;

    //binaryErode->SetErodeValue( foreground );
	binaryDilate->SetDilateValue( DilateValue.getValue());


	binaryDilate->SetInput( itkImage1 );
	binaryDilate->Update();
    binaryDilate->GetOutput()->Register();
	mOutput = new SoItkDataImage( inputImage1->getType(), inputImage1->getComponentLayoutType(), inputImage1->getNumDimension() );		
	mOutput->ref();                                                      		
	mOutput->setPointer( binaryDilate->GetOutput() );  

	SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue(mOutput));
}
