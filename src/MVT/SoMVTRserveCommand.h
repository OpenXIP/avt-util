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
*	@file    SoMVTRserveCommand.h
*	@brief   Rserve interactive command interface
*	@author  Jie Zheng
**/

#if !defined(AFX_SoMVTRserveCommand_H__351767FB_3AWE_43A3_9C67_7CAC0DB3D90C__INCLUDED_)
#define AFX_SoMVTRserveCommand_H__351767FB_3AWE_43A3_9C67_7CAC0DB3D90C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Inventor/Fields/SoSFString.h"
#include "Inventor/Engines/SoSubEngine.h"
#include "Inventor/fields/SoSFBool.h"
#include "Inventor/fields/SoSFTrigger.h"
#include "Inventor/fields/SoSFInt32.h"

class __declspec(dllexport) SoMVTRserveCommand :
	public SoEngine
{
	SO_ENGINE_HEADER( SoMVTRserveCommand);

public:
	SoMVTRserveCommand(void);
	static void initClass();

	//fields
	SoSFInt32	port;
	SoSFTrigger stop;

	SoEngineOutput output; // SoSFBool

private:
	~SoMVTRserveCommand(void);

	virtual void evaluate();
		// Evaluation method

	void inputChanged (SoField* whichField);
	
protected:
	bool status;
	bool shutdownRserve(int nPort);
};

#endif // !defined(AFX_SoMVTRserve_H__351754CC_3AWE_43A3_9C82_7CAC0DB1F90C__INCLUDED_)
