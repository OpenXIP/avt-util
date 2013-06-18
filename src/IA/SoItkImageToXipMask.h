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
*	@file    SoItkImageToXipMask.h
*	@brief   convert the ItkImage to XipImage with the given model matrix
*	@author  Jie Zheng
**/

#if !defined(AFX_SoItkImageToXipMask_H__356844CC_3ABE_43A3_9C82_7CAC0DB1F90C__INCLUDED_)
#define AFX_SoItkImageToXipMask_H__356844CC_3ABE_43A3_9C82_7CAC0DB1F90C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Inventor/Fields/SoSFPlane.h>
#include <Inventor/Fields/SoSFFloat.h>
#include <Inventor/Fields/SoSFEnum.h>
#include <Inventor/Fields/SoSFVec3f.h>
#include <Inventor/Engines/SoSubEngine.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoMFInt32.h>

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/itk/SoItkSFDataImage.h>

#include <InsightToolkit/Common/itkImage.h>
#include <InsightToolkit/BasicFilters/itkImportImageFilter.h>

class __declspec(dllexport) SoItkImageToXipMask : public SoEngine
{
	SO_ENGINE_HEADER( SoItkImageToXipMask);

public:
	SoItkImageToXipMask(void);
	static void initClass();

	SoSFMatrix			modelMatrix;
	SoItkSFDataImage 	input;

	SoEngineOutput output; // SoXipSFDataImage
		// Output Image

private:
	~SoItkImageToXipMask(void);
		// Destructor

	virtual void evaluate();
		// Evaluation method
	virtual void inputChanged (SoField* whichField);

protected:
	SoXipDataImage*		mXipImage;
		// Data wrapper for the XIP image class
};

#endif // !defined(AFX_SoItkImageToXipMask_H__356844CC_3ABE_43A3_9C82_7CAC0DB1F90C__INCLUDED_)
