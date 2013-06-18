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

/**
*	@file    SoNormalizeImagePt.h
*	@brief   calculate the 3D points according to the 2D image points
*	@author  Jie Zheng
**/

#pragma once
#include <Inventor/Engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/Fields/SoMFVec3f.h>
#include <Inventor/Fields/SoMFInt32.h>
#include <Inventor/Fields/SoSFInt32.h>
#include <Inventor/Fields/SoSFVec3f.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFMatrix.h>

#include <xip/inventor/dicom/SoXipMFDataDicom.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>

#include <dcmtk/dcmdata/dcmetinf.h>
#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmdata/dcdebug.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmdata/dcdict.h>
#include <dcmtk/dcmdata/cmdlnarg.h>
#include <dcmtk/ofstd/ofconapp.h>
#include <dcmtk/ofstd/ofstd.h>
#include <dcmtk/ofstd/ofdatime.h>
#include <dcmtk/dcmdata/dcuid.h>         /* for dcmtk version name */
#include <dcmtk/dcmdata/dcdeftag.h>      /* for DCM_StudyInstanceUID */

class __declspec(dllexport) SoNormalizeImagePt : public SoEngine
{
	SO_ENGINE_HEADER( SoNormalizeImagePt);

public:
	SoNormalizeImagePt(void);
	static void initClass();

	//input
	SoXipMFDataDicom	refInput;
	SoMFInt32			points;
	SoSFString			sopInstanceUID;

	//output
	SoEngineOutput		coordinates;
	SoEngineOutput		plane;
	SoEngineOutput		status;

private:
	~SoNormalizeImagePt(void);

	virtual void evaluate();
		// Evaluation method
	virtual void inputChanged (SoField* whichField);

protected:
	void updateOutput();
	bool getNormalizedPoint(SbVec3f &pt, int point[2], SbString &uid);
};
