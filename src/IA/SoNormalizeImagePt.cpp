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

#include "SoNormalizeImagePt.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoNormalizeImagePt );

SoNormalizeImagePt::SoNormalizeImagePt(void)
{
	SO_ENGINE_CONSTRUCTOR( SoNormalizeImagePt );

	//Initialize the input parameter
	SO_ENGINE_ADD_INPUT( refInput, (0) );
	SO_ENGINE_ADD_INPUT( points, (0) );
	SO_ENGINE_ADD_INPUT( sopInstanceUID, ("") );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( coordinates, SoMFVec3f );	
	SO_ENGINE_ADD_OUTPUT( plane, SoSFMatrix );
	SO_ENGINE_ADD_OUTPUT( status, SoSFBool );	
}

void SoNormalizeImagePt::initClass()
{
	SO_ENGINE_INIT_CLASS( SoNormalizeImagePt, SoEngine, "SoEngine" );
}

SoNormalizeImagePt::~SoNormalizeImagePt(void)
{
}

void SoNormalizeImagePt::inputChanged(SoField *whichInput)
{
	updateOutput();
}

void SoNormalizeImagePt::evaluate()
{
	SO_ENGINE_OUTPUT( status, SoSFBool, setValue(true) );	
}

void SoNormalizeImagePt::updateOutput()
{
	if (refInput.getNum() <=0 || points.getNum() <=0 || sopInstanceUID.getValue().getLength() <= 0)
		return;

	int ptNum = points.getNum() / 2;
	SbString uid = sopInstanceUID.getValue();

	SoMFVec3f _coordinates;
	for (int i = 0; i < ptNum; i++)
	{
		int point[2];
		point[0] = points[2*i];
		point[1] = points[2*i+1];

		SbVec3f pt;
		if (getNormalizedPoint(pt, point, uid))
			_coordinates.set1Value(_coordinates.getNum(), pt);
	}

	if (_coordinates.getNum() > 0)
	{
		SO_ENGINE_OUTPUT( coordinates, SoMFVec3f, setValues(0, _coordinates.getNum(), _coordinates.getValues(0)) );	

		SbMatrix mat = SbMatrix::identity();
		mat[1][1] = -1;
		mat[2][2] = -1;
		mat[3][0] = 0.5;
		mat[3][1] = 0.5;
		mat[3][2] = _coordinates[0][2];

		SO_ENGINE_OUTPUT( plane, SoSFMatrix, setValue(mat) );	
	}
}

bool SoNormalizeImagePt::getNormalizedPoint(SbVec3f &pt, int point[2], SbString &uid)
{
	for (int i = 0; i < refInput.getNum(); i++){
		SoXipDataDicom *dicom = refInput[i];

		if (dicom){
			if (!dicom->getDataset().isNull()){
				SbXipDicomItem dataset(dicom->getDataset());

				//sop instance UID
				SbString sopInstanceUID;
				dataset.findAndGet(SbXipDicomTagKey(0x08, 0x18), sopInstanceUID, true);

				if (strcmp(sopInstanceUID.getString(), uid.getString()) == 0){
					SbString imageCols;
					//image col
					dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x0011), imageCols, true);

					SbString imageRows;
					//image row
					dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x0010), imageRows, true);

					int col = atoi(imageCols.getString());
					int row = atoi(imageRows.getString());
					int depth = refInput.getNum();

					pt[0] = (float)point[0] / (float)col;
					pt[1] = (float)point[1] / (float)row;
					pt[2] = (float)i / (float)depth;

					return true;
				}
			}
		}

	}

	return false;
}
