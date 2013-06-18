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
*	@file    SoLoadContour.h
*	@brief   load contour from file
*	@author  Jie Zheng
**/

#pragma once

#include <Inventor/Engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/SbString.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class __declspec(dllexport) SoLoadContour : public SoEngine
{
	SO_ENGINE_HEADER( SoLoadContour);

public:
	SoLoadContour(void);
	static void initClass();

	//input
	SoSFString	pointFile;
	SoSFString	indexFile;

	SoSFTrigger	execute;

	//output
	SoEngineOutput points;
	SoEngineOutput coordIndex;

private:
	~SoLoadContour(void);
	virtual void evaluate();
	virtual void inputChanged (SoField* whichField);

private:
	bool loadContour(const char *point, const char *index);
	bool parseContour(const char *input,vector<string>& tokens, string del);
};
