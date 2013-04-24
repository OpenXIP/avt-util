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
