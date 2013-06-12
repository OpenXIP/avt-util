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

#include "SoItkImageToXipMask.h"
#include <itkCastImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoItkImageToXipMask );

SoItkImageToXipMask::SoItkImageToXipMask(void)
{
	SO_ENGINE_CONSTRUCTOR( SoItkImageToXipMask );

	// Inputs
	SO_ENGINE_ADD_INPUT ( modelMatrix, (SbMatrix::identity()) );

	SO_ENGINE_ADD_INPUT( input, (0) );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( output, SoXipSFDataImage );

	mXipImage = 0;
}

void 
SoItkImageToXipMask::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkImageToXipMask, SoEngine, "SoEngine" );
}

SoItkImageToXipMask::~SoItkImageToXipMask(void)
{
	if( mXipImage )
	{
		mXipImage->unref();
		mXipImage = 0;
	}
}

void SoItkImageToXipMask::inputChanged (SoField* whichField)
{
}

template <class inType, class outType, int nDims>
static SoXipDataImage *
createXipImageSingle(SoItkDataImage * xipItkImage, SbXipImage::DataType typeFlag,
		     int bitsPerComp, SbMatrix & modelMat)
{
	typedef itk::Image< inType, nDims > InputImageType;
	typedef itk::Image< outType, nDims > OutputImageType;
	typedef itk::CastImageFilter< InputImageType, OutputImageType > FilterType;
	
	FilterType::Pointer filter = FilterType::New();
	
	// Set the filter's inputs
	filter->SetInPlace(false);

	itk::Object* obj = static_cast<itk::Object* >( xipItkImage->getPointer() );
	if (obj)
	{
		InputImageType* val = dynamic_cast<InputImageType* >( obj );
		if (val)
			filter->SetInput(0, val);
	}
	
	// Start processing the ouputs
	filter->Update();

	// Retrieve the filter's outputs
	filter->GetOutput()->Register();

    OutputImageType * itkImage = reinterpret_cast<OutputImageType *>(filter->GetOutput());

    typename OutputImageType::RegionType region = itkImage->GetBufferedRegion();

    SbXipImageDimensions dimensions(1, 1, 1);

    for (unsigned int i = 0; i < nDims; ++ i)
    {
	dimensions[i] = region.GetSize()[i];
    }

    SbXipImage* image =
	new SbXipImage(dimensions, typeFlag, bitsPerComp,
		       itkImage->GetBufferPointer(), 1,
		       SbXipImage::INTERLEAVED, SbXipImage::LUMINANCE,
		       modelMat);

    if (!image) return 0;

    SoXipDataImage * xipImage = new SoXipDataImage;
    xipImage->ref();
    xipImage->addRef(xipItkImage);
    xipImage->set(image);

    return xipImage;
}

template <int nDims>
static SoXipDataImage *
createXipImage(SoItkDataImage * xipItkImage, SbMatrix & modelMat)
{
    SoXipDataImage * xipImage = 0;

    switch (xipItkImage->getType())
    {
	case SoItkDataImage::FLOAT:
		xipImage = createXipImageSingle<float, unsigned char, nDims>(xipItkImage, SbXipImage::UNSIGNED_BYTE, 8, modelMat);
		break;

    case SoItkDataImage::UNSIGNED_CHAR:
		xipImage = createXipImageSingle<unsigned char, unsigned char, nDims>(xipItkImage, SbXipImage::UNSIGNED_BYTE, 8, modelMat);
		break;

    case SoItkDataImage::UNSIGNED_SHORT:
		xipImage = createXipImageSingle<unsigned short, unsigned char, nDims>(xipItkImage, SbXipImage::UNSIGNED_BYTE, 8, modelMat);
		break;
	}
                
    return xipImage;
}

void
SoItkImageToXipMask::evaluate()
{	
	if( mXipImage )
	{
		mXipImage->unref();
		mXipImage = 0;
		SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue(0) );
	}

	SoItkDataImage* xipItkImage = input.getValue();

	if (!xipItkImage)
	    return;

	if (xipItkImage->getType() != SoItkDataImage::UNSIGNED_SHORT &&
	    xipItkImage->getType() != SoItkDataImage::UNSIGNED_CHAR &&
		xipItkImage->getType() != SoItkDataImage::FLOAT)
	{
	    SoDebugError::post( __FILE__, "Itk image only supports UNSIGNED_SHORT, UNSIGNED_CHAR, OR FLOAT" );
	    return ;
	}

	if (xipItkImage->getComponentLayoutType() != SoItkDataImage::LUMINANCE)
	{
	    SoDebugError::post( __FILE__, "Itk image only supports LUMINANCE" );
	    return ;
	}

	SbMatrix modelMat = modelMatrix.getValue();

	try
	{
        switch (xipItkImage->getNumDimension())
        {
	    case 1:
		mXipImage = createXipImage<1>(xipItkImage, modelMat);
		break;
	    case 2:
		mXipImage = createXipImage<2>(xipItkImage, modelMat);
		break;
	    case 3:
		mXipImage = createXipImage<3>(xipItkImage, modelMat);
		break;
	    }
	}
	catch( itk::ExceptionObject& e )
	{
		SoDebugError::post( e.GetFile(), "line %d: %s", e.GetLine(), e.GetDescription() );
		return ;
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown exception" );
		return ;
	}

	SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue(mXipImage) );
}
