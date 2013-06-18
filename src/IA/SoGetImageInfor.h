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
*	@file    SoGetImageInfor.h
*	@brief   get the dicom informations according to image instanceUID
*	@author  Jie Zheng
**/

#pragma once
#include <Inventor/Engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/Fields/SoMFVec3f.h>
#include <Inventor/Fields/SoSFVec3f.h>

#include <xip/inventor/dicom/SoXipMFDataDicom.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>


class __declspec(dllexport) SoGetImageInfor : public SoEngine
{
	SO_ENGINE_HEADER( SoGetImageInfor );

public:
	SoGetImageInfor(void);
	static void initClass();

	//input
	SoXipMFDataDicom	refInput;
	SoSFString			imageInstanceUID;

	//output
	SoEngineOutput		imagePosition;
	SoEngineOutput		imageSpacing;

private:
	~SoGetImageInfor(void);

	virtual void evaluate();
		// Evaluation method
	virtual void inputChanged (SoField* whichField);

protected:
	void updateOutput();
	bool getImageInfor(SbString &uid);
};
