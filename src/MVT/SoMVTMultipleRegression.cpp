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

/* author Jie Zheng */

#include "SoMVTMultipleRegression.h"
#include "RconnectionFunc.h"

SO_ENGINE_SOURCE(SoMVTMultipleRegression);

void SoMVTMultipleRegression::initClass()
{
	SO_ENGINE_INIT_CLASS(SoMVTMultipleRegression, SoEngine, "Engine");
}

SoMVTMultipleRegression::SoMVTMultipleRegression(void)
{
	SO_ENGINE_CONSTRUCTOR(SoMVTMultipleRegression);

	//Initialize the input parameter
	SO_ENGINE_ADD_INPUT( port, (6311) );
	SO_ENGINE_ADD_INPUT( dependentY, (NULL) );
	SO_ENGINE_ADD_INPUT( variable0, (NULL) );
	SO_ENGINE_ADD_INPUT( variable1, (NULL) );
	SO_ENGINE_ADD_INPUT( variable2, (NULL) );
	SO_ENGINE_ADD_INPUT( variable3, (NULL) );
	SO_ENGINE_ADD_INPUT( variable4, (NULL) );
	SO_ENGINE_ADD_INPUT( variable5, (NULL) );
	SO_ENGINE_ADD_INPUT( variable6, (NULL) );
	SO_ENGINE_ADD_INPUT( variable7, (NULL) );


	SO_ENGINE_ADD_INPUT (update, ());

	//set up the output type of the engine
	SO_ENGINE_ADD_OUTPUT( residual, SoMFFloat );
	SO_ENGINE_ADD_OUTPUT( estimate, SoMFFloat );
	SO_ENGINE_ADD_OUTPUT( std, SoMFFloat );
	SO_ENGINE_ADD_OUTPUT( f_value, SoMFFloat );
	SO_ENGINE_ADD_OUTPUT( p_value, SoMFFloat );

	fResidual.clear();
	fEstimate.clear();
	fStd.clear();
	fFvalue.clear();
	fPvalue.clear();
}

SoMVTMultipleRegression::~SoMVTMultipleRegression(void)
{
}

void SoMVTMultipleRegression::inputChanged(SoField *whichField)
{
	if (whichField == &update)
		calculateOutput();
}

void SoMVTMultipleRegression::evaluate()
{
}

void SoMVTMultipleRegression::updateOutput()
{
	SO_ENGINE_OUTPUT(residual, SoMFFloat, setNum(fResidual.size()));
	if(fResidual.size()>0)
		SO_ENGINE_OUTPUT(residual, SoMFFloat, setValues(0, fResidual.size(), (float*)&(fResidual[0])));

	SO_ENGINE_OUTPUT(estimate, SoMFFloat, setNum(fEstimate.size()));
	if(fEstimate.size()>0)
		SO_ENGINE_OUTPUT(estimate, SoMFFloat, setValues(0, fEstimate.size(), (float*)&(fEstimate[0])));

	SO_ENGINE_OUTPUT(std, SoMFFloat, setNum(fStd.size()));
	if(fStd.size()>0)
		SO_ENGINE_OUTPUT(std, SoMFFloat, setValues(0, fStd.size(), (float*)&(fStd[0])));

	SO_ENGINE_OUTPUT(f_value, SoMFFloat, setNum(fFvalue.size()));
	if(fFvalue.size()>0)
		SO_ENGINE_OUTPUT(f_value, SoMFFloat, setValues(0, fFvalue.size(), (float*)&(fFvalue[0])));

	SO_ENGINE_OUTPUT(p_value, SoMFFloat, setNum(fPvalue.size()));
	if(fPvalue.size()>0)
		SO_ENGINE_OUTPUT(p_value, SoMFFloat, setValues(0, fPvalue.size(), (float*)&(fPvalue[0])));
}

bool SoMVTMultipleRegression::validateInput()
{
	if (dependentY.getNum() < 3)
		return false;

	return true;
}

