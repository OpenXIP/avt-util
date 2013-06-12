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
*	@file    SoMap2ImagePt.h
*	@brief   convert the 3D points to 2D image points
*	@author  Jie Zheng
**/

#pragma once
#include <Inventor/Engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/Fields/SoMFVec3f.h>
#include <Inventor/Fields/SoMFInt32.h>
#include <Inventor/Fields/SoSFInt32.h>
#include <Inventor/Fields/SoSFVec3f.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFBool.h>

#include <xip/inventor/dicom/SoXipMFDataDicom.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>

   class __declspec(dllexport) SoMap2ImagePt : public SoEngine
{
	SO_ENGINE_HEADER( SoMap2ImagePt );

public:
	SoMap2ImagePt(void);
	static void initClass();

	//input
	SoXipMFDataDicom	refInput;
	SoMFVec3f			coordinates;

	//output
	SoEngineOutput		points;
	SoEngineOutput		sopInstanceUID;
	SoEngineOutput		status;

private:
	~SoMap2ImagePt(void);

	virtual void evaluate();
		// Evaluation method
	virtual void inputChanged (SoField* whichField);

protected:
	void updateOutput();
	bool getMappingPoint(int pt[2], SbString &uid,  SbVec3f point);
};
