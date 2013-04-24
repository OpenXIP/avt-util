/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
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