bool SoMVTMultipleRegression::assignVariable(SoMFFloat &data, vector<double> &fInput)
{
	int len = data.getNum();
	if (len > 3)
	{
		fInput.clear();
		for (int i = 0; i < len; i++)
			fInput.push_back(data[i]);

		return true;
	}

	return false;
}

bool SoMVTMultipleRegression::getCalculation(char *cmd, vector<float> &fOutput)
{
	int nNum = 0;

	fOutput.clear();
	int nRet = getEval(cmd, fOutput);
	if (nRet <= 0)
		SoDebugError::postInfo("SoMVTMultipleRegression:", "error in calculating output ", cmd);

	return true;
}

bool SoMVTMultipleRegression::calculateOutput()
{
	if (!validateInput())
		return false;

	int _port = port.getValue();
	int ret = createConnect(_port);
    if (ret != 0) 
	{
		// print the value
		SoDebugError::postInfo("SoMVTMultipleRegression:", "unable to connect Rserve - error: %d", ret);
		return false;
    }

	char strbuffer0[256];
	char strbuffer1[256];
	char expression[256];
   
	vector<double> y;
	assignVariable(dependentY, y);

	assignDataset("Y", y);
	strcpy(strbuffer0, "Y,");
	strcpy(strbuffer1, "Y~");

	vector<double> x0;
	if(assignVariable(variable0, x0))
	{
		assignDataset("X0", x0);
		strcat(strbuffer0, "X0,");
		strcat(strbuffer1, "X0+");
	}

	vector<double> x1;
	if(assignVariable(variable1, x1))
	{
		assignDataset("X1", x1);
		strcat(strbuffer0, "X1,");
		strcat(strbuffer1, "X1+");
	}

	vector<double> x2;
	if(assignVariable(variable2, x2))
	{
		assignDataset("X2", x2);
		strcat(strbuffer0, "X2,");
		strcat(strbuffer1, "X2+");
	}

	vector<double> x3;
	if(assignVariable(variable3, x3))
	{
		assignDataset("X3", x3);
		strcat(strbuffer0, "X3,");
		strcat(strbuffer1, "X3+");
	}

	vector<double> x4;
	if(assignVariable(variable4, x4))
	{
		assignDataset("X4", x4);
		strcat(strbuffer0, "X4,");
		strcat(strbuffer1, "X4+");
	}

	vector<double> x5;
	if(assignVariable(variable5, x5))
	{
		assignDataset("X05", x5);
		strcat(strbuffer0, "X5,");
		strcat(strbuffer1, "X5+");
	}

	vector<double> x6;
	if(assignVariable(variable6, x6))
	{
		assignDataset("X6", x6);
		strcat(strbuffer0, "X6,");
		strcat(strbuffer1, "X6+");
	}

	vector<double> x7;
	if(assignVariable(variable7, x7))
	{
		assignDataset("X7", x7);
		strcat(strbuffer0, "X7,");
		strcat(strbuffer1, "X7+");
	}

	//set data frame
	strbuffer0[strlen(strbuffer0) - 1] = '\0';
	sprintf_s(expression, "val<-data.frame(%s)", strbuffer0);
	if (!executeCmd(expression))
		SoDebugError::postInfo("SoMVTMultipleRegression:", "error in setting data frame");

	//multiple regression
	strbuffer1[strlen(strbuffer1) - 1] = '\0';
	sprintf_s(expression, "m<-lm(formula=%s, data=val)", strbuffer1);
	if (!executeCmd(expression))
		SoDebugError::postInfo("SoMVTMultipleRegression:", "error in multiple regression");

	getCalculation("summary(m)[[3]]", fResidual);
	getCalculation("summary(m)[[4]][,1]", fEstimate);
	getCalculation("summary(m)[[4]][,2]", fStd);
	getCalculation("summary(m)[[4]][,3]", fFvalue);
	getCalculation("summary(m)[[4]][,4]", fPvalue);

	updateOutput();

	return true;
}
