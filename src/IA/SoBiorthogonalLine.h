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
*	@file    SoBiorthogonalLine.h
*	@brief   Draw the biorthogonal lines
*	@author  Jie Zheng
**/

#pragma once

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/Fields/SoSFInt32.h>
#include <Inventor/Fields/SoSFFloat.h>
#include <Inventor/Fields/SoSFString.h>
#include <Inventor/Fields/SoSFEnum.h>
#include <Inventor/Fields/SoSFTrigger.h>
#include <Inventor/Fields/SoSFVec3f.h>
#include <Inventor/Fields/SoSFColor.h>
#include <Inventor/Fields/SoSFBool.h>
#include <Inventor/Fields/SoSFVec4f.h>
#include <Inventor/Fields/SoSFUShort.h>
#include <Inventor/Fields/SoMFMatrix.h>
#include <Inventor/Fields/SoMFVec3f.h>
#include <Inventor/Fields/SoMFVec4f.h>
#include <Inventor/Actions/SoHandleEventAction.h>
#include <Inventor/Actions/SoGLRenderAction.h>
#include <Inventor/Actions/SoGetBoundingBoxAction.h>
#include <Inventor/sensors/SoSensor.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/SbBox.h>
#include <Inventor/SbViewportRegion.h>

#include <xip/inventor/overlay/SoXipOverlayElement.h>

class __declspec(dllexport) SoBiorthogonalLine : SoNode
{
	SO_NODE_HEADER( SoBiorthogonalLine );

public:
	SoBiorthogonalLine(void);
	static void initClass();

	SoSFBool	on;
	/// lineWidth
	SoSFFloat	lineWidth;
	/// lineColor
	SoSFColor	linecolor;
	/// transparency
	SoSFUShort	linePattern;
		
	SoSFTrigger	clear;
	SoSFTrigger	import;

	SoMFVec3f	points;

private:
	SbVec3f curPt0;
	SbVec3f curPt1;
	SbVec3f curPt2;
	SbVec3f curPt3;

	//the distance from the intersection point to the curPt0, 1, 2, 3;
	SbVec4f fDistance;

	SbVec3f intersectionPt;
	SbVec3f	lineDir;

	SbBool	bPressed;
	SbBool	bInitial;
	int		nHandlerPtID;

	SbXipOverlaySettings		mOverlaySettings;

	class SbPlaneProjector*		mPlaneProj;
	SbViewVolume				mViewVolume;
	SbViewportRegion			mViewport;

	SoFieldSensor *clearSensor;
	SoFieldSensor *importSensor;

	void	renderLine(SbVec3f &pt, SbVec3f &dir, SbVec3f &projDir, SbVec4f &dis, SbColor &clr);
	void	renderLine(SbVec3f &pt0, SbVec3f &pt1, SbVec3f &pt2, SbVec3f &pt3, SbColor &clr);

	const SbVec2f getNormalizedPosition( const SbVec2s& screenPt ) const;
	SbBool getPoint( SoHandleEventAction* action, SbVec3f& point );
	SbBool getPoint( SoNode* node, const SbVec2s& screenPt, SbVec3f& worldPt );
	void saveViewInformation( SoAction* action );	

    static void clearSensorCB( void *, SoSensor * );
	void	clearLines();

    static void importSensorCB( void *, SoSensor * );
	void	importLines();

	void	updatePoints();

public:
	virtual void	GLRender(SoGLRenderAction *action);
    virtual void	handleEvent(SoHandleEventAction *action);

protected:
	virtual ~SoBiorthogonalLine(void);
};
