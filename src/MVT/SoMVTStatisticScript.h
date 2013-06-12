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
*	@file    SoMVTStatisticScript.h
*	@brief   User-defined R script interface
*	@author  Jie Zheng
**/

#if !defined(AFX_SoMVTStatisticScript_H__3515469GC_3AWE_43A3_9C82_7CAC0DB1F90C__INCLUDED_)
#define AFX_SoMVTStatisticScript_H__3515469GC_3AWE_43A3_9C82_7CAC0DB1F90C__INCLUDED_

#pragma once

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFTrigger.h>

class SoMVTStatisticScript : public SoEngine
{
	SO_ENGINE_HEADER(SoMVTStatisticScript);

public:
	/// Initialization
	static void	initClass();
	SoMVTStatisticScript(void);

public:
	SoSFInt32		 port;
	SoMFFloat		 data;
	SoSFString		 script;
	SoSFInt32		 size;

	SoSFTrigger		 update;

	SoEngineOutput	 output;
	SoEngineOutput	 ret;

protected:
	/// Destructor
	~SoMVTStatisticScript(void);

	/// Evaluation
	virtual void			inputChanged (SoField* whichField);
	virtual void			evaluate ();

	void					enableOutputs (BOOL flag);
	bool					updateOutput();

	bool					checkScript(const char* strScript, char *variable);
private:
	int				nRet;
	vector<float>	fOutput;
};

#endif // !defined(AFX_SoMVTStatisticScript_H__3515469GC_3AWE_43A3_9C82_7CAC0DB1F90C__INCLUDED_)
