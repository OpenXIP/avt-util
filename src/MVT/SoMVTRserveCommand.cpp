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

// SoMVTRserveCommand.cpp: implementation of the SoMVTRserveCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "SoMVTRserveCommand.h"
#include "RconnectionFunc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoMVTRserveCommand );

SoMVTRserveCommand::SoMVTRserveCommand(void)
{
	SO_ENGINE_CONSTRUCTOR( SoMVTRserveCommand );

	// Inputs
	SO_ENGINE_ADD_INPUT( port, (6311) );
	SO_ENGINE_ADD_INPUT( stop, () );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( output, SoSFBool );

	status = false;
}

void 
SoMVTRserveCommand::initClass()
{
	SO_ENGINE_INIT_CLASS( SoMVTRserveCommand, SoEngine, "SoEngine" );
}

SoMVTRserveCommand::~SoMVTRserveCommand(void)
{
}

void SoMVTRserveCommand::inputChanged (SoField* whichField)
{
	if (whichField == &stop)
	{
		int nPort = port.getValue();
		if (nPort > 1)
			status = shutdownRserve(nPort);
	}
}

void
SoMVTRserveCommand::evaluate()
{	
	SO_ENGINE_OUTPUT( output, SoSFBool, setValue(status) );	
}

bool SoMVTRserveCommand::shutdownRserve(int nPort)
{
	return shutdownServ(nPort);
}
