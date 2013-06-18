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
 * @version	January 2010
 * @author Jie Zheng
 */

#include "SoBiorthogonalLine.h"

#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/elements/SoViewportRegionElement.h>

#include <GL/Gl.h>

#include <vector>       // stl vector header
using namespace std;    // saves us typing std:: before vector

const float epsilon = 0.0001f;
const float threhold = 0.002f;
const SbVec3f Axial = SbVec3f(1.0,0.0,0.0);
const float pi = 3.1415726;
const float pi2degree = 180.0f/pi;
const float LEN = 0.25f;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_NODE_SOURCE( SoBiorthogonalLine );

SoBiorthogonalLine::SoBiorthogonalLine(void)
{
	SO_NODE_CONSTRUCTOR( SoDrawLine );

    SO_NODE_ADD_FIELD(on,	(FALSE));

    SO_NODE_ADD_FIELD(linecolor,	(SbColor(0.9,0.9,0.2)));
	SO_NODE_ADD_FIELD(lineWidth, (0.25));
	SO_NODE_ADD_FIELD(linePattern, (0xffff));

    SO_NODE_ADD_FIELD(clear,	());
    SO_NODE_ADD_FIELD(import,	());

	SO_NODE_ADD_FIELD(points,	(0,0,0));

	clearSensor = new SoFieldSensor( &SoBiorthogonalLine::clearSensorCB, this);
	clearSensor->attach(&clear);
    clearSensor->setPriority( 0 );

	importSensor = new SoFieldSensor( &SoBiorthogonalLine::importSensorCB, this);
	importSensor->attach(&import);
    importSensor->setPriority( 0 );

	nHandlerPtID = -1;
	bPressed = false;
	bInitial = true;
	curPt0 = SbVec3f(0.0, 0.0, 0.0);
	curPt1 = SbVec3f(0.0, 0.0, 0.0);
	curPt2 = SbVec3f(0.0, 0.0, 0.0);
	curPt3 = SbVec3f(0.0, 0.0, 0.0);

	intersectionPt = SbVec3f(0.0, 0.0, 0.0);
	fDistance = SbVec4f(0.0, 0.0, 0.0, 0.0);

	mPlaneProj		= new SbPlaneProjector(FALSE);
	mPlaneProj->setPlane( SbPlane( SbVec3f(0, 0, 1), 0 ) );
}

void SoBiorthogonalLine::initClass()
{
	SO_NODE_INIT_CLASS( SoBiorthogonalLine, SoNode, "SoNode" );
}

SoBiorthogonalLine::~SoBiorthogonalLine(void)
{
	if( mPlaneProj )
	{
		delete mPlaneProj;
		mPlaneProj = 0;
	}

	if( clearSensor )
		delete clearSensor;
}

void SoBiorthogonalLine::GLRender(SoGLRenderAction *action)
{
	SbColor lineclr = linecolor.getValue();

	SoState *state = action->getState();
	SbViewVolume viewVolume = SoViewVolumeElement::get(state);
	SbMatrix modelMatrix = SoModelMatrixElement::get(state);
	SbVec3f projPoint = viewVolume.getProjectionPoint();
	SbVec3f projDir = viewVolume.getProjectionDirection();

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

//	renderLine(intersectionPt, lineDir, projDir, fDistance, lineclr);
	renderLine(curPt0, curPt1, curPt2, curPt3, lineclr);

	//pop drawing attributes 
	glLineWidth(penWidth);
	glLineStipple(1, penPattern);
	glColor4f(penColor[0], penColor[1], penColor[2], penColor[3]);

	glPopMatrix();
	glPopAttrib();

	SoNode::GLRender(action);
}

void SoBiorthogonalLine::renderLine(SbVec3f &pt, SbVec3f &dir, SbVec3f &projDir, SbVec4f &dis, SbColor &clr)
{
	if (pt == SbVec3f(0.0, 0.0, 0.0) || dis == SbVec4f(0.0, 0.0, 0.0, 0.0))
		return;

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, linePattern.getValue());
	glLineWidth(lineWidth.getValue());
	glColor4f(clr[0], clr[1], clr[2], 1.0);
	
	SbVec3f vertical = dir.cross(projDir);

	curPt0 = pt + dis[0] * dir;
	curPt1 = pt - dis[1] * dir;
	curPt2 = pt + dis[2] * vertical;
	curPt3 = pt - dis[3] * vertical;

	glBegin( GL_LINES );

	glVertex3f(curPt0[0], curPt0[1], curPt0[2]);
	glVertex3f(curPt1[0], curPt1[1], curPt1[2]);

	glEnd();

	glBegin( GL_LINES );

	glVertex3f(curPt2[0], curPt2[1], curPt2[2]);
	glVertex3f(curPt3[0], curPt3[1], curPt3[2]);

	glEnd();

	glDisable(GL_LINE_STIPPLE);
}

