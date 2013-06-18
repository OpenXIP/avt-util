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

#include "SoGetImageInfor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoGetImageInfor );

SoGetImageInfor::SoGetImageInfor(void)
{
	SO_ENGINE_CONSTRUCTOR( SoGetImageInfor );

	//Initialize the input parameter
	SO_ENGINE_ADD_INPUT( refInput, (0) );
	SO_ENGINE_ADD_INPUT( imageInstanceUID, ("") );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( imagePosition, SoSFVec3f );	
	SO_ENGINE_ADD_OUTPUT( imageSpacing, SoSFVec3f );	
}

void SoGetImageInfor::initClass()
{
	SO_ENGINE_INIT_CLASS( SoGetImageInfor, SoEngine, "SoEngine" );
}

SoGetImageInfor::~SoGetImageInfor(void)
{
}

void SoGetImageInfor::inputChanged(SoField *whichInput)
{
	updateOutput();
}

void SoGetImageInfor::evaluate()
{
}

void SoGetImageInfor::updateOutput()
{
	SbString uid = imageInstanceUID.getValue();

	if (refInput.getNum() <= 0 ||strlen(uid.getString()) <= 0)
		return;

	getImageInfor(uid);
}

bool SoGetImageInfor::getImageInfor(SbString &uid)
{
	int num = refInput.getNum();

	for (int i = 0; i < num; i++){
		SoXipDataDicom *dicom = refInput[i];
		if (dicom){
			if (!dicom->getDataset().isNull()){
				SbXipDicomItem dataset(dicom->getDataset());

				//sop instance UID
				SbString sopUID;
				dataset.findAndGet(SbXipDicomTagKey(0x08, 0x18), sopUID, true);
				if (sopUID == uid)
				{
					SbString imgPosition;
					dataset.findAndGet(SbXipDicomTagKey(0x0020, 0x0032), imgPosition, true);

					SbVec3f position;
					sscanf_s(imgPosition.getString(), "%f\\%f\\%f", &position[0], &position[1], &position[2]);

					SbString imgSpacing;
					dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x0030), imgSpacing, true);

					SbString sliceSpacing;
					dataset.findAndGet(SbXipDicomTagKey(0x0018, 0x0088), sliceSpacing, true);

					SbVec3f spacing;
					sscanf_s(imgSpacing.getString(), "%f\\%f", &spacing[0], &spacing[1]);
					spacing[2] = atof(sliceSpacing.getString());

					SO_ENGINE_OUTPUT(imagePosition, SoSFVec3f, setValue(position));
					SO_ENGINE_OUTPUT(imageSpacing, SoSFVec3f, setValue(spacing));

					return true;
				}
			}
		}

	}
	
	return false;
}
