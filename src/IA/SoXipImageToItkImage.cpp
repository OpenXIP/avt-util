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

#include "SoXipImageToItkImage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoXipImageToItkImage );

SoXipImageToItkImage::SoXipImageToItkImage(void)
{
	SO_ENGINE_CONSTRUCTOR( SoXipImageToItkImage );

	// Inputs
	SO_ENGINE_ADD_INPUT( input, (0) );
	SO_ENGINE_ADD_INPUT(trigger, ());	

	// Outputs
	SO_ENGINE_ADD_OUTPUT( output, SoItkSFDataImage );

	mItkImage = 0;
}

void 
SoXipImageToItkImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipImageToItkImage, SoEngine, "SoEngine" );
}

SoXipImageToItkImage::~SoXipImageToItkImage(void)
{
	if( mItkImage )
	{
		mItkImage->unref();
		mItkImage = 0;
	}
}

void SoXipImageToItkImage::inputChanged (SoField* whichField)
{
	if (whichField == &trigger)
	{
		enableOutput(TRUE);
		imageConvert();
	}

	enableOutput(FALSE);
}

void SoXipImageToItkImage::enableOutput(SbBool status)
{
	output.enable(status);
}

void SoXipImageToItkImage::imageConvert()
{
	if( mItkImage )
	{
		mItkImage->unref();
		mItkImage = 0;
	}

	SoXipDataImage* radImage = input.getValue();
	if( !radImage )
	{
		SO_ENGINE_OUTPUT( output, SoItkSFDataImage, setValue(0) );
		return ;
	}

    SbXipImage* inputImage = radImage->get();
	if( inputImage->getType() != SbXipImage::UNSIGNED_SHORT &&
		inputImage->getType() != SbXipImage::FLOAT &&
		inputImage->getType() != SbXipImage::SHORT &&
		inputImage->getType() != SbXipImage::UNSIGNED_BYTE )
	{
		SoDebugError::post( __FILE__, "Itk image only supports UNSIGNED_SHORT, SHORT, UNSIGNED_BYTE or FLOAT" );
		return ;
	}

	try
	{
		SbXipImage* inputImage = radImage->get();
		SbXipImageDimensions dimensions = inputImage->getDimStored();
		SbMatrix volModelMatrix = inputImage->getModelMatrix();

		unsigned int imageDimension = 2;
		if( dimensions[2] > 1 )
			++ imageDimension;

		//decompose the model matrix
		SbVec3f colVector, rowVector, norVector, volPosition;

		colVector[0] = volModelMatrix[0][0];
		colVector[1] = volModelMatrix[0][1];
		colVector[2] = volModelMatrix[0][2];

		rowVector[0] = volModelMatrix[1][0];
		rowVector[1] = volModelMatrix[1][1];
		rowVector[2] = volModelMatrix[1][2];

		norVector[0] = volModelMatrix[2][0];
		norVector[1] = volModelMatrix[2][1];
		norVector[2] = volModelMatrix[2][2];

		volPosition[0] = volModelMatrix[3][0];
		volPosition[1] = volModelMatrix[3][1];
		volPosition[2] = volModelMatrix[3][2];

		SbVec3f scale;
		scale[0] = colVector.length() / (float)dimensions[0];
		scale[1] = rowVector.length() / (float)dimensions[1];
		scale[2] = norVector.length() / (float)dimensions[2];

		if( inputImage->getComponentLayoutType() != SbXipImage::LUMINANCE && 
			inputImage->getComponentLayoutType() != SbXipImage::RGB && 
			inputImage->getComponentLayoutType() != SbXipImage::RGBA )
		{
			SoDebugError::post( __FILE__, "Image format not supported yet" );
			SoDebugError::post( __FILE__, "Rad To Itk only works with LUMINANCE, RGB and RGBA" );
			return ;
		}

		#define CREATE_RADITK_IMAGE( Type, TypeFlag, ComponentLayoutFlag, Dimension )	\
		{																				\
			Type* pixelBuffer = (Type *) inputImage->refBufferPtr();					\
																						\
			typedef itk::ImportImageFilter< Type, Dimension > ImportFilterType;			\
																						\
			ImportFilterType::SizeType size;											\
			ImportFilterType::IndexType start;											\
			double origin[ Dimension ];													\
			double spacing[ Dimension ];												\
																						\
			for( unsigned int d = 0; d < Dimension; ++ d )								\
			{												                            \
				size[d]    = dimensions[d];												\
				start[d]   = 0;															\
				origin[d]  = 0;															\
				spacing[d] = scale[d];															\
			}																			\
																						\
			ImportFilterType::RegionType region;										\
			region.SetIndex( start );													\
			region.SetSize( size );														\
																						\
			ImportFilterType::Pointer importFilter = ImportFilterType::New();			\
			importFilter->SetRegion( region );											\
			importFilter->SetOrigin( origin );											\
			importFilter->SetSpacing( spacing );										\
			importFilter->SetImportPointer(	pixelBuffer, size[0] * size[1], false );	\
			importFilter->Update();														\
																						\
			inputImage->unrefBufferPtr();												\
																						\
			/* Since Itk objects are reference-counted, we need to manually   */		\
			/* increment the reference count of the resulting image, to avoid */		\
			/* the importFilter instance to destroy it.                       */		\
			/*                                                                */		\
			importFilter->GetOutput()->Register();										\
																						\
			mItkImage = new SoItkDataImage( TypeFlag, ComponentLayoutFlag, Dimension );	\
			mItkImage->ref();															\
			mItkImage->addRef( radImage );												\
			mItkImage->setPointer( importFilter->GetOutput() );							\
		}

		switch( imageDimension )
		{
			case 2:
			{
				switch( inputImage->getType() )                                      
				{
					case SbXipImage::UNSIGNED_SHORT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE(unsigned short, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::LUMINANCE, 2);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<unsigned short>, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGB, 2);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<unsigned short>, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGBA, 2);
							}
							break;
						}
					}
					break ;
					case SbXipImage::FLOAT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE( float, SoItkDataImage::FLOAT, SoItkDataImage::LUMINANCE, 2);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<float>, SoItkDataImage::FLOAT, SoItkDataImage::RGB, 2);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<float>, SoItkDataImage::FLOAT, SoItkDataImage::RGBA, 2);
							}
							break;
						}
					}
					break ;
					case SbXipImage::SHORT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE( short, SoItkDataImage::SHORT, SoItkDataImage::LUMINANCE, 2);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<short>, SoItkDataImage::SHORT, SoItkDataImage::RGB, 2);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<short>, SoItkDataImage::SHORT, SoItkDataImage::RGBA, 2);
							}
							break;
						}
					}
					break ;
					case SbXipImage::UNSIGNED_BYTE:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE(unsigned char, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::LUMINANCE, 2);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<unsigned char>, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGB, 2);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<unsigned char>, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGBA, 2);
							}
							break;
						}
					}
					break ;
				}
			}
			break;
			case 3:
			{
				switch( inputImage->getType() )                                      
				{
					case SbXipImage::UNSIGNED_SHORT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE(unsigned short, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::LUMINANCE, 3);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<unsigned short>, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGB, 3);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<unsigned short>, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGBA, 3);
							}
							break;
						}
					}
					break ;
					case SbXipImage::FLOAT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE( float, SoItkDataImage::FLOAT, SoItkDataImage::LUMINANCE, 3);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<float>, SoItkDataImage::FLOAT, SoItkDataImage::RGB, 3);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<float>, SoItkDataImage::FLOAT, SoItkDataImage::RGBA, 3);
							}
							break;
						}
					}
					break ;
					case SbXipImage::SHORT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE( short, SoItkDataImage::SHORT, SoItkDataImage::LUMINANCE, 3);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<short>, SoItkDataImage::SHORT, SoItkDataImage::RGB, 3);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<short>, SoItkDataImage::SHORT, SoItkDataImage::RGBA, 3);
							}
							break;
						}
					}
					break ;
					case SbXipImage::UNSIGNED_BYTE:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE(unsigned char, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::LUMINANCE, 3);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<unsigned char>, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGB, 3);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<unsigned char>, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGBA, 3);
							}
							break;
						}
					}
					break ;
				}
			}
			break;
		}
#undef CREATE_RADITK_IMAGE
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

	SO_ENGINE_OUTPUT( output, SoItkSFDataImage, setValue( mItkImage ) );
}

void
SoXipImageToItkImage::evaluate()
{	
}
