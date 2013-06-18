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
*	@file    SoMVTAnova.h
*	@brief   ANOVA R implementation interface
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

class SoMVTAnova : public SoEngine
{
	SO_ENGINE_HEADER(SoMVTAnova);

public:
	/// Initialization
	static void	initClass();
	SoMVTAnova(void);

public:
	SoSFInt32		 port;
	SoMFFloat		 data0;
	SoMFFloat		 data1;
	SoMFFloat		 data2;
	SoMFFloat		 data3;
	SoMFFloat		 data4;
	SoMFFloat		 data5;
	SoMFFloat		 data6;
	SoMFFloat		 data7;

	SoSFTrigger		 update;

	SoEngineOutput	 df;
	SoEngineOutput	 sum;
	SoEngineOutput	 mean;
	SoEngineOutput	 f_value;
	SoEngineOutput	 p_value;

protected:
	/// Destructor
	~SoMVTAnova(void);
	/// Evaluation
	virtual void			inputChanged (SoField* whichField);
	virtual void			evaluate ();

	bool					validateInput();
	bool					calculateOutput();
	void					updateOutput();
	bool					assignVariable(SoMFFloat &data, vector<double> &fInput);
	bool					getCalculation(char *cmd, vector<float> &fOutput);

private:
	vector<float>	fDf;
	vector<float>	fSum;
	vector<float>	fMean;
	vector<float>	fFvalue;
	vector<float>	fPvalue;
};
