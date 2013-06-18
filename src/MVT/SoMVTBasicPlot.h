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
*	@file    SoMVTBasicPlot.h
*	@brief   Scatter and Bland_Altmann R implementation interface
*	@author  Jie Zheng
**/

#if !defined(AFX_SoMVTBasicPlot_H__3512375434GC_3AWE_43A3_9C82_7CAC0DB1F90C__INCLUDED_)
#define AFX_SoMVTBasicPlot_H__3512375434GC_3AWE_43A3_9C82_7CAC0DB1F90C__INCLUDED_

#pragma once

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/Fields/SoSFEnum.h>
#include <Inventor/Fields/SoSFBool.h>

class SoMVTBasicPlot : public SoEngine
{
	SO_ENGINE_HEADER(SoMVTBasicPlot);

public:
	enum Format {
		BMP,
		JPEG,
		PNG
	};

	enum Type {
		Scatter,
		Bland_Altmann,
	};

	/// Initialization
	static void	initClass();
	SoMVTBasicPlot(void);

public:
	SoSFInt32		 port;
	SoSFString		 x_Label;
	SoMFFloat		 x_Axial;
	SoSFString		 y_Label;
	SoMFFloat		 y_Axial;
	SoSFString		 title;
	SoSFString       footnote;
	SoSFBool		 labelOutliers;
	SoSFBool		 legend;

	SoSFEnum		 format;
	SoSFString		 file;

	SoSFEnum		 type;
	SoSFTrigger		 update;

	SoEngineOutput	 ret;

protected:
	/// Destructor
	~SoMVTBasicPlot(void);

	/// Evaluation
	virtual void			inputChanged (SoField* whichField);
	virtual void			evaluate ();

	bool					updateOutput();
	bool					validateInput();

private:
	bool					nRet;

	bool					plotScatter();
	bool					plotBlandAltmann();
};

#endif // !defined(AFX_SoMVTBasicPlot_H__3512375434GC_3AWE_43A3_9C82_7CAC0DB1F90C__INCLUDED_)
