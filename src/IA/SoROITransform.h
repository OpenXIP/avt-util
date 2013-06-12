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
*	@file    SoROITransform.h
*	@brief   calculate the ROI volume offset to the original volume
*	@author  Jie Zheng
**/

#pragma once

#include <Inventor/Engines/SoSubEngine.h>
#include <Inventor/Fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/Fields/SoSFInt32.h>

class __declspec(dllexport) SoROITransform :
	public SoEngine
{
	SO_ENGINE_HEADER( SoROITransform );

public:
	SoROITransform(void);
	static void initClass();

	SoSFMatrix	volModelMatrix;

	SoSFMatrix	roiModelMatrix;

	SoEngineOutput	scale;
	SoEngineOutput	translate;

public:
	~SoROITransform(void);

	virtual void evaluate();
	virtual void inputChanged(SoField* whichField);

};
