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

#include <memory.h>
#include <fstream>

#include "SoROIVolume.h"

using namespace std; 

const float EPSILON = 0.000001;

SO_ENGINE_SOURCE(SoROIVolume);

SoROIVolume::SoROIVolume()
{
    SO_ENGINE_CONSTRUCTOR(SoROIVolume);

    // Inputs
    seeds.setNum(0);
    SO_ENGINE_ADD_INPUT( bypassTrigger, (FALSE) );	
    SO_ENGINE_ADD_INPUT( volumeImageData, (0) );
	SO_ENGINE_ADD_INPUT( seeds, (SbVec3f(0,0,0)) );
	SO_ENGINE_ADD_INPUT( size, (32) );
	SO_ENGINE_ADD_INPUT( depth, (32) );
	SO_ENGINE_ADD_INPUT( update, () );	
	
	// Output
	SO_ENGINE_ADD_OUTPUT( roiVolume, SoXipSFDataImage );
	SO_ENGINE_ADD_OUTPUT( roiITKVolume, SoItkSFDataImage );
	SO_ENGINE_ADD_OUTPUT( roiRegion, SoMFInt32 );
	SO_ENGINE_ADD_OUTPUT( roiSize, SoMFInt32 );
	SO_ENGINE_ADD_OUTPUT( roiOrigin, SoMFInt32 );

	SO_ENGINE_ADD_OUTPUT( seedPoints, SoMFVec3f );

	mOutput = 0;
	mItkImage = 0;

	seedBuffer.setNum(0);

	int origin[3] = {0, 0, 0};

	regionBuffer.setNum(6);
	regionBuffer.setValues(0, 3, origin);
	regionBuffer.setValues(3, 3, origin);

	sizeBuffer.setNum(3);
	sizeBuffer.setValues(0, 3, origin);

	originBuffer.setNum(3);
	originBuffer.setValues(0, 3, origin);
}

SoROIVolume::~SoROIVolume()
{
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
	}	

	if( mItkImage )
	{
		mItkImage->unref();
		mItkImage = 0;
	}
}

void SoROIVolume::initClass()
{
    SO_ENGINE_INIT_CLASS(SoROIVolume,SoEngine,"SoEngine");
}

void SoROIVolume::inputChanged (SoField* whichField)
{
	SbBool bypass = bypassTrigger.getValue();

	if (whichField == &update || (bypass && whichField == &seeds))
	{
		enableOutput(true);
		updateROIVolume();
	}

	enableOutput(false);
}

void SoROIVolume::enableOutput(SbBool status)
{
	roiVolume.enable(status);
	roiITKVolume.enable(status);
	roiRegion.enable(status);
	roiSize.enable(status);
	roiOrigin.enable(status);

	seedPoints.enable(status);
}

