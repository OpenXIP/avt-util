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
*	@file    SoVolumeMetrics.h
*	@brief   caculate the volume metrics
*	@author  Jie Zheng
**/

#pragma once
#include <Inventor/Fields/SoSFPlane.h>
#include <Inventor/Fields/SoSFFloat.h>
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

class __declspec(dllexport) SoVolumeMetrics : public SoEngine
{
	SO_ENGINE_HEADER(SoVolumeMetrics);

public:
	SoVolumeMetrics(void);
	static void initClass();

	SoXipSFDataImage	inputVolume;
		// Input Image

	SoSFTrigger			update;

	SoEngineOutput		RECIST;
	SoEngineOutput		WHO;
	SoEngineOutput		Volume;

private:
	~SoVolumeMetrics(void);
		// Destructor

	virtual void		evaluate();
		// Evaluation method

	void				calculateVolumeMetris();
	virtual void		inputChanged (SoField* whichField);

protected:
	float				_recist;
	float				_who;
	float				_volume;
};
