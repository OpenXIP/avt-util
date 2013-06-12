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
 * @version	June 2009
 * @author Jie Zheng
 */

// SoDrawLine.cpp: implementation of the SoDrawLine class.
//
//////////////////////////////////////////////////////////////////////
#include <assert.h>
#include "SoDrawLine.h"
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/elements/SoViewportRegionElement.h>

#include <GL/Gl.h>

#include <vector>       // stl vector header
using namespace std;    // saves us typing std:: before vector

const float EPSILON = 0.0001f;
const float THREHOLD = 0.01f;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_NODE_SOURCE( SoDrawLine );

SoDrawLine::SoDrawLine()
{
	SO_NODE_CONSTRUCTOR( SoDrawLine );

    SO_NODE_ADD_FIELD(on,	(FALSE));

    SO_NODE_ADD_FIELD(linecolor,	(SbColor(0.9,0.9,0.2)));
	SO_NODE_ADD_FIELD(lineWidth, (0.25));
	SO_NODE_ADD_FIELD(linePattern, (0xffff));

    SO_NODE_ADD_FIELD(clear,	());
    SO_NODE_ADD_FIELD(import,	());

	SO_NODE_ADD_FIELD(points,	(0,0,0));

	clearSensor = new SoFieldSensor( &SoDrawLine::clearSensorCB, this);
	clearSensor->attach(&clear);
    clearSensor->setPriority( 0 );

	importSensor = new SoFieldSensor( &SoDrawLine::importSensorCB, this);
	importSensor->attach(&import);
    importSensor->setPriority( 0 );

	bPressed = false;
	curPt0 = SbVec3f(0.0, 0.0, 0.0);
	curPt1 = SbVec3f(0.0, 0.0, 0.0);

	bInitial = true;
	nHandlerPtID = -1;

	mPlaneProj		= new SbPlaneProjector(FALSE);
	mPlaneProj->setPlane( SbPlane( SbVec3f(0, 0, 1), 0 ) );
}

void SoDrawLine::initClass()
{
	SO_NODE_INIT_CLASS( SoDrawLine, SoNode, "SoNode" );
}

SoDrawLine::~SoDrawLine()
{
	if( mPlaneProj )
	{
		delete mPlaneProj;
		mPlaneProj = 0;
	}

	if( clearSensor )
		delete clearSensor;

	if( importSensor )
		delete importSensor;
}

void SoDrawLine::GLRender(SoGLRenderAction *action)
{
	SbColor lineclr = linecolor.getValue();

	SoState *state = action->getState();
	SbViewVolume viewVolume = SoViewVolumeElement::get(state);
	SbMatrix modelMatrix = SoModelMatrixElement::get(state);
	SbVec3f projPoint = viewVolume.getProjectionPoint();

	glPushAttrib( GL_CURRENT_BIT );
	glPushAttrib( GL_ENABLE_BIT );

	glEnable( GL_LINE_SMOOTH );
	glDisable( GL_LIGHTING );

	glPushMatrix();

	//push drawing attributes 
	float penWidth;
	glGetFloatv(GL_LINE_WIDTH, &penWidth);

	int penPattern;
	glGetIntegerv(GL_LINE_STIPPLE_PATTERN, &penPattern);

	float penColor[4];
	glGetFloatv(GL_CURRENT_COLOR, penColor);

	renderLine(curPt0, curPt1, lineclr);

	//pop drawing attributes 
	glLineWidth(penWidth);
	glLineStipple(1, penPattern);
	glColor4f(penColor[0], penColor[1], penColor[2], penColor[3]);

	glPopMatrix();
	glPopAttrib();

	SoNode::GLRender(action);
}

void SoDrawLine::renderLine(SbVec3f &point0, SbVec3f &point1, SbColor &clr)
{
	if (point0 == SbVec3f(0.0, 0.0, 0.0) || point1 == SbVec3f(0.0, 0.0, 0.0))
		return;

	float fPen;
	glGetFloatv(GL_LINE_WIDTH, &fPen);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, linePattern.getValue());
	glLineWidth(lineWidth.getValue());
	glColor4f(clr[0], clr[1], clr[2], 1.0);
	
	glBegin( GL_LINES );

	glVertex3f(point0[0], point0[1], point0[2]);
	glVertex3f(point1[0], point1[1], point1[2]);

	glEnd();

	//glBegin( GL_QUADS );
	//glColor4f(clr[0], clr[1], clr[2], 0.8);

	//float radius = 0.01;
	//glVertex3f(point0[0]-radius, point0[1]+radius, point0[2]);
	//glVertex3f(point0[0]+radius, point0[1]+radius, point0[2]);
	//glVertex3f(point0[0]+radius, point0[1]-radius, point0[2]);
	//glVertex3f(point0[0]-radius, point0[1]-radius, point0[2]);

	//glVertex3f(point1[0]-radius, point1[1]+radius, point1[2]);
	//glVertex3f(point1[0]+radius, point1[1]+radius, point1[2]);
	//glVertex3f(point1[0]+radius, point1[1]-radius, point1[2]);
	//glVertex3f(point1[0]-radius, point1[1]-radius, point1[2]);

	//glEnd();

	glDisable(GL_LINE_STIPPLE);

	glLineWidth(fPen);
}

