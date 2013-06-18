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
*	@file    SoIAParseString.h
*	@brief   Parse the string in the given pattern
*	@author  Jie Zheng
**/

#pragma once

#include <Inventor/Fields/SoMFVec3f.h>
#include <Inventor/Fields/SoSFVec3f.h>
#include <Inventor/Engines/SoSubEngine.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFNode.h>
#include <xip/inventor/overlay/SoXipShape.h>

class __declspec(dllexport) SoIAParseString : SoEngine
{
public:
	SO_ENGINE_HEADER( SoIAAttachPoints );

	// input
	SoSFString	seperator;
	SoSFString	string;

	SoSFInt32	index;

	//output
	SoEngineOutput output;

public:
	SoIAParseString(void);
	static void initClass();

protected:
	~SoIAParseString(void);
	virtual void inputChanged(SoField *whichField);
	virtual void evaluate();
};
