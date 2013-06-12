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
*	@file    SoROIVolume.h
*	@brief   general the ROI volume from the original volume
*	@author  Jie Zheng
**/

#include <Inventor/engines/SoSubEngine.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFBool.h>

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/itk/SoItkSFDataImage.h>

#include <InsightToolkit/Common/itkImage.h>
#include <InsightToolkit/BasicFilters/itkImportImageFilter.h>

class __declspec(dllexport) SoROIVolume : public SoEngine
{
    SO_ENGINE_HEADER( SoROIVolume );

public:
    SoROIVolume();
    static void initClass();

	SoSFBool			bypassTrigger;
    SoXipSFDataImage	volumeImageData;
    SoMFVec3f			seeds;
	SoSFInt32			size;
    SoSFInt32			depth;
    // Input 
	SoSFTrigger			update;
    
    SoEngineOutput		roiVolume;			// SoXipSFDataImage  
    SoEngineOutput		roiITKVolume;		// SoXipSFDataImage  
	SoEngineOutput		roiRegion;			//SoMFInt32
	SoEngineOutput		roiSize;			//SoMFInt32
	SoEngineOutput		roiOrigin;			//SoMFInt32
    SoEngineOutput		seedPoints;			// SoMFVec3f 
    
private:
    // Evaluation method
	virtual void inputChanged (SoField* whichField);
    virtual void evaluate();
    
	void enableOutput(SbBool status);
	void updateROIVolume();	

	void getROIPosition(int* iCol, int* iRow, int* iDepth, SbVec3f &center, int volCol, int volRow, int volDepth);
    
protected:
	~SoROIVolume();

	SoMFInt32 regionBuffer;
	SoMFInt32 sizeBuffer;
	SoMFInt32 originBuffer;

	SoMFVec3f seedBuffer;
    SoXipDataImage* mOutput;
	SoItkDataImage* mItkImage;
};
