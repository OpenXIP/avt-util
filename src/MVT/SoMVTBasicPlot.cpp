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
#include <io.h>
using namespace std;

#include "RconnectionFunc.h"
#include "SoMVTBasicPlot.h"

SO_ENGINE_SOURCE(SoMVTBasicPlot);

void SoMVTBasicPlot::initClass()
{
	SO_ENGINE_INIT_CLASS(SoMVTBasicPlot, SoEngine, "Engine");
}

SoMVTBasicPlot::SoMVTBasicPlot(void)
{
	SO_ENGINE_CONSTRUCTOR(SoMVTBasicPlot);

	//Initialize the input parameter
	SO_ENGINE_ADD_INPUT( port, (6311) );
	SO_ENGINE_ADD_INPUT( x_Label, ("") );
	SO_ENGINE_ADD_INPUT( x_Axial, (NULL) );
	SO_ENGINE_ADD_INPUT( y_Label, ("") );
	SO_ENGINE_ADD_INPUT( y_Axial, (NULL) );
	SO_ENGINE_ADD_INPUT( title, ("") );
	SO_ENGINE_ADD_INPUT( footnote, ("") );
	SO_ENGINE_ADD_INPUT( labelOutliers, (TRUE) );
	SO_ENGINE_ADD_INPUT( legend, (TRUE) );

	SO_ENGINE_ADD_INPUT( format, (BMP) );
	SO_ENGINE_DEFINE_ENUM_VALUE(Format, BMP);
	SO_ENGINE_DEFINE_ENUM_VALUE(Format, JPEG);
	SO_ENGINE_DEFINE_ENUM_VALUE(Format, PNG);
	SO_ENGINE_SET_SF_ENUM_TYPE(format, Format);

	SO_ENGINE_ADD_INPUT( type, (Scatter) );
	SO_ENGINE_DEFINE_ENUM_VALUE(Type, Scatter);
	SO_ENGINE_DEFINE_ENUM_VALUE(Type, Bland_Altmann);
	SO_ENGINE_SET_SF_ENUM_TYPE(type, Type);

	SO_ENGINE_ADD_INPUT( file, ("") );
	SO_ENGINE_ADD_INPUT (update, ());

	//set up the output type of the engine
	SO_ENGINE_ADD_OUTPUT( ret, SoSFBool );

	nRet = FALSE;
}

SoMVTBasicPlot::~SoMVTBasicPlot(void)
{
}

void SoMVTBasicPlot::inputChanged(SoField *whichField)
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

void SoMVTBasicPlot::evaluate()
{
	SO_ENGINE_OUTPUT(ret, SoSFBool, setValue(nRet));
}

bool SoMVTBasicPlot::validateInput()
{
	const char * _file = file.getValue().getString();
	if (strlen(_file) == 0)
	{
		SoDebugError::postInfo("SoMVTScatterPlot:", "can not plot to file");
		return FALSE;
	}

	if (x_Axial.getNum() <= 1 || y_Axial.getNum() <= 1)
	{
		SoDebugError::postInfo("SoMVTScatterPlot:", "can not get input values");
		return FALSE;
	}

	return true;
}

bool SoMVTBasicPlot::updateOutput()
{
	bool ret = true;
	if (!validateInput())
		return false;

	int _port = port.getValue();
	int val = createConnect(_port);
    if (val != 0) 
	{
		// print the value
		SoDebugError::post("SoMVTScatterPlot:", "unable to connect Rserve - error: %d", val);
		return false;
    }

	int x_num = x_Axial.getNum();
	int y_num = y_Axial.getNum();
	if (x_num != y_num)
		SoDebugError::postWarning("SoMVTScatterPlot:", "shrink to the same length");
	
	int num = x_num < y_num ? x_num : y_num;

	double * x_data = new double[num];
	for (int i = 0; i < num; i++)
		x_data[i] = x_Axial[i];

	double * y_data = new double[num];
	for (int i = 0; i < num; i++)
		y_data[i] = y_Axial[i];

	//assign data
	char *x_variable = "x";
	assignData(x_variable, x_data, num);

	char *y_variable = "y";
	assignData(y_variable, y_data, num);

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
		switch(type.getValue())
		{
		case Scatter:
			ret = plotScatter();
			break;

		case Bland_Altmann:
			ret = plotBlandAltmann();
			break;
		}

		//close device
		if (ret)
			ret = executeCmd("dev.off()");
	}
	else
		SoDebugError::post("SoMVTBasicPlot - error:", cmd);

	delete [] x_data;
	x_data = NULL;

	delete [] y_data;
	y_data = NULL;

	return ret;
}

