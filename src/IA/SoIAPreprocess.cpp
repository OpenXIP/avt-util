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

#include "SoIAPreprocess.h"
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

SO_ENGINE_SOURCE(SoIAPreprocess);

SoIAPreprocess::SoIAPreprocess()
{
	
	SO_ENGINE_CONSTRUCTOR(SoIAPreprocess);

	SO_ENGINE_ADD_INPUT( Input1, (0) );

	SO_ENGINE_ADD_OUTPUT( Output, SoItkSFDataImage );
	///////////////////////////////
    SO_ENGINE_ADD_INPUT( Extention, (4) );
	////////////////////////////
	mOutput = 0;

}
void SoIAPreprocess::initClass()
{
	SO_ENGINE_INIT_CLASS(SoIAPreprocess,SoEngine,"SoEngine")
}

SoIAPreprocess::~SoIAPreprocess()
{
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
	}
}
void SoIAPreprocess::evaluate()
{
	SoItkDataImage* inputImage1= Input1.getValue();
	if (inputImage1 == NULL)
		return;

	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
	}
	
	typedef   float  PixelTypeRead;
	const   unsigned int        Dimension = 3;
	typedef itk::Image< PixelTypeRead, Dimension >    ImageTypeRead;

	ImageTypeRead* itkImage1=static_cast< ImageTypeRead* >( inputImage1->getPointer());

	typedef itk::ImageRegionIterator<ImageTypeRead> IteratorType;
	ImageTypeRead::Pointer image1=ImageTypeRead::New();
	image1=itkImage1;
	IteratorType it1(image1,image1->GetRequestedRegion());
	
	int w=0,h=0,l=0;

	ImageTypeRead::RegionType region;
	region = image1->GetBufferedRegion();
	ImageTypeRead::SizeType size= region.GetSize();
	ImageTypeRead::IndexType start =region.GetIndex();
	w= size[0];
	h= size[1];
	l= size[2];

	if (w*h*l == 0)
		return;

	int times=Extention.getValue();
	float *origimage=itkImage1->GetBufferPointer();
	float *interimage=new float [w*h*l*times];
	for (int i=0;i<l*times;i++)
	{
		for (int j=0;j<h;j++)
		{
			for (int k=0;k<w;k++)
			{
				float pos=i/(float)times;
				if (pos>l-1)
				{
					pos=l-1;
				}
				float uppix=origimage[((int)(ceil(pos)))*w*h+j*w+k];
				float downpix=origimage[((int)(floor(pos)))*w*h+j*w+k];
				interimage[i*w*h+j*w+k]=downpix+(pos-i/times)*(uppix-downpix);
			}
		}
	}

	//FILE* fpw3;
	//char MaskFileName[100];
	//sprintf(MaskFileName,"D:\\outimge1.img");
	//fpw3=fopen(MaskFileName,"wb");
	//if (!fpw3)
	//{
	//	std::cout<<"cannot open the file!"<<std::endl;
	//}

	//while(fwrite(origimage, sizeof(float),w*h*l, fpw3) !=w*h*l)
	//{
	//	std::cout<<"cannot read the data correctly!"<<std::endl;
	//}
	//fclose(fpw3);

	ImageTypeRead::Pointer image= ImageTypeRead::New();
	ImageTypeRead::SizeType size1;
	size1[0] = w;
	size1[1] = h;
	size1[2]=  l*times;
	ImageTypeRead::IndexType start1;
	start1[0] = 0;
	start1[1] = 0;
	start1[2] = 0;
	ImageTypeRead::RegionType region1;
	region1.SetSize( size1 );
	region1.SetIndex( start1 );
	image->SetRegions( region1);
	image->Allocate();
	double spacing[3];
	spacing[0] = 1;
	spacing[1] = 1;
	spacing[2] = 1;
	image->SetSpacing( spacing );
	double origin[3];
	origin[0] = 0;
	origin[1] = 0;
	origin[2] =0 ;
	image->SetOrigin( origin);
	IteratorType it( image, region1);
	it.GoToBegin();
	float * data2= interimage;
	while( ! it.IsAtEnd() )
	{
		it.Set((float)(*data2));
		++it;
		++data2;
	}

	
	//FILE* fpw;
	//sprintf(MaskFileName,"D:\\outimge2.img");
	//fpw=fopen(MaskFileName,"wb");
	//if (!fpw)
	//{
	//	std::cout<<"cannot open the file!"<<std::endl;
	//}

	//while(fwrite(interimage, sizeof(float),w*h*l*5, fpw) !=w*h*l*5)
	//{
	//	std::cout<<"cannot read the data correctly!"<<std::endl;
	//}
	//fclose(fpw);
	
	//for (it1.GoToBegin();!it1.IsAtEnd(); ++it1)
	//{
	//	
	//	float a=it1.Get();
	//	if (a>500)
	//	{
	//		it1.Set(1024);
	//	}
	//	else
	//	{
	//		it1.Set(a*1024/500);
	//	}		
	//}
	image->Register();
	mOutput = new SoItkDataImage( inputImage1->getType(), inputImage1->getComponentLayoutType(), inputImage1->getNumDimension() );		
	mOutput->ref();                                                      		
	mOutput->setPointer( image);  
	
	delete [] interimage;
	SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue(mOutput));
}