void SoROIVolume::updateROIVolume()
{
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
	}
	
	if( mItkImage )
	{
		mItkImage->unref();
		mItkImage = 0;
	}

	SoXipDataImage* inputXipImage = volumeImageData.getValue();
	if( !inputXipImage )
		return;

    SbXipImage* inputImage = inputXipImage->get();
	if(inputImage->getType() != SbXipImage::UNSIGNED_BYTE && 
		inputImage->getType() != SbXipImage::UNSIGNED_SHORT)
	{
		SoDebugError::post( __FILE__, "only support UNSIGNED_BYTE and UNSIGNED_SHORT data type");
	    return;
	}

	SbXipImageDimensions dimensions = inputImage->getDimStored();
	SbMatrix volModelMatrix = inputImage->getModelMatrix();

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

	//voxel spacing
	float spacing[3];
	spacing[0] = colVector.length() / float(dimensions[0]);
	spacing[1] = rowVector.length() / float(dimensions[1]);
	spacing[2] = norVector.length() / float(dimensions[2]);

	//transcode the seed points
	int seedNum = seeds.getNum();
	if (seedNum <= 0)
	{
	    SoDebugError::post( __FILE__, "The number of input point is less than 0" );
	    return;
	}

	SbVec3f center;
	center = (seeds[0] + seeds[seedNum-1]) / 2.0;
	
	//get the roi information
	if (depth.getValue()*size.getValue() <= 0)
	{
	    SoDebugError::post( __FILE__, "The input ROI is less than 0" );
	    return;
	}

	//get the corners of the ROI
	int iCol[2], iRow[2], iDepth[2];
	getROIPosition(iCol, iRow, iDepth, center, dimensions[0], dimensions[1], dimensions[2]);

	//build ROI model matrix
	float factor[3];
	factor[0] = float(iCol[1] - iCol[0]) / float(dimensions[0]);
	factor[1] = float(iRow[1] - iRow[0]) / float(dimensions[1]);
	factor[2] = float(iDepth[1] - iDepth[0]) / float(dimensions[2]);

	float fTop[3];
	fTop[0] = float(iCol[0]) / float(dimensions[0]);
	fTop[1] = float(iRow[0]) / float(dimensions[1]);
	fTop[2] = float(iDepth[0]) / float(dimensions[2]);

    SbMatrix ROImodelmatrix(colVector[0]*factor[0], colVector[1]*factor[0], colVector[2]*factor[0], 0, 
							rowVector[0]*factor[1], rowVector[1]*factor[1], rowVector[2]*factor[1], 0, 
							norVector[0]*factor[2], norVector[1]*factor[2], norVector[2]*factor[2], 0, 
							volPosition[0]+colVector.length()*fTop[0], volPosition[1]+rowVector.length()*fTop[1], volPosition[2]+norVector.length()*fTop[2], 1);

	//create the ROI XIP image
	SbXipImageDimensions ROIdims((iCol[1]-iCol[0]), (iRow[1]-iRow[0]), (iDepth[1]-iDepth[0]));
    SbXipImage* ROIimage =
		new SbXipImage(ROIdims, inputImage->getType(), inputImage->getBitsStored(),
		inputImage->getComponents(),inputImage->getComponentType(), inputImage->getComponentLayoutType(),
		ROImodelmatrix);

    if (!ROIimage) 
	{
	    SoDebugError::post( __FILE__, "can not create the ROI volume" );
	    return;
	}
	
	//copy the ROI image data
	int bytesAllocated = 0;
	switch (inputImage->getType())
	{
	    case SbXipImage::UNSIGNED_BYTE:
			bytesAllocated = 1; 
			break;

	    case SbXipImage::UNSIGNED_SHORT:
			bytesAllocated = 2; 
			break;
	}

	int bytesComponents = bytesAllocated * inputImage->getComponents();

	unsigned char* radData = (unsigned char*)inputImage->refBufferPtr();
	unsigned char* roiData = (unsigned char*)ROIimage->refBufferPtr();
    
	int nSize = dimensions[0] * dimensions[1] * bytesComponents;
	int nROISize = ROIdims[0] * ROIdims[1] * bytesComponents;

	for (int j = 0; j < ROIdims[2]; j++)
	{
		for (int i = 0; i < ROIdims[1]; i++)
		{
			unsigned char *pSrc = radData + (j+iDepth[0])*nSize + (i+iRow[0])*dimensions[0]*bytesComponents + iCol[0]*bytesComponents;
			unsigned char *pDest = roiData + j*nROISize + i*ROIdims[0]*bytesComponents;

			memcpy(pDest, pSrc, ROIdims[0]*bytesComponents);
		}
	}

	//set the engine output
	SoXipDataImage * mOutput = new SoXipDataImage;
    mOutput->ref();
    mOutput->set(ROIimage);    

    SO_ENGINE_OUTPUT( roiVolume, SoXipSFDataImage, setValue(mOutput) );

	//create the roi volume as an itk image for the further process
	int Dimension = 3;
	#define CREATE_RADITK_IMAGE( Type, TypeFlag, ComponentLayoutFlag, Dimension )	\
	{																				\
		Type* pixelBuffer = (Type *) ROIimage->refBufferPtr();						\
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
			size[d]    = ROIdims[d];												\
			start[d]   = 0;															\
			origin[d]  = 0;															\
			spacing[d] = 1.0;														\
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
		ROIimage->unrefBufferPtr();												    \
																					\
		/* Since Itk objects are reference-counted, we need to manually   */		\
		/* increment the reference count of the resulting image, to avoid */		\
		/* the importFilter instance to destroy it.                       */		\
		/*                                                                */		\
		importFilter->GetOutput()->Register();										\
																					\
		mItkImage = new SoItkDataImage( TypeFlag, ComponentLayoutFlag, Dimension );	\
		mItkImage->ref();															\
		mItkImage->addRef( mOutput );												\
		mItkImage->setPointer( importFilter->GetOutput() );							\
	}

	switch(ROIimage->getType())
	{
	case SbXipImage::UNSIGNED_SHORT:
		{
			CREATE_RADITK_IMAGE(unsigned short, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::LUMINANCE, 3);
		}
		break;

	case SbXipImage::UNSIGNED_BYTE:
		{
			CREATE_RADITK_IMAGE(unsigned char, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::LUMINANCE, 3);
		}
		break;
	}
	SO_ENGINE_OUTPUT( roiITKVolume, SoItkSFDataImage, setValue( mItkImage ) );

	inputImage->unrefBufferPtr();

	//set the ROI size information
	SoMFInt32 buffer;

	int origin[3] = {0, 0, 0};
	regionBuffer.setValues(0, 3, origin);

	int dims[3] = {ROIdims[0], ROIdims[1], ROIdims[2]};
	regionBuffer.setValues(3, 3, dims);
	sizeBuffer.setValues(0, 3, dims);

	SO_ENGINE_OUTPUT( roiRegion, SoMFInt32, setValues(0, regionBuffer.getNum(), regionBuffer.getValues(0)) );
	SO_ENGINE_OUTPUT( roiSize, SoMFInt32, setValues(0, sizeBuffer.getNum(), sizeBuffer.getValues(0)) );

	originBuffer.set1Value(0, (int)(colVector.length()*fTop[0]/spacing[0]));
	originBuffer.set1Value(1, (int)(rowVector.length()*fTop[1]/spacing[1]));
	originBuffer.set1Value(2, (int)(norVector.length()*fTop[2]/spacing[2]));

	SO_ENGINE_OUTPUT( roiOrigin, SoMFInt32, setValues(0, originBuffer.getNum(), originBuffer.getValues(0)) );

    //normalize the seed points to the ROI
	//for (int i = 0 ; i < seedNum; i++)
	{
		//SbVec3f point = seeds[i];
		SbVec3f point = center;

		point[0] = float(point[0]*dimensions[0] - iCol[0]) / float(ROIdims[0]);
		point[0]  = point[0] < EPSILON ? 0 : point[0];
		point[0]  = point[0] - 1.0 > EPSILON ? 1.0 : point[0];

		point[1] = float(point[1]*dimensions[1] - iRow[0]) / float(ROIdims[1]);
		point[1]  = point[1] < EPSILON ? 0 : point[1];
		point[1]  = point[1] - 1.0 > EPSILON ? 1.0 : point[1];

		point[2] = float(point[2]*dimensions[2] - iDepth[0]) / float(ROIdims[2]);

		seedBuffer.set1Value(0, point);
		//seedBuffer.set1Value(i, point);
	}

	SO_ENGINE_OUTPUT( seedPoints, SoMFVec3f, setValues(0, seedBuffer.getNum(), seedBuffer.getValues(0)) );
}