void SoBiorthogonalLine::renderLine(SbVec3f &pt0, SbVec3f &pt1, SbVec3f &pt2, SbVec3f &pt3, SbColor &clr)
{
	if (pt0 == SbVec3f(0.0, 0.0, 0.0) || pt1 == SbVec3f(0.0, 0.0, 0.0) || pt2 == SbVec3f(0.0, 0.0, 0.0) ||pt3 == SbVec3f(0.0, 0.0, 0.0))
		return;

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, linePattern.getValue());
	glLineWidth(lineWidth.getValue());
	glColor4f(clr[0], clr[1], clr[2], 1.0);
	
	glBegin( GL_LINES );

	glVertex3f(pt0[0], pt0[1], pt0[2]);
	glVertex3f(pt1[0], pt1[1], pt1[2]);

	glEnd();

	glBegin( GL_LINES );

	glVertex3f(pt2[0], pt2[1], pt2[2]);
	glVertex3f(pt3[0], pt3[1], pt3[2]);

	glEnd();

	glDisable(GL_LINE_STIPPLE);
}

void SoBiorthogonalLine::handleEvent(SoHandleEventAction *action)
{
	if( !on.getValue() )
		return ;

	if( !action ) return;

	doAction(action);

	saveViewInformation(action);

	SoState *state = action->getState();
	SbViewVolume viewVolume = SoViewVolumeElement::get(state);
	SbVec3f projDir = viewVolume.getProjectionDirection();

	SbBool handled = FALSE;
	const SoEvent* event = action->getEvent();

	SbVec3f pt, vertical, dir;
	if(SoMouseButtonEvent::isButtonPressEvent(event, SoMouseButtonEvent::BUTTON1))
	{
//		clearLines();
		if (getPoint( action, pt ))
		{
			if (bInitial)
				curPt0 = pt;
			else //determinate the handler points
			{
				if (((pt-curPt0).length() - threhold) < epsilon)
				{
					nHandlerPtID = 0;
					fDistance[0] = (intersectionPt - curPt0).length();
				}
				else if (((pt-curPt1).length() - threhold) < epsilon)
				{
					nHandlerPtID = 1;
					fDistance[1] = (intersectionPt - curPt1).length();
				}
				else if (((pt-curPt2).length() - threhold) < epsilon)
				{
					nHandlerPtID = 2;
					fDistance[2] = (intersectionPt - curPt2).length();
				}
				else if (((pt-curPt3).length() - threhold) < epsilon)
				{
					nHandlerPtID = 3;
					fDistance[3] = (intersectionPt - curPt3).length();
				}
				else if (((pt-intersectionPt).length() - threhold) < epsilon)
				{
					nHandlerPtID = 4;
				}
			}

			bPressed = true;
		}

		handled = TRUE;
	}
	else if(event->isOfType(SoLocation2Event::getClassTypeId()))
	{
		if(getPoint( action, pt ) && bPressed)
		{
			if (bInitial)
			{
				curPt1 = pt;

				lineDir = curPt0 - curPt1;
				float length = lineDir.normalize();

				intersectionPt = (curPt0 + curPt1) / 2.0;

				vertical = lineDir.cross(projDir);
				curPt2 = intersectionPt + LEN * length * vertical;
				curPt3 = intersectionPt - LEN * length * vertical;

				fDistance[0] = length / 2.0;
				fDistance[1] = length / 2.0;
				fDistance[2] = LEN * length;
				fDistance[3] = LEN * length;
			}
			else
			{
				float len = 0;
				SbVec3f vec;
				switch (nHandlerPtID)
				{
				case 0:
					curPt0 = pt;
					lineDir = curPt0 - curPt1;
					lineDir.normalize();
					
					intersectionPt = curPt1 + fDistance[1]*lineDir;

					vertical = lineDir.cross(projDir);
					curPt2 = intersectionPt + fDistance[2] * vertical;
					curPt3 = intersectionPt - fDistance[3] * vertical;

					fDistance[0] = (intersectionPt - curPt0).length();
					break;

				case 1:
					curPt1 = pt;
					lineDir = curPt0 - curPt1;
					lineDir.normalize();

					intersectionPt = curPt0 - fDistance[0]*lineDir;

					vertical = lineDir.cross(projDir);
					curPt2 = intersectionPt + fDistance[2] * vertical;
					curPt3 = intersectionPt - fDistance[3] * vertical;

					fDistance[1] = (intersectionPt - curPt1).length();
					break;

				case 2:
					curPt2 = pt;
					lineDir = curPt0 - curPt1;
					dir = curPt2 - curPt1;

					len = lineDir.normalize();
					fDistance[1] = lineDir.dot(dir);
					fDistance[0] = len - fDistance[1];
					intersectionPt = curPt1 + fDistance[1]*lineDir;

					vertical = lineDir.cross(projDir);
					curPt3 = intersectionPt - fDistance[3] * vertical;

					fDistance[2] = (intersectionPt - curPt2).length();
					break;

				case 3:
					curPt3 = pt;
					lineDir = curPt0 - curPt1;
					dir = curPt3 - curPt1;

					len = lineDir.normalize();
					fDistance[1] = lineDir.dot(dir);
					fDistance[0] = len - fDistance[1];
					intersectionPt = curPt1 + fDistance[1]*lineDir;

					vertical = lineDir.cross(projDir);
					curPt2 = intersectionPt + fDistance[2] * vertical;

					fDistance[3] = (intersectionPt - curPt3).length();
					break;

				//the intersection point
				case 4:
					intersectionPt = pt;
					lineDir = curPt0 - curPt1;
					lineDir.normalize();
					vertical = lineDir.cross(projDir);

					curPt0 = intersectionPt + fDistance[0] * lineDir;
					curPt1 = intersectionPt - fDistance[1] * lineDir;
					curPt2 = intersectionPt + fDistance[2] * vertical;
					curPt3 = intersectionPt - fDistance[3] * vertical;

					break;

				default:
					break;
				}
			}

			updatePoints();
		}

		handled = TRUE;
	}
	else if(SoMouseButtonEvent::isButtonReleaseEvent(event, SoMouseButtonEvent::BUTTON1))
	{
		if (bPressed)
			bPressed = false;

		if (bInitial)
			bInitial = false;

		nHandlerPtID = -1;
	}

	if( handled )
	{
		action->setHandled();
	}
}

