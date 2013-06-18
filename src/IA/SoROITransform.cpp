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

#include "SoROITransform.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoROITransform );

SoROITransform::SoROITransform(void)
{
	SO_ENGINE_CONSTRUCTOR( SoROITransform );

	//Input
	SO_ENGINE_ADD_INPUT( volModelMatrix, (SbMatrix::identity()) );
	SO_ENGINE_ADD_INPUT( roiModelMatrix, (SbMatrix::identity()) );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( scale, SoSFVec3f );
	SO_ENGINE_ADD_OUTPUT( translate, SoSFVec3f );
}

void 
SoROITransform::initClass()
{
	SO_ENGINE_INIT_CLASS( SoROITransform, SoEngine, "SoEngine" );
}


SoROITransform::~SoROITransform(void)
{
}

void SoROITransform::inputChanged(SoField* whichField)
{
}

void SoROITransform::evaluate()
{
	SbMatrix _matVol = volModelMatrix.getValue();
	SbMatrix _matRoi = roiModelMatrix.getValue();

	float _scale_x = (_matRoi[0][0]) / _matVol[0][0];
	float _scale_y = (_matRoi[1][1]) / _matVol[1][1];
	float _scale_z = (_matRoi[2][2]) / _matVol[2][2];

	float _translate_x = (_matRoi[3][0] - _matVol[3][0]) / _matVol[0][0];
	float _translate_y = (_matRoi[3][1] - _matVol[3][1]) / _matVol[1][1];
	float _translate_z = (_matRoi[3][2] - _matVol[3][2]) / _matVol[2][2];

	SO_ENGINE_OUTPUT(scale, SoSFVec3f, setValue(_scale_x, _scale_y, _scale_z));
	SO_ENGINE_OUTPUT(translate, SoSFVec3f, setValue(_translate_x, _translate_y, _translate_z));
}
