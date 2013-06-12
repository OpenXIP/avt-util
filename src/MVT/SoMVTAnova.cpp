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

#include "SoMVTAnova.h"
#include "RconnectionFunc.h"

SO_ENGINE_SOURCE(SoMVTAnova);

void SoMVTAnova::initClass()
{
	SO_ENGINE_INIT_CLASS(SoMVTAnova, SoEngine, "Engine");
}

SoMVTAnova::SoMVTAnova(void)
{
	SO_ENGINE_CONSTRUCTOR(SoMVTAnova);

	//Initialize the input parameter
	SO_ENGINE_ADD_INPUT( port, (6311) );
	SO_ENGINE_ADD_INPUT( data0, (NULL) );
	SO_ENGINE_ADD_INPUT( data1, (NULL) );
	SO_ENGINE_ADD_INPUT( data2, (NULL) );
	SO_ENGINE_ADD_INPUT( data3, (NULL) );
	SO_ENGINE_ADD_INPUT( data4, (NULL) );
	SO_ENGINE_ADD_INPUT( data5, (NULL) );
	SO_ENGINE_ADD_INPUT( data6, (NULL) );
	SO_ENGINE_ADD_INPUT( data7, (NULL) );


	SO_ENGINE_ADD_INPUT (update, ());

	//set up the output type of the engine
	SO_ENGINE_ADD_OUTPUT( df, SoMFFloat );
	SO_ENGINE_ADD_OUTPUT( sum, SoMFFloat );
	SO_ENGINE_ADD_OUTPUT( mean, SoMFFloat );
	SO_ENGINE_ADD_OUTPUT( f_value, SoMFFloat );
	SO_ENGINE_ADD_OUTPUT( p_value, SoMFFloat );

	fDf.clear();
	fSum.clear();
	fMean.clear();
	fFvalue.clear();
	fPvalue.clear();
}

SoMVTAnova::~SoMVTAnova(void)
{
}

void SoMVTAnova::inputChanged(SoField *whichField)
{
	if (whichField == &update)
		calculateOutput();
}


void SoMVTAnova::evaluate()
{
}

void SoMVTAnova::updateOutput()
{
	SO_ENGINE_OUTPUT(df, SoMFFloat, setNum(fDf.size()));
	if(fDf.size()>0)
		SO_ENGINE_OUTPUT(df, SoMFFloat, setValues(0, fDf.size(), (float*)&(fDf[0])));

	SO_ENGINE_OUTPUT(sum, SoMFFloat, setNum(fSum.size()));
	if(fSum.size()>0)
		SO_ENGINE_OUTPUT(sum, SoMFFloat, setValues(0, fSum.size(), (float*)&(fSum[0])));

	SO_ENGINE_OUTPUT(mean, SoMFFloat, setNum(fMean.size()));
	if(fMean.size()>0)
		SO_ENGINE_OUTPUT(mean, SoMFFloat, setValues(0, fMean.size(), (float*)&(fMean[0])));

	SO_ENGINE_OUTPUT(f_value, SoMFFloat, setNum(fFvalue.size()));
	if(fFvalue.size()>0)
		SO_ENGINE_OUTPUT(f_value, SoMFFloat, setValues(0, fFvalue.size(), (float*)&(fFvalue[0])));

	SO_ENGINE_OUTPUT(p_value, SoMFFloat, setNum(fPvalue.size()));
	if(fPvalue.size()>0)
		SO_ENGINE_OUTPUT(p_value, SoMFFloat, setValues(0, fPvalue.size(), (float*)&(fPvalue[0])));
}

bool SoMVTAnova::validateInput()
{
	if (data0.getNum() < 3)
		return false;

	return true;
}

bool SoMVTAnova::assignVariable(SoMFFloat &data, vector<double> &fInput)
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

bool SoMVTAnova::getCalculation(char *cmd, vector<float> &fOutput)
{
	int nNum = 0;

	fOutput.clear();
	int nRet = getEval(cmd, fOutput);
	if (nRet <= 0)
		SoDebugError::postInfo("SoMVTAnova:", "error in calculating output ", cmd);

	return true;
}

bool SoMVTAnova::calculateOutput()
{
	if (!validateInput())
		return false;

	int _port = port.getValue();
	int ret = createConnect(_port);
    if (ret != 0) 
	{
		// print the value
		SoDebugError::postInfo("SoMVTAnova:", "unable to connect Rserve - error: %d", ret);
		return false;
    }

	char strbuffer0[256];
	char strbuffer1[256];
	char expression[256];
   
	char buf[16];
	vector<double> x0;
	assignVariable(data0, x0);
	int size = x0.size();

	assignDataset("X0", x0);
	strcpy(strbuffer0, "X0,");

	sprintf_s(buf, "rep(1, %d),", size);
	strcpy(strbuffer1, buf);

	vector<double> x1;
	if(assignVariable(data1, x1))
	{
		assignDataset("X1", x1);
		strcat(strbuffer0, "X1,");

		sprintf_s(buf, "rep(2, %d),", size);
		strcat(strbuffer1, buf);
	}

	vector<double> x2;
	if(assignVariable(data2, x2))
	{
		assignDataset("X2", x2);
		strcat(strbuffer0, "X2,");

		sprintf_s(buf, "rep(3, %d),", size);
		strcat(strbuffer1, buf);
	}

	vector<double> x3;
	if(assignVariable(data3, x3))
	{
		assignDataset("X3", x3);
		strcat(strbuffer0, "X3,");

		sprintf_s(buf, "rep(4, %d),", size);
		strcat(strbuffer1, buf);
	}

	vector<double> x4;
	if(assignVariable(data4, x4))
	{
		assignDataset("X4", x4);
		strcat(strbuffer0, "X4,");

		sprintf_s(buf, "rep(5, %d),", size);
		strcat(strbuffer1, buf);
	}

	vector<double> x5;
	if(assignVariable(data5, x5))
	{
		assignDataset("X5", x5);
		strcat(strbuffer0, "X5,");

		sprintf_s(buf, "rep(6, %d),", size);
		strcat(strbuffer1, buf);
	}

	vector<double> x6;
	if(assignVariable(data6, x6))
	{
		assignDataset("X6", x6);
		strcat(strbuffer0, "X6,");

		sprintf_s(buf, "rep(7, %d),", size);
		strcat(strbuffer1, buf);
	}

	vector<double> x7;
	if(assignVariable(data7, x7))
	{
		assignDataset("X7", x7);
		strcat(strbuffer0, "X7,");

		sprintf_s(buf, "rep(8, %d),", size);
		strcat(strbuffer1, buf);
	}

	//set data frame
	strbuffer0[strlen(strbuffer0) - 1] = '\0';
	strbuffer1[strlen(strbuffer1) - 1] = '\0';
	sprintf_s(expression, "val<-data.frame(input=c(%s), level<-factor(c(%s)))", strbuffer0, strbuffer1);
	if (!executeCmd(expression))
		SoDebugError::postInfo("SoMVTAnova:", "error in setting data frame");

	//ANOVA
	if (!executeCmd("m<-aov(input~level,data=val)"))
		SoDebugError::postInfo("SoMVTAnova:", "error in ANOVA");

	//summary
	if (!executeCmd("ret<-summary(m)[[1]]"))
		SoDebugError::postInfo("SoMVTAnova:", "error in summary");

	getCalculation("ret$Df", fDf);
	getCalculation("ret$Sum", fSum);
	getCalculation("ret$Mean", fMean);
	getCalculation("ret$F", fFvalue);
	getCalculation("ret$Pr", fPvalue);

	updateOutput();
	return true;
}
