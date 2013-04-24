/*
 *  Rconnection.h : constants and macros for Interaction functions with Rserv
 *  Copyright (C) 2009-10 Jie Zheng
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published
 *  by the Free Software Foundation; version 2.1 of the License
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Note: This header file is licensed under LGPL to allow other
 *        programs to use it under LGPL. Rserve itself is licensed under GPL.
 *
 *  
 */

#ifndef EXPORTAPI
#define EXPORTAPI  extern "C" __declspec(dllimport)
#endif

#include <vector>
using namespace std;

EXPORTAPI int createConnect(int port);
EXPORTAPI int  evalExpress(char *variable, double *data, int nSize, char *cmd, double *output, int nNum);
EXPORTAPI int  getEval(char *cmd, vector<float> &output);
EXPORTAPI bool assignData(char *variable, double *input, int nNum);
EXPORTAPI bool assignDataset( char *variable, vector<double> &input);
EXPORTAPI bool executeCmd(char *cmd);
EXPORTAPI void closeConnect();

EXPORTAPI bool shutdownServ(int nPort);

