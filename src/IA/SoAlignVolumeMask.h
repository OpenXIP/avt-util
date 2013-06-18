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
*	@file    SoAlignVolumeMask.h
*	@brief   Align two volume mask in the same coordination system
*	@author  Jie Zheng
**/

#if !defined(AFX_SoAlignVolumeMask_H__353923CC_3ABE_43A3_9C56_7CAC0DB1F90C__INCLUDED_)
#define AFX_SoAlignVolumeMask_H__353923CC_3ABE_43A3_9C56_7CAC0DB1F90C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Inventor/Engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/SbString.h>

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/itk/SoItkSFDataImage.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include <xip/inventor/dicom/xipivDicomUtils.h>

#include <xip/inventor/itk/SoItkSFDataImage.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/itk/SoItkSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>

class __declspec(dllexport) SoAlignVolumeMask : public SoEngine
{
	SO_ENGINE_HEADER( SoAlignVolumeMask);

public:
	SoAlignVolumeMask(void);
	static void initClass();

	SoXipSFDataImage		inputMask;
		// Input Dcm seg Image

	SoXipSFDataImage		refMask;
		// reference Dcm seg Image

	SoSFTrigger		process; 

	SoEngineOutput		inputVolume; // 
	SoEngineOutput		refVolume; // 

private:
	~SoAlignVolumeMask(void);
		// Destructor

	virtual void evaluate();
		// Evaluation method

	void resampleVolume();

	virtual void inputChanged (SoField* whichField);

protected:
	SoXipDataImage* mXipInputImage;
	SoXipDataImage* mXipRefImage;

	void clearDataImages();

	void getPositionItems(SbXipImage *image, double imgPosition[3], int imgDimension[3], double imgSpacing[3]);

	void createXipDataImage(SoXipDataImage **mXipImage, SbMatrix &volModelMatrix, int bufDimension[3]);
	void updateXipDataImage(SoXipDataImage* mXipImage, SbXipImage *image, double _begin_Pos[3], int bufDimension[3], double imgPosition[3], int imgDimension[3], double imgSpacing[3]);

	void resizeVec(SbVec3f &vec, float len);
};

#endif // !defined(AFX_SoAlignVolumeMask_H__353923CC_3ABE_43A3_9C56_7CAC0DB1F90C__INCLUDED_)
