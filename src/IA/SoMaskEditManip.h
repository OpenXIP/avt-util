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
*	@file    SoMaskEditManip.h
*	@brief   handle the mask editing
*	@author  Jie Zheng
**/

#pragma once
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/Fields/SoSFInt32.h>
#include <Inventor/Fields/SoSFFloat.h>
#include <Inventor/Fields/SoSFString.h>
#include <Inventor/Fields/SoSFBool.h>
#include <Inventor/Fields/SoSFEnum.h>
#include <Inventor/Fields/SoSFTrigger.h>
#include <Inventor/Fields/SoSFVec2f.h>
#include <Inventor/Fields/SoSFVec3f.h>
#include <Inventor/Fields/SoSFColor.h>
#include <Inventor/Fields/SoSFMatrix.h>
#include <Inventor/Fields/SoMFMatrix.h>
#include <Inventor/Fields/SoMFVec3f.h>
#include <Inventor/Fields/SoMFInt32.h>
#include <Inventor/Fields/SoSFColor.h>
#include <Inventor/Fields/SoSFUShort.h>
#include <Inventor/Actions/SoHandleEventAction.h>
#include <Inventor/Actions/SoGLRenderAction.h>
#include <Inventor/Actions/SoGetBoundingBoxAction.h>
#include <Inventor/sensors/SoSensor.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/SbBox.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SbTime.h>
#include <Inventor/Sblinear.h>

#include <xip/inventor/overlay/SoXipOverlayManipulatedElement.h>
#include <xip/inventor/overlay/SoXipOverlayElement.h>
#include <xip/inventor/overlay/SoXipOverlayManipBase.h>
#include <xip/inventor/overlay/SoXipEditableShape.h>
#include <xip/inventor/overlay/XipOverlayUtils.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLineSet.h>

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>

class __declspec(dllexport) SoMaskEditManip : SoXipOverlayManipBase
{
	SO_NODE_HEADER( SoMaskEditManip );

public:
	SoMaskEditManip(void);

	enum Type {
		CONTOUR,
		POLYGON,
	};

	SoSFEnum		type;
	SoSFFloat		width;
	SoSFUShort		style;
	SoSFColor		color;
	SoMFVec3f		points;

	static void initClass();

protected:
	~SoMaskEditManip(void);

	SoMFVec3f			curvePoints;

	SoSeparator*		mCurveSeparator;
	SoCoordinate3*		mCurveCoords;
	SoBaseColor*		mCurveColor;
	SoDrawStyle*		mCurveStyle;

	virtual void handleEvent( SoHandleEventAction* action );
	virtual void GLRender( SoGLRenderAction* action );

	SoXipEditableShape* mWorkingShape;
	SoXipEditableShape* getEditableShape(SoNode* root);

private:
	SbVec2s				mMouseDownPos;
	SbTime				mMouseDownTime;

	int					mDoubleClickMaxJump;
	SbTime				mDoubleClickTime;

	SbBool				mIsButtonPressed;
};
