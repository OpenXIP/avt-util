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