void SoDrawLine::handleEvent(SoHandleEventAction *action)
{
	if( !on.getValue() )
		return ;

	if( !action ) return;

	doAction(action);

	saveViewInformation(action);

	SbBool handled = FALSE;
	const SoEvent* event = action->getEvent();

	SbVec3f pt;
	if(SoMouseButtonEvent::isButtonPressEvent(event, SoMouseButtonEvent::BUTTON1))
	{
//		clearLines();

		if (getPoint( action, pt ))
		{
			if (bInitial)
				curPt0 = pt;
			else
			{
				if (((pt-curPt0).length() - THREHOLD) < EPSILON)
					nHandlerPtID = 0;
				else if (((pt-curPt1).length() - THREHOLD) < EPSILON)
					nHandlerPtID = 1;
			}

			bPressed = true;
//			SoDebugError::post("MouseDown", "MouseDown! point pos. (%4.2f, %4.2f, %4.2f) \n", pt[0], pt[1], pt[2]);
		}

		handled = TRUE;
	}
	else if(event->isOfType(SoLocation2Event::getClassTypeId()))
	{
		if(getPoint( action, pt ) && bPressed)
		{
			if (bInitial)
				curPt1 = pt;
			else
			{
				switch (nHandlerPtID)
				{
				case 0:
					curPt0 = pt;
					break;

				case 1:
					curPt1 = pt;
					break;

				default:
					break;
				}
			}
			updatePoints();

//			SoDebugError::post("MouseMove", "MouseMove! point pos. (%4.2f, %4.2f, %4.2f) \n", pt[0], pt[1], pt[2]);
		}
		handled = TRUE;
	}
	else if(SoMouseButtonEvent::isButtonReleaseEvent(event, SoMouseButtonEvent::BUTTON1))
	{
		if (bInitial)
			bInitial = false;

		if (bPressed)
			bPressed = false;
	}

	if( handled )
	{
		action->setHandled();
	}
}

void SoDrawLine::updatePoints()
{
	points.setNum(2);

	points.set1Value(0, curPt0);
	points.set1Value(1, curPt1);
}

void SoDrawLine::clearLines()
{
	bInitial = true;
	nHandlerPtID = -1;

	curPt0 = SbVec3f(0.0, 0.0, 0.0);
	curPt1 = SbVec3f(0.0, 0.0, 0.0);

	updatePoints();
}

void SoDrawLine::clearSensorCB( void *inPlaneRect, SoSensor * )
{
    SoDrawLine *planeline = (SoDrawLine *) inPlaneRect;
	planeline->clearLines();
}

void SoDrawLine::importSensorCB( void *inPlaneRect, SoSensor * )
{
    SoDrawLine *planeline = (SoDrawLine *) inPlaneRect;
	planeline->importLines();
}

void SoDrawLine::importLines()
{
	int size = points.getNum();
	if (size < 2)
		return;

	curPt0 = points[0];
	curPt1 = points[1];
}

const SbVec2f SoDrawLine::getNormalizedPosition( const SbVec2s& screenPt ) const
{
    const SbVec2s& pixSize = mViewport.getViewportSizePixels();
	const SbVec2s& origin = mViewport.getViewportOriginPixels();
    SbVec2s pos = screenPt - origin;

	SbVec2f normalizedScreenPt;
	if ( pixSize[0] == 0 )
		normalizedScreenPt[0] = 0.;
    else
		normalizedScreenPt[0] = (float) pos[0] / (float) pixSize[0];

	if ( pixSize[1] == 0 )
		normalizedScreenPt[1] = 0.;
    else
		normalizedScreenPt[1] = (float) pos[1] / (float) pixSize[1];

    return normalizedScreenPt;
}

SbBool SoDrawLine::getPoint( SoNode* node, const SbVec2s& screenPt, SbVec3f& worldPt )
{
	SoRayPickAction pa( mViewport );
	pa.setPoint( screenPt );
	pa.setRadius( 1 );
	pa.enableCulling( FALSE );
	pa.apply( node );

	if( pa.getPickedPoint() )
	{
		worldPt = pa.getPickedPoint()->getPoint();
		return TRUE;
	}
	else
	{
		worldPt = mPlaneProj->project( getNormalizedPosition( screenPt ) );
		return TRUE;

	}

	SoError::post( "SoDrawLine: Unknown location" );

	return FALSE;
}

SbBool SoDrawLine::getPoint( SoHandleEventAction* action, SbVec3f& point )
{
	const SoEvent* event = action->getEvent();
	if( !event )
		return FALSE;
	
	return getPoint( action->getNodeAppliedTo(), 
		action->getEvent()->getPosition(), point );	
}

void SoDrawLine::saveViewInformation( SoAction* action )
{
	SoState* state = action->getState();
	if( !state )
		return ;

	SbBool canSave = FALSE;

	if( action->isOfType( SoHandleEventAction::getClassTypeId() ) )
	{
		// make sure no grabber is active
		if( !((SoHandleEventAction*) action)->getGrabber() )
			canSave = TRUE;
	}

	if( canSave )
	{
		mOverlaySettings = SoXipOverlayElement::get( state );

		// Save the view volume element
		mViewVolume = SoViewVolumeElement::get( state );

		// Save the viewport
		mViewport = SoViewportRegionElement::get( state );

		// NEAR_PLANE : move slighty inwards of nearplane to ensure proper drawing
		float distance = 0.001;
		if( mOverlaySettings.getLocation() == SoXipOverlayElement::FOCAL_PLANE )
			distance = mViewVolume.getDepth() / 2.f;

		mPlaneProj->setViewVolume( mViewVolume );
		mPlaneProj->setPlane( mViewVolume.getPlane( mViewVolume.getNearDist() + distance ) );
	}
}
