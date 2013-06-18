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

// MVTStatistics.cpp : Defines the entry point for the DLL application.
//

#ifdef WIN32
#include <windows.h>
#endif

#include "SoMVTBasicStatistic.h"
#include "SoMVTStatisticScript.h"

#include "SoMVTVolumeCalculator.h"
#include "SoMVTSurfaceCalculator.h"

#include "SoMVTRserveCommand.h"
#include "SoMVTBasicPlot.h"

#include "SoMVTAnova.h"
#include "SoMVTMultipleRegression.h"
#include "SoMVTHistogram.h"

int init()
{
	SoMVTRserveCommand::initClass();

	SoMVTBasicStatistic::initClass();
	SoMVTStatisticScript::initClass();
	SoMVTAnova::initClass();
	SoMVTMultipleRegression::initClass();

	SoMVTBasicPlot::initClass();
	SoMVTHistogram::initClass();

	SoMVTVolumeCalculator::initClass();
	SoMVTSurfaceCalculator::initClass();

	return 0;
}

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
 	if( ul_reason_for_call == DLL_PROCESS_ATTACH )
		init();

	return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

