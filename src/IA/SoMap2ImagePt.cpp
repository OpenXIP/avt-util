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

#include "SoMap2ImagePt.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoMap2ImagePt );

SoMap2ImagePt::SoMap2ImagePt(void)
{
	SO_ENGINE_CONSTRUCTOR( SoMap2ImagePt );

	//Initialize the input parameter
	SO_ENGINE_ADD_INPUT( refInput, (0) );
	SO_ENGINE_ADD_INPUT( coordinates, (SbVec3f(0,0,0)) );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( points, SoMFInt32 );	
	SO_ENGINE_ADD_OUTPUT( sopInstanceUID, SoSFString );	
	SO_ENGINE_ADD_OUTPUT( status, SoSFBool );	
}

void SoMap2ImagePt::initClass()
{
	SO_ENGINE_INIT_CLASS( SoMap2ImagePt, SoEngine, "SoEngine" );
}

SoMap2ImagePt::~SoMap2ImagePt(void)
{
}

void SoMap2ImagePt::inputChanged(SoField *whichInput)
{
	updateOutput();
}

void SoMap2ImagePt::evaluate()
{
	SO_ENGINE_OUTPUT( status, SoSFBool, setValue(true) );	
}

void SoMap2ImagePt::updateOutput()
{
	if (refInput.getNum() <= 0 ||coordinates.getNum() <= 0)
		return;

	SoMFInt32 _points;
	SbString _sopInstanceUID;

	for (int i = 0; i < coordinates.getNum(); i++){
		SbVec3f point = coordinates[i];

		int pt[2];
		SbString uid;
		if (getMappingPoint(pt, uid, point) && point != SbVec3f(0, 0, 0)){
			_points.set1Value(_points.getNum(), pt[0]);
			_points.set1Value(_points.getNum(), pt[1]);
			_sopInstanceUID = uid;
		}
	}

//	if (_points.getNum() > 0)
	{
		SO_ENGINE_OUTPUT( points, SoMFInt32, setValues(0, _points.getNum(), _points.getValues(0)) );	
		SO_ENGINE_OUTPUT( sopInstanceUID, SoSFString, setValue(_sopInstanceUID) );	
	}
}

bool SoMap2ImagePt::getMappingPoint(int pt[2], SbString &uid, SbVec3f point)
{
	int depth = refInput.getNum();

	int slice = (int)(point[2] * depth);
	if (slice < 0 || slice >= depth)
		return false;

	SoXipDataDicom *dicom = refInput[slice];
	if (dicom){
		if (!dicom->getDataset().isNull()){
			SbXipDicomItem dataset(dicom->getDataset());

			//sop instance UID
			dataset.findAndGet(SbXipDicomTagKey(0x08, 0x18), uid, true);

			SbString imageCols;
			//image col
			dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x0011), imageCols, true);

			SbString imageRows;
			//image row
			dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x0010), imageRows, true);

			int col = atoi(imageCols.getString());
			int row = atoi(imageRows.getString());

			pt[0] = (int)(point[0] * col + 0.5);
			pt[1] = (int)(point[1] * row + 0.5);

			return true;
		}
	}
	
	return false;
}
