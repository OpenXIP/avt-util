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
*	@file    SoMVTMultipleRegression.h
*	@brief   Multiple Regression R implementation interface
*	@author  Jie Zheng
**/

#pragma once

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <vector>

using namespace std;

class SoMVTMultipleRegression : public SoEngine
{
	SO_ENGINE_HEADER(SoMVTMultipleRegression);

public:
	/// Initialization
	static void	initClass();
	SoMVTMultipleRegression(void);

public:
	SoSFInt32		 port;
	SoMFFloat		 dependentY;
	SoMFFloat		 variable0;
	SoMFFloat		 variable1;
	SoMFFloat		 variable2;
	SoMFFloat		 variable3;
	SoMFFloat		 variable4;
	SoMFFloat		 variable5;
	SoMFFloat		 variable6;
	SoMFFloat		 variable7;

	SoSFTrigger		 update;

	SoEngineOutput	 residual;
	SoEngineOutput	 estimate;
	SoEngineOutput	 std;
	SoEngineOutput	 f_value;
	SoEngineOutput	 p_value;

protected:
	/// Destructor
	~SoMVTMultipleRegression(void);

	/// Evaluation
	virtual void			inputChanged (SoField* whichField);
	virtual void			evaluate ();

	bool					validateInput();
	bool					calculateOutput();
	void					updateOutput();
	bool					assignVariable(SoMFFloat &data, vector<double> &fInput);
	bool					getCalculation(char *cmd, vector<float> &fOutput);

private:
	vector<float>	fResidual;
	vector<float>	fEstimate;
	vector<float>	fStd;
	vector<float>	fFvalue;
	vector<float>	fPvalue;
};
