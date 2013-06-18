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

#include "SoVolumeMetrics.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoVolumeMetrics );

SoVolumeMetrics::SoVolumeMetrics(void)
{
	SO_ENGINE_CONSTRUCTOR( SoVolumeMetrics );

	// Inputs
	SO_ENGINE_ADD_INPUT( inputVolume, (0) );
	SO_ENGINE_ADD_INPUT( update, () );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( RECIST, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( WHO, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( Volume, SoSFFloat );

	_recist = 0.0;
	_who = 0.0;
	_volume = 0.0;
}

void SoVolumeMetrics::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVolumeMetrics, SoEngine, "SoEngine" );
}

SoVolumeMetrics::~SoVolumeMetrics(void)
{
}

void SoVolumeMetrics::inputChanged (SoField* whichField)
{
	if (whichField == &update)
		calculateVolumeMetris();
}

void SoVolumeMetrics::evaluate()
{	
	SO_ENGINE_OUTPUT( RECIST, SoSFFloat, setValue( _recist ) );
	SO_ENGINE_OUTPUT( WHO, SoSFFloat, setValue( _who ) );
	SO_ENGINE_OUTPUT( Volume, SoSFFloat, setValue( _volume ) );
}

void SoVolumeMetrics::calculateVolumeMetris()
{
	SoXipDataImage* maskData = inputVolume.getValue();
	if (!maskData || !maskData->get())
	{
		SoDebugError::postInfo(__FILE__, "input volume data is NULL");
		return;
	}

	SbXipImage* mask = maskData->get();
	SbMatrix matMask = mask->getModelMatrix();
	SbXipImageDimensions maskDimension = mask->getDimStored();

	//decompose the model matrix
	SbVec3f colVector, rowVector, norVector, volPosition;

	colVector[0] = matMask[0][0];
	colVector[1] = matMask[0][1];
	colVector[2] = matMask[0][2];

	rowVector[0] = matMask[1][0];
	rowVector[1] = matMask[1][1];
	rowVector[2] = matMask[1][2];

	norVector[0] = matMask[2][0];
	norVector[1] = matMask[2][1];
	norVector[2] = matMask[2][2];

	volPosition[0] = matMask[3][0];
	volPosition[1] = matMask[3][1];
	volPosition[2] = matMask[3][2];

	float valSpacing[3];
	valSpacing[0] = colVector.length() / (float)maskDimension[0];
	valSpacing[1] = rowVector.length() / (float)maskDimension[1];
	valSpacing[2] = norVector.length() / (float)maskDimension[2];

	double volumeFactor = 0.001*valSpacing[0]*valSpacing[1]*valSpacing[2];

	unsigned long volume=0, recist=0, who=0;
	int nSize = maskDimension[0] * maskDimension[1];
	unsigned char* pMask = (unsigned char*)mask->refBufferPtr();

	for (int k = 0; k < maskDimension[2]; k++) {
		unsigned char* pSlice = pMask + k * nSize;

		for (int j = 0; j < nSize; j++) {

			if (pSlice[j] != 0)
				volume++;
		}
	}

	_volume = (double)volume * volumeFactor;

	mask->unrefBufferPtr();
}
