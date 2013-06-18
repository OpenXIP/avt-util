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
*	@file    SoMVTHistogram.h
*	@brief   Histogram R implementation interface
*	@author  Jie Zheng
**/

#pragma once

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/Fields/SoSFEnum.h>
#include <Inventor/Fields/SoSFBool.h>

class SoMVTHistogram : public SoEngine
{
	SO_ENGINE_HEADER(SoMVTHistogram);

public:
	enum Format {
		BMP,
		JPEG,
		PNG
	};

	/// Initialization
	static void	initClass();
	SoMVTHistogram(void);
public:
	SoSFInt32		 port;
	SoMFFloat		 data;
	SoSFString		 x_Label;
	SoSFString		 y_Label;
	SoSFString		 title;

	SoSFBool		 normalCurve;
	SoSFEnum		 format;
	SoSFString		 file;

	SoSFTrigger		 update;

	SoEngineOutput	 ret;

protected:
	/// Destructor
	~SoMVTHistogram(void);

	/// Evaluation
	virtual void			inputChanged (SoField* whichField);
	virtual void			evaluate ();

	bool					updateOutput();
	bool					validateInput();

private:
	bool					nRet;

	bool					plotHistogram();
};
