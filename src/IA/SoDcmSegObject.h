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
*	@file    SoDcmSegObject.h
*	@brief   export the mask to dicom segmentation object
*	@author  Jie Zheng
**/

// SoDcmSegObject.h: interface for the SoDcmSegObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SoDcmSegObject_H__351754CC_3ABE_43A3_9C82_7CAC0DB1F90C__INCLUDED_)
#define AFX_SoDcmSegObject_H__351754CC_3ABE_43A3_9C82_7CAC0DB1F90C__INCLUDED_

#if _MSC_VER > 1000

#pragma once
#endif // _MSC_VER > 1000

#include "Inventor/Fields/SoSFPlane.h"
#include "Inventor/Fields/SoSFFloat.h"
#include "Inventor/Fields/SoSFEnum.h"
#include "Inventor/Fields/SoSFVec3f.h"
#include "Inventor/Engines/SoSubEngine.h"
#include "Inventor/fields/SoSFBool.h"
#include "Inventor/fields/SoSFString.h"
#include "Inventor/fields/SoSFMatrix.h"
#include "Inventor/fields/SoSFVec4f.h"
#include "Inventor/fields/SoSFTrigger.h"
#include "Inventor/fields/SoMFInt32.h"
#include "Inventor/SbString.h"

#include <xip/inventor/dicom/SoXipMFDataDicom.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/itk/SoItkSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>

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

class __declspec(dllexport) SoDcmSegObject : SoEngine  
{
	SO_ENGINE_HEADER( SoDcmSegObject);

public:
	// input
	SoSFString file;
	SoXipMFDataDicom	refInput;

	//Annotator
	SoSFString	ann_name;
	SoSFString	ann_date;

	//Tumor
	SoSFString	tumor_ID;
	SoSFString	tumor_Confidence;
	SoSFString	tumor_Comments;

	//data
	SoMFInt32		 origin;
	SoXipSFDataImage input0;

	SoSFTrigger	process;

	SoEngineOutput		status; // 

	BOOL saveSegObject(const char *filename, const char *maskUID);

	void writeSegHeader(DcmDataset *dataset, const char *maskUID, int iSegDimension[3]);
	void writeSegFrames(DcmDataset *dataset, SbVec3f &colVector, SbVec3f &rowVector, SbVec3f &volPosition, float fVolumeSpacing[3], int iSegDimension[3]);
	void writeSegPixel(DcmDataset *dataset, unsigned char *pData, int iSegDimension[3]);
	
public:
	void processResult();
	SoDcmSegObject();
	static void initClass();

protected:
	virtual ~SoDcmSegObject();
	virtual void inputChanged(SoField *whichField);
	virtual void evaluate();

	bool loadDicomStrings();
	bool loadImageInstanceUID(int index, SbString &strUID);

	SoXipDataImage* mXipImage;

	//data information
	SbString	dicom_name;
	SbString	dicom_gender;
	SbString	dicom_age;
	SbString	dicom_patientID;
	SbString	dicom_studyID;
	SbString	dicom_studyUID;
	SbString	dicom_seriesUID;
	SbString	dicom_seriesNumber;
	SbString	dicom_sopClassUID;
	SbString	dicom_studyDate;
	SbString	dicom_studyTime;

	//image information
	SbString	dicom_imagePosition;
	SbString	dicom_imageOrientation;
	SbString	dicom_pixelSpacing;
	SbString	dicom_sliceThickness;

	SbString	dicom_imageCols;
	SbString	dicom_imageRows;
};

#endif // !defined(AFX_SoDcmSegObject_H__351754CC_3ABE_43A3_9C82_7CAC0DB1F90C__INCLUDED_)
