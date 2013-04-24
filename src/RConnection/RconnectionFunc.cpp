/*
 *  C++ Interface to Rconnection
 *  Copyright (C) 2009-10 Jie Zheng, All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; version 2.1 of the License
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Leser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Although this code is licensed under LGPL v2.1, we strongly encourage
 *  everyone modifying this software to contribute back any improvements and
 *  bugfixes to the project for the benefit all other users. Thank you.
 * 
 *  
 */


#define EXPORTAPI extern "C" __declspec(dllexport)

#include "RconnectionFunc.h"
#include "Rconnection.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

Rconnection *rc = NULL;

int createConnect(int port)
{
    delete rc;
	rc = NULL;

	rc = new Rconnection(NULL, port);
    
    int i=rc->connect();

	return i;
}

void closeConnect()
{
    delete rc;
	rc = NULL;
}

int evalExpress(char *variable, double *data, int nSize, char *cmd, double *output, int nNum)
{
	if (rc == NULL || variable == NULL || data == NULL || output == NULL)
		return 0;

	// assign the above contents to the variable "data" in R
	rc->assign(variable, new Rdouble(data, nSize));

	// calculate
	Rdouble *result = (Rdouble*) rc->eval(cmd);
	int nActualNum = 0;
	if (result) {// if everything was fine, we have the result
		// get the contents of the data (unformatted)
		double *d = result->doubleArray();
		int ct = result->length();
		nActualNum = ct > nNum ? nNum : ct;
		memcpy(output, d, sizeof(double)*nActualNum);
		// finally dispose of the object
		delete result;
	}
	else
	{
		// print the value
		std::cerr << "MVTStatistic - error:" << cmd << endl;
	}
	return nActualNum;
}

int getEval(char *cmd, vector<float> &output)
{
	if (rc == NULL)
		return 0;

	// calculate
	Rdouble *result = (Rdouble*) rc->eval(cmd);
	int nActualNum = 0;
	if (result) {// if everything was fine, we have the result
		// get the contents of the data (unformatted)
		double *d = result->doubleArray();
		int ct = result->length();
		nActualNum = ct;
		for (int i = 0; i < ct; i++)
			output.push_back(d[i]);
		// finally dispose of the object
		delete result;
	}
	else
	{
		// print the value
		std::cerr << "MVTStatistic - error:" << cmd << endl;
	}
	return nActualNum;
}

bool assignDataset(char *variable, vector<double> &input)
{
	if (rc == NULL || variable == NULL || input.size() <= 0)
		return false;

	// assign the above contents to the variable in R
	rc->assign(variable, new Rdouble((double*)&(input[0]), input.size()));
	return true;
}

bool assignData(char *variable, double *input, int nNum)
{
	if (rc == NULL || variable == NULL || input == NULL)
		return false;

	// assign the above contents to the variable in R
	rc->assign(variable, new Rdouble(input, nNum));
	return true;
}

bool executeCmd(char *cmd)
{
	if (rc == NULL || cmd == NULL)
		return false;
	
	// calculate
	int result = rc->voidEval(cmd);
	if (result)
	{
		// print the value
		std::cerr << "MVTStatistic - error:" << cmd << endl;

		return false;
	}
	
	return true;
}

bool shutdownServ(int nPort)
{
	bool bRet = false;
	if (nPort < 1)
	{
		std::cerr << "Rserve is not running" << endl;
		return bRet;
	}
	
	Rconnection *rc = 0;
	int port = nPort;
	const char *host_name = "127.0.0.1";
	const char *pwd = 0;
	if (host_name) {
		
		if (port > 1) rc = new Rconnection(host_name, port);
		else rc = new Rconnection(host_name);
	} else {
		rc = new Rconnection();
	}
	
	int i = rc->connect();
	if (i) {
		std::cerr << "ERROR: unable to connect Rserve" << endl;
	} else	{
		rc->shutdown(pwd);
		bRet = true;
	}
	delete rc;

	return bRet;
}
