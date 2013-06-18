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

#include <string>
#include <vector>

using namespace std;

#include "SoMVTStatisticScript.h"
#include "RconnectionFunc.h"

SO_ENGINE_SOURCE(SoMVTStatisticScript);

void SoMVTStatisticScript::initClass()
{
	SO_ENGINE_INIT_CLASS(SoMVTStatisticScript, SoEngine, "Engine");
}

SoMVTStatisticScript::SoMVTStatisticScript(void)
{
	SO_ENGINE_CONSTRUCTOR(SoMVTStatisticScript);

	//Initialize the input parameter
	SO_ENGINE_ADD_INPUT( port, (6311) );
	SO_ENGINE_ADD_INPUT( data, (NULL) );
	SO_ENGINE_ADD_INPUT( size, (1) );
	SO_ENGINE_ADD_INPUT( script, ("") );

	SO_ENGINE_ADD_INPUT (update, ());

	//set up the output type of the engine
	SO_ENGINE_ADD_OUTPUT( output, SoMFFloat );
	SO_ENGINE_ADD_OUTPUT( ret, SoSFInt32 );

	fOutput.clear();
}

SoMVTStatisticScript::~SoMVTStatisticScript(void)
{
}

void SoMVTStatisticScript::inputChanged(SoField *whichField)
{
//	if (whichField == &data || whichField == &update)
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

void SoMVTStatisticScript::enableOutputs (BOOL flag)
{
	output.enable (flag);
	ret.enable (flag);
}

void SoMVTStatisticScript::evaluate()
{
	SO_ENGINE_OUTPUT(ret, SoSFInt32, setValue(nRet));
	SO_ENGINE_OUTPUT(output, SoMFFloat, setNum(fOutput.size()));
	if(fOutput.size()>0)
		SO_ENGINE_OUTPUT(output, SoMFFloat, setValues(0, fOutput.size(), (float*)&(fOutput[0])));
}

bool SoMVTStatisticScript::updateOutput()
{
	char *variable = "data";
	if (data.getNum() <= 0)
		return FALSE;
	if (script.getValue().getLength() <= 0 || size.getValue() <= 0)
		return FALSE;

	const char *cmd = script.getValue().getString();
	if (checkScript(cmd, variable) == 0)
	{
		SoDebugError::postInfo("SoMVTStatisticScript:", "unknown statistics script");
		return FALSE;
	}

//	SoDebugError::postInfo("SoMVTStatisticScript:", cmd);

	int _port = port.getValue();
	int ret = createConnect(_port);
    if (ret != 0) 
	{
		// print the value
		SoDebugError::postInfo("SoMVTStatisticScript:", "unable to connect Rserve - error: %d", ret);
		return FALSE;
    }
   
	int nSize = data.getNum();
	double * _data = new double[nSize];
	for (int i = 0; i < nSize; i++)
		_data[i] = data[i];

	fOutput.clear();
	int nNum = size.getValue();
	double *_output = new double[nNum];

	string strBuf(cmd);

	char expression[512];
	sprintf_s(expression, "%s", strBuf.c_str());
	nRet = evalExpress(variable, _data, nSize, expression, _output, nNum);
	if (nRet <= nNum)
	{
		for (int i = 0; i < nRet; i++)
			fOutput.push_back(_output[i]);
	}
	else
		SoDebugError::postInfo("SoMVTStatisticScript:", "error in calculating script");

	delete [] _data;
	_data = NULL;

	return TRUE;
}

bool SoMVTStatisticScript::checkScript(const char* strScript, char *variable)
{
	string strBuf(strScript);

	string::size_type loc = strBuf.find(variable);
	if (loc != string::npos)
		return TRUE;

	return FALSE;
}

