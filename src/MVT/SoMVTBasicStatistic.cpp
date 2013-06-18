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

#include "SoMVTBasicStatistic.h"
#include "RconnectionFunc.h"

SO_ENGINE_SOURCE(SoMVTBasicStatistic);

void SoMVTBasicStatistic::initClass()
{
	SO_ENGINE_INIT_CLASS(SoMVTBasicStatistic, SoEngine, "Engine");
}

SoMVTBasicStatistic::SoMVTBasicStatistic(void)
{
	SO_ENGINE_CONSTRUCTOR(SoMVTBasicStatistic);

	//Initialize the input parameter
	SO_ENGINE_ADD_INPUT( port, (6311) );
	SO_ENGINE_ADD_INPUT( data, (NULL) );

	SO_ENGINE_ADD_INPUT( prob, (0.50f) );

	SO_ENGINE_ADD_INPUT (update, ());

	//set up the output type of the engine
	SO_ENGINE_ADD_OUTPUT( mean, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( std, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( quantile, SoMFFloat );

	fMean = 0;
	fStd = 0;
	fQuantile.clear();
}

SoMVTBasicStatistic::~SoMVTBasicStatistic(void)
{
}

void SoMVTBasicStatistic::inputChanged(SoField *whichField)
{
//	if (whichField == &data || whichField == &prob || whichField == &update)
	if (whichField == &update)
	{
		if (updateOutput())
			enableOutputs(TRUE);
	}
	else
	{
		enableOutputs(FALSE);
	}

}

void SoMVTBasicStatistic::enableOutputs (BOOL flag)
{
	mean.enable (flag);
	std.enable (flag);
	quantile.enable (flag);
}

void SoMVTBasicStatistic::evaluate()
{
	SO_ENGINE_OUTPUT(mean, SoSFFloat, setValue(fMean));
	SO_ENGINE_OUTPUT(std, SoSFFloat, setValue(fStd));

	SO_ENGINE_OUTPUT(quantile, SoMFFloat, setNum(fQuantile.size()));
	if(fQuantile.size()>0)
		SO_ENGINE_OUTPUT(quantile, SoMFFloat, setValues(0, fQuantile.size(), (float*)&(fQuantile[0])));
}

bool SoMVTBasicStatistic::updateOutput()
{
	if (data.getNum() <= 0)
		return FALSE;

	int _port = port.getValue();
	int ret = createConnect(_port);
    if (ret != 0) 
	{
		// print the value
		SoDebugError::postInfo("SoMVTBasicStatistic:", "unable to connect Rserve - error: %d", ret);
		return FALSE;
    }
   
	int nSize = data.getNum();
	double * _data = new double[nSize];
	for (int i = 0; i < nSize; i++)
		_data[i] = data[i];

	int nNum = 1;
	double *_output = new double[nNum];

	int nRet = 0;

	char expression[256];
	char *variable = "data";

	char *cmd = "mean";
	sprintf_s(expression, "%s(%s)", cmd, variable);
	nRet = evalExpress(variable, _data, nSize, expression, _output, nNum);
	if (nRet > 0)
		fMean = _output[0];
	else
		SoDebugError::postInfo("SoMVTBasicStatistic:", "error in calculating mean");

	cmd = "sd";
	sprintf_s(expression, "%s(%s)", cmd, variable);
	nRet = evalExpress(variable, _data, nSize, expression, _output, nNum);
	if (nRet > 0)
		fStd = _output[0];
	else
		SoDebugError::postInfo("SoMVTBasicStatistic:", "error in calculating sd");

	delete [] _output;
	_output = NULL;

	nNum = prob.getNum();
	if (nNum <= 0)
		return FALSE;

	fQuantile.clear();
	_output = new double[nNum];

	char buf[256];
	sprintf_s(buf, "%.3f", prob[0]);

	for (int i = 1; i < nNum; i++)
	{
		char temp[8];
		float fValue = prob[i];
		sprintf_s(temp, ",%.3f", fValue);
		strcat_s(buf, temp);
	}

	cmd = "quantile";
	sprintf_s(expression, "%s(%s, prob=c(%s))",cmd, variable, buf); 
	nRet = evalExpress(variable, _data, nSize, expression, _output, nNum);
	if (nRet == nNum)
	{

		for (int i = 0; i < nNum; i++)
			fQuantile.push_back(_output[i]);
	}
	else
		SoDebugError::postInfo("SoMVTBasicStatistic:", "error in calculating quantile");

	delete [] _data;
	_data = NULL;

 	return TRUE;
}