bool SoMVTBasicPlot::plotScatter()
{
	try {
		//set plot parameters
		executeCmd("opar<-par();par(mar=c(4, 4, 2.5, 2))");

		executeCmd("if(abs(min(x))<10){xb<-floor(min(x))}");
		executeCmd("if(abs(min(x))>=10&&abs(xb)<100){xb<-floor(min(x)/10)*10}");
		executeCmd("if(abs(min(x))>=100){xb<-floor(min(x)/100)*100}");

		executeCmd("if(abs(max(x))<10){xa<-ceiling(max(x))}");
		executeCmd("if(abs(max(x))>=10&&abs(max(x))<100){xa<-ceiling(max(x)/10)*10}");
		executeCmd("if(abs(max(x))>=100){xa<-ceiling(max(x)/100)*100}");

		executeCmd("if(abs(min(y))<10){yb<-floor(min(y))}");
		executeCmd("if(abs(min(y))>=10&&abs(min(y))<100){yb<-floor(min(y)/10)*10}");
		executeCmd("if(abs(min(y))>=100){yb<-floor(min(y)/100)*100}");

		executeCmd("if(abs(max(y))<10){ya<-ceiling(max(y))}");
		executeCmd("if(abs(max(y))>=10&&abs(max(y))<100){ya<-ceiling(max(y)/10)*10}");
		executeCmd("if(abs(max(y))>=100){ya<-ceiling(max(y)/100)*100}");

		executeCmd("if(xb<10&&xb>=0){xb<-0}");
		executeCmd("if(yb<10&&yb>=0){yb<-0}");

		//plotting
		executeCmd("plot(x, y, type=\"n\", xlab=\"\", ylab=\"\", xlim=c(xb-0.04*(xa-xb),xa+0.04*(xa-xb)), ylim=c(yb-0.04*(ya-yb),ya+0.04*(ya-yb)),xaxt=\"n\", yaxt=\"n\")");
		executeCmd("axis(side=1,seq(xb,xa,(xa-xb)/20),labels=F,tcl=-0.2)");
		executeCmd("axis(side=1,seq(xb,xa,(xa-xb)/5))");
		executeCmd("axis(side=2,seq(yb,ya,(ya-yb)/20),labels=F,tcl=-0.2)");
		executeCmd("axis(side=2,seq(yb,ya,(ya-yb)/5))");

		executeCmd("points(x, y, cex=1)");
		executeCmd("lm.sol<-lm(y~x)");
		executeCmd("abline(lm.sol,col=\"red\",lty=2)");

		executeCmd("res<-lm.sol[[2]]");
		executeCmd("coeff<-lm.sol[[1]]");
		
		if (legend.getValue())
			executeCmd("legend(\"topleft\",c(as.expression(substitute(y==r1*x+(r2),list(r1=round(coeff[[2]],4),r2=round(coeff[[1]],4)))),as.expression(substitute(italic(R)^2==r,list(r=round(1.0-sum(res^2)/sum((y-mean(y))^2),3))))),inset = c(.2,.15))");

		char cmd[128];
		const char* str = NULL;
		//title
		str = title.getValue().getString();
		if (strlen(str) > 0)
		{
			sprintf_s(cmd, "title(\"%s\")", str);
			executeCmd(cmd);
		}

		//label
		str = x_Label.getValue().getString();
		if (strlen(str) > 0)
		{
			sprintf_s(cmd, "mtext(\"%s\", side=1, line=2, cex=1, font=3)", str);
			executeCmd(cmd);
		}

		str = y_Label.getValue().getString();
		if (strlen(str) > 0)
		{
			sprintf_s(cmd, "mtext(\"%s\", side=2, line=2, cex=1, font=3)", str);
			executeCmd(cmd);
		}

		//label outliers
		if (labelOutliers.getValue())
		{
			executeCmd("outliers<-y[abs(scale(res))>3];index<-sequence(length(x))");
			executeCmd("if(length(outliers)>0){text(x[index[y==outliers]]+5, outliers+5, label=index[y==outliers])}");
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

bool SoMVTBasicPlot::plotBlandAltmann()
{
	try {
		//set plot parameters
		executeCmd("opar<-par();par(mar=c(4, 4, 2.5, 2))");

		//caculate average and difference
		executeCmd("average=(x+y)/2;difference=x-y");
		executeCmd("low=mean(difference)-1.96*sd(difference);high=mean(difference)+1.96*sd(difference)");

		//set range
		executeCmd("labels1<-c(min(average), min(difference), low)");

		executeCmd("labels2<-c(max(average), max(difference), high)");

		executeCmd("xb<-labels1[1]");
		executeCmd("if(abs(xb)<10){xb<-floor(xb)}");
		executeCmd("if(abs(xb)>=10&&abs(xb)<100){xb<-floor(xb/10)*10}");
		executeCmd("if(abs(xb)>=100){xb<-floor(xb/100)*100}");

		executeCmd("xa<-labels2[1]");
		executeCmd("if(abs(xa)<10){xa<-ceiling(xa)}");
		executeCmd("if(abs(xa)>=10&&abs(xa)<100){xa<-ceiling(xa/10)*10}");
		executeCmd("if(abs(xa)>=100){xa<-ceiling(xa/100)*100}");

		executeCmd("yb<-min(labels1[2], labels1[3])");
		executeCmd("if(abs(yb)<10){yb<-floor(yb)}");
		executeCmd("if(abs(yb)>=10&&abs(yb)<100){yb<-floor(yb/10)*10}");
		executeCmd("if(abs(yb)>=100){yb<-floor(yb/100)*100}");

		executeCmd("ya<-max(labels2[2], labels2[3])");
		executeCmd("if(abs(ya)<10){ya<-ceiling(ya)}");
		executeCmd("if(abs(ya)>=10&&abs(ya)<100){ya<-ceiling(ya/10)*10}");
		executeCmd("if(abs(ya)>=100){ya<-ceiling(ya/100)*100}");

		executeCmd("if(xb<10&&xb>=0){xb<-0}");
		executeCmd("if(yb<10&&yb>=0){yb<-0}");

		executeCmd("if((ya-high)>(ya-yb)/5){ya<-ya-(ya-yb)/5}");
		executeCmd("if((low-yb)>(ya-yb)/5){yb<-yb+(ya-yb)/5}");

		//plotting
		executeCmd("plot(average, difference, xaxt=\"n\", yaxt=\"n\", type=\"n\", xlab=\"\", ylab=\"\", xlim=c(xb-0.04*(xa-xb),xa+0.04*(xa-xb)), ylim=c(yb-0.04*(ya-yb),ya+0.04*(ya-yb)))");
		executeCmd("points(average, difference)");
		executeCmd("axis(side=1,seq(xb,xa,(xa-xb)/20),labels=F,tcl=-0.2)");
		executeCmd("axis(side=1,seq(xb,xa,(xa-xb)/5))");
		executeCmd("axis(side=2,seq(yb,ya,(ya-yb)/20),labels=F,tcl=-0.2)");
		executeCmd("axis(side=2,seq(yb,ya,(ya-yb)/5))");

		//reference line
		executeCmd("abline(h=mean(difference)+1.96*sd(difference), col=2, lty=2)");
		executeCmd("abline(h=mean(difference)-1.96*sd(difference), col=2, lty=2)");
		executeCmd("abline(h=mean(difference), lty=2)");

		executeCmd("text(xb,mean(difference)+0.02*(ya-yb), paste('Mean =', format(round(mean(difference),3))), pos=4, col=4)");
		executeCmd("text(xb,mean(difference)-1.96*sd(difference)+0.02*(ya-yb), paste('Mean-1.96*SD =',format(round(mean(difference)-1.96*sd(difference),3))), pos=4, col=4)");
		executeCmd("text(xb,mean(difference)+1.96*sd(difference)+0.02*(ya-yb), paste('Mean+1.96*SD =',format(round(mean(difference)+1.96*sd(difference),3))), pos=4, col=4)");

		if (legend.getValue())
			executeCmd("legend(\"topright\",c(as.expression(substitute(Mean==a,list(a=round(mean(difference),3)))),as.expression(substitute(SD==b,list(b=round(sd(difference),3)))), \"alpha=0.05\"),inset = c(.05,.25))");

		char cmd[128];
		const char* str = NULL;

		//title
		str = title.getValue().getString();
		if (strlen(str) > 0)
		{
			sprintf_s(cmd, "title(\"%s\")", str);
			executeCmd(cmd);
		}

		//label
		str = x_Label.getValue().getString();
		if (strlen(str) > 0)
		{
			sprintf_s(cmd, "mtext(\"%s\", side=1, line=2, cex=1, font=3)", str);
			executeCmd(cmd);
		}

		str = y_Label.getValue().getString();
		if (strlen(str) > 0)
		{
			sprintf_s(cmd, "mtext(\"%s\", side=2, line=2, cex=1, font=3)", str);
			executeCmd(cmd);
		}

		//label outliers
		if (labelOutliers.getValue())
		{
			executeCmd("outliers<-difference[(difference<mean(difference)-1.96*sd(difference))|(difference>mean(difference)+1.96*sd(difference))]");
			executeCmd("index<-sequence(length(y));");
			executeCmd("if(length(outliers)>0){text(average[index[difference==outliers]]+5, outliers+5, label=index[difference==outliers])}");
		}

		//restore plot setting
		executeCmd("par(opar)");
	}
	catch(char *cmd)
	{
		SoDebugError::post("MVTStatistic - plotBlandAltmann error:", cmd);

		return false;
	}

	return true;
}
