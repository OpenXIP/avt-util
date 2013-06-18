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
*	@brief   resample the volume data
*	@author  Jie Zheng
**/

#if !defined(AFX_SoResampleVolume_H__35682WEG_3ABE_43SD_9C34_7CAC0DFGF90C__INCLUDED_)
#define AFX_SoResampleVolume_H__35682WEG_3ABE_43SD_9C34_7CAC0DFGF90C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Inventor/Fields/SoSFFloat.h>
#include <Inventor/Fields/SoSFInt32.h>
#include <Inventor/Fields/SoSFUShort.h>
#include <Inventor/Fields/SoSFEnum.h>
#include <Inventor/Fields/SoSFVec3f.h>
#include <Inventor/Engines/SoSubEngine.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoMFInt32.h>

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>


class __declspec(dllexport) SoResampleVolume : public SoEngine
{
	SO_ENGINE_HEADER( SoResampleVolume);

public:
	SoResampleVolume(void);
	static void initClass();

	SoXipSFDataImage	inputVolume;
		// Input Image

	SoSFInt32			factor_x;
	SoSFInt32			factor_y;
	SoSFInt32			factor_z;

	SoEngineOutput outputVolume; // SoXipSFDataImage
		// Output Image

private:
	~SoResampleVolume(void);
		// Destructor

	virtual void evaluate();
		// Evaluation method

	void allocOutputVolume();
	void resampleVolume();

	virtual void inputChanged (SoField* whichField);

protected:
	SoXipDataImage* mXipImage;
		// Data wrapper for the XIP image class
};

#endif // !defined(AFX_SoResampleVolume_H__35682WEG_3ABE_43SD_9C34_7CAC0DFGF90C__INCLUDED_)
