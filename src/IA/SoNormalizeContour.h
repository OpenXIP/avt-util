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
*	@file    SoNormalizeContour.h
*	@brief   calculate the ROI of the volume mask from the input contour
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

class __declspec(dllexport) SoNormalizeContour : public SoEngine
{
	SO_ENGINE_HEADER( SoNormalizeContour);

public:
	SoNormalizeContour(void);
	static void initClass();

	//input
	SoSFVec3f	voxelPosition;
	SoMFVec3f	voxelDirection;
	SoSFVec3f	voxelSpacing;
	SoSFInt32	width;
	SoSFInt32	height;
	SoSFInt32	depth;
	SoMFVec2f	point;
	SoMFInt32	coordIndex;
	SoSFTrigger	execute;

	//output
	SoEngineOutput	modelMatrix;
	SoEngineOutput	maskWidth;
	SoEngineOutput	maskHeight;
	SoEngineOutput	maskDepth;
	SoEngineOutput	pointList;
	SoEngineOutput	pointIndex;

private:
	~SoNormalizeContour(void);
	virtual void evaluate();
	virtual void inputChanged (SoField* whichField);

private:
	bool validateInputs();
	bool buildModelmatrix(SbVec3f &_position, int _width, int _height, int _depth);
	bool normailzePoints(SbVec3f &position, int &_width, int &_height, int &_depth);
};
