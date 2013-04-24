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
