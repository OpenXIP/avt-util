/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
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