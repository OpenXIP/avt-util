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

#include "RconnectionFunc.h"
#include "SoMVTHistogram.h"
#include <string>
#include <io.h>

using namespace std;

SO_ENGINE_SOURCE(SoMVTHistogram);

void SoMVTHistogram::initClass()
{
	SO_ENGINE_INIT_CLASS(SoMVTHistogram, SoEngine, "Engine");
}

SoMVTHistogram::SoMVTHistogram(void)
{
	SO_ENGINE_CONSTRUCTOR(SoMVTBasicPlot);

	//Initialize the input parameter
	SO_ENGINE_ADD_INPUT( port, (6311) );
	SO_ENGINE_ADD_INPUT( data, (NULL) );
	SO_ENGINE_ADD_INPUT( x_Label, ("") );
	SO_ENGINE_ADD_INPUT( y_Label, ("") );
	SO_ENGINE_ADD_INPUT( title, ("") );

	SO_ENGINE_ADD_INPUT( format, (PNG) );
	SO_ENGINE_DEFINE_ENUM_VALUE(Format, BMP);
	SO_ENGINE_DEFINE_ENUM_VALUE(Format, JPEG);
	SO_ENGINE_DEFINE_ENUM_VALUE(Format, PNG);
	SO_ENGINE_SET_SF_ENUM_TYPE(format, Format);

	SO_ENGINE_ADD_INPUT( normalCurve, (TRUE) );

	SO_ENGINE_ADD_INPUT( file, ("") );
	SO_ENGINE_ADD_INPUT (update, ());

	//set up the output type of the engine
	SO_ENGINE_ADD_OUTPUT( ret, SoSFBool );

	nRet = FALSE;
}

SoMVTHistogram::~SoMVTHistogram(void)
{
}

void SoMVTHistogram::inputChanged(SoField *whichField)
{
	if (whichField == &update)
	{
		if (updateOutput())
			nRet = TRUE;
	}
	else
	{
		nRet = FALSE;
	}

}

void SoMVTHistogram::evaluate()
{
	SO_ENGINE_OUTPUT(ret, SoSFBool, setValue(nRet));
}

bool SoMVTHistogram::validateInput()
{
	const char * _file = file.getValue().getString();
	if (strlen(_file) == 0)
	{
		SoDebugError::postInfo("SoMVTHistogram:", "can not plot to file");
		return FALSE;
	}

	if (data.getNum() <= 1)
	{
		SoDebugError::postInfo("SoMVTHistogram:", "can not get input values");
		return FALSE;
	}

	return true;
}

bool SoMVTHistogram::updateOutput()
{
	bool ret = true;
	if (!validateInput())
		return false;

	int _port = port.getValue();
	int val = createConnect(_port);
    if (val != 0) 
	{
		// print the value
		SoDebugError::post("SoMVTHistogram:", "unable to connect Rserve - error: %d", val);
		return false;
    }

	int num = data.getNum();
	double * _data = new double[num];
	for (int i = 0; i < num; i++)
		_data[i] = data[i];

	//assign data
	char *_variable = "val";
	assignData(_variable, _data, num);

	char cmd[128];
	switch(format.getValue())
	{
	case BMP:
		sprintf_s(cmd, "bmp(file=\"%s\")", file.getValue().getString());
		break;

	case JPEG:
		sprintf_s(cmd, "jpeg(file=\"%s\")", file.getValue().getString());
		break;

	case PNG:
		sprintf_s(cmd, "png(file=\"%s\")", file.getValue().getString());
		break;
	}

	//open R deveice to plot
	if (ret = executeCmd(cmd))
	{
		ret = plotHistogram();

		//close device
		if (ret)
			ret = executeCmd("dev.off()");
	}
	else
		SoDebugError::post("SoMVTHistogram - error:", cmd);

	delete [] _data;
	_data = NULL;

	return ret;
}

bool SoMVTHistogram::plotHistogram()
{
	try {
		//set plot parameters
		executeCmd("opar<-par();par(mar=c(4, 4, 2.5, 2))");

		char expression[256];

		//title
		const char* strTitle = title.getValue().getString();

		sprintf_s(expression, "hist(val, main=\"%s\", xlab=\"\")", strTitle);
		executeCmd(expression);

		//label
		const char* str = NULL;
		str = x_Label.getValue().getString();
		if (strlen(str) > 0)
		{
			sprintf_s(expression, "mtext(\"%s\", side=1, line=2, cex=1, font=3)", str);
			executeCmd(expression);
		}

		//str = y_Label.getValue().getString();
		//if (strlen(str) > 0)
		//{
		//	sprintf_s(expression, "mtext(\"%s\", side=2, line=2, cex=1, font=3)", str);
		//	executeCmd(expression);
		//}

		if (normalCurve.getValue())
		{
			executeCmd("x<-(min(val):max(val))");
			executeCmd("lines(x, dnorm(x, mean(val), sd(val)), col=\"red\")");
		}

		//restore plot setting
		executeCmd("par(opar)");
	}
	catch(char *cmd)
	{
		SoDebugError::post("MVTStatistic - plotScatter error:", cmd);

		return false;
	}

	return true;
}