void SoBiorthogonalLine::updatePoints()
{
	points.setNum(4);

	points.set1Value(0, curPt0);
	points.set1Value(1, curPt1);
	points.set1Value(2, curPt2);
	points.set1Value(3, curPt3);
}

void SoBiorthogonalLine::clearLines()
{
	bInitial = true;
	intersectionPt = SbVec3f(0.0, 0.0, 0.0);
	fDistance = SbVec4f(0.0, 0.0, 0.0, 0.0);

	curPt0 = SbVec3f(0.0, 0.0, 0.0);
	curPt1 = SbVec3f(0.0, 0.0, 0.0);
	curPt2 = SbVec3f(0.0, 0.0, 0.0);
	curPt3 = SbVec3f(0.0, 0.0, 0.0);

	updatePoints();
}

void SoBiorthogonalLine::clearSensorCB( void *inPlaneRect, SoSensor * )
{
    SoBiorthogonalLine *planeline = (SoBiorthogonalLine *) inPlaneRect;
	planeline->clearLines();
}

void SoBiorthogonalLine::importSensorCB( void *inPlaneRect, SoSensor * )
{
    SoBiorthogonalLine *planeline = (SoBiorthogonalLine *) inPlaneRect;
	planeline->importLines();
}

void SoBiorthogonalLine::importLines()
{
	int size = points.getNum();
	if (size < 4)
		return;

	curPt0 = points[0];
	curPt1 = points[1];
	curPt2 = points[2];
	curPt3 = points[3];
}

const SbVec2f SoBiorthogonalLine::getNormalizedPosition( const SbVec2s& screenPt ) const
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

SbBool SoBiorthogonalLine::getPoint( SoNode* node, const SbVec2s& screenPt, SbVec3f& worldPt )
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

	SoError::post( "SoBiorthogonalLine: Unknown location" );

	return FALSE;
}

SbBool SoBiorthogonalLine::getPoint( SoHandleEventAction* action, SbVec3f& point )
{
	const SoEvent* event = action->getEvent();
	if( !event )
		return FALSE;
	
	return getPoint( action->getNodeAppliedTo(), 
		action->getEvent()->getPosition(), point );	
}

void SoBiorthogonalLine::saveViewInformation( SoAction* action )
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