void SoROIVolume::evaluate()
{  
	//int nNum = seeds.getNum();
	//if (nNum > 1)
	//{
	//	if(seeds[0] != SbVec3f(0.0, 0.0, 0.0) && seeds[nNum-1] != SbVec3f(0.0, 0.0, 0.0))
	//	{
	//		SO_ENGINE_OUTPUT( roiRegion, SoMFInt32, setValues(0, regionBuffer.getNum(), regionBuffer.getValues(0)) );
	//		SO_ENGINE_OUTPUT( roiSize, SoMFInt32, setValues(0, sizeBuffer.getNum(), sizeBuffer.getValues(0)) );
	//		SO_ENGINE_OUTPUT( roiOrigin, SoMFInt32, setValues(0, originBuffer.getNum(), originBuffer.getValues(0)) );
	//	}
	//}
}

void SoROIVolume::getROIPosition(int* iCol, int* iRow, int* iDepth, SbVec3f &center, int volCol, int volRow, int volDepth)
{
	int len = size.getValue();
	int iCenter = center[0] * volCol;
	iCol[0] = (iCenter - len) < 0 ? 0 : (iCenter - len); 
	iCol[1] = (iCenter + len) > volCol ? volCol : (iCenter + len);

	iCenter = center[1] * volRow;
	iRow[0] = (iCenter - len) < 0 ? 0 : (iCenter - len); 
	iRow[1] = (iCenter + len) > volRow ? volRow : (iCenter + len);

	len = depth.getValue();
	iCenter = center[2] * volDepth;
	iDepth[0] = (iCenter - len) < 0 ? 0 : (iCenter - len); 
	iDepth[1] = (iCenter + len) > volDepth ? volDepth : (iCenter + len);
}
