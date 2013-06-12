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
*	@file    SoIAPostprocess.h
*	@brief   Downsample the volume ROI
*	@author  Jie Zheng
**/

#pragma once

# include <xip/inventor/itk/xipivitk.h>
# include <Inventor/engines/SoSubEngine.h>
# include <xip/inventor/itk/SoItkSFDataImage.h>
# include <Inventor/fields/SoSFFloat.h>
# include <Inventor/fields/SoSFShort.h>


class SoIAPostprocess:public SoEngine
{

	SO_ENGINE_HEADER(SoIABinaryErode);
public:
	SoIAPostprocess();
	static void initClass();

public:
	SoEngineOutput	Output;			// SoItkSFDataImage
	SoItkSFDataImage	Input1;

	///////////////////
	SoSFShort StartSlice;
	SoSFShort Shrink;
	///////////////////
protected:
	virtual void evaluate();

	SoItkDataImage* mOutput;

	virtual ~SoIAPostprocess();
};
