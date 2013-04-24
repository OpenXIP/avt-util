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
 * @version	Dec 2009
 * @author Jie Zheng
 */

#include "SoMaskEditManip.h"
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/elements/SoViewportRegionElement.h>

#include <GL/Gl.h>

#include <vector>       // stl vector header
using namespace std;    // saves us typing std:: before vector

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SO_NODE_SOURCE( SoMaskEditManip );

SoMaskEditManip::SoMaskEditManip(void)
{
	SO_NODE_CONSTRUCTOR( SoIAOverlayCutManip );

	SO_NODE_ADD_FIELD(type, (CONTOUR));

	SO_NODE_DEFINE_ENUM_VALUE(Type, CONTOUR);
	SO_NODE_DEFINE_ENUM_VALUE(Type, POLYGON);
	SO_NODE_SET_SF_ENUM_TYPE(type, Type);

	SO_NODE_ADD_FIELD( width, (1.0) );
	SO_NODE_ADD_FIELD( style, (0xffff) );
	SO_NODE_ADD_FIELD( color, (SbVec3f(0, 1, 0)) );

	SO_NODE_ADD_FIELD( points, (0, 0, 0));
	points.setNum(0);
	curvePoints.setNum(0);

	mCurveCoords = new SoCoordinate3;
	mCurveCoords->point.setNum(0);
	
	mCurveColor = new SoBaseColor;
	mCurveColor->rgb.setValue( 0, 1, 0 );	

	mCurveStyle = new SoDrawStyle;
	mCurveStyle->pointSize.setValue(1.0);
	mCurveStyle->lineWidth.setValue(1.0);
	mCurveStyle->linePattern.setValue(0xffff);
	
	mCurveSeparator = new SoSeparator;
	mCurveSeparator->addChild( mCurveStyle );
	mCurveSeparator->addChild( mCurveColor );
	mCurveSeparator->addChild( mCurveCoords );
	mCurveSeparator->addChild( new SoLineSet );

	mCurveSeparator->ref();

	mDoubleClickMaxJump = 2;
	mDoubleClickTime = SbTime(0.5);
	mIsButtonPressed = FALSE;
}

SoMaskEditManip::~SoMaskEditManip(void)
{
	if( mCurveSeparator )
	{
		mCurveSeparator->unref();
		mCurveSeparator = 0;
	}
}

void SoMaskEditManip::initClass()
{
	SO_NODE_INIT_CLASS( SoMaskEditManip, SoXipOverlayManipBase, "SoXipOverlayManipBase" );
}

void SoMaskEditManip::handleEvent(SoHandleEventAction *action)
{
	if( !on.getValue() )
		return;

	SoXipOverlayManipBase::handleEvent( action );
	if( action->isHandled() )
		return;

	const SoEvent* event = action->getEvent();

	SbVec3f pt;
	const SbVec2s& mousePosition = action->getEvent()->getPosition();
	if(SoMouseButtonEvent::isButtonPressEvent(event, SoMouseButtonEvent::BUTTON1))
	{
		action->setHandled();

		SbTime time = action->getEvent()->getTime();

		SbVec2s v = (mMouseDownPos - mousePosition);
		float mouseJump = sqrtf( v.dot(v) );

		if( (time - mMouseDownTime) < mDoubleClickTime && mouseJump < mDoubleClickMaxJump )
		{
			SoDebugError::postInfo(__FILE__, "Field Update - double click");

			if (type.getValue() == POLYGON)
			{
				points.setValues(0, curvePoints.getNum(), curvePoints.getValues(0));

				mCurveCoords->point.setNum(0);
				curvePoints.setNum(0);
			}

			action->setHandled();

			mMouseDownTime = SbTime::zero();
			mMouseDownPos = SbVec2s(-1, -1);
		}
		else
		{
			action->setGrabber( this );
			if (getPoint( action, pt ))
			{
				mCurveCoords->point.set1Value ( mCurveCoords->point.getNum (), pt );
				curvePoints.set1Value ( curvePoints.getNum (), pt );
			}

			points.setNum(0);
			mIsButtonPressed = TRUE;
			mMouseDownTime = time;
			mMouseDownPos = mousePosition;
		}
	}
	else if(event->isOfType(SoLocation2Event::getClassTypeId()))
	{
		if (type.getValue() == CONTOUR)
		{
			if(getPoint( action, pt ) && action->getGrabber() == this)
			{
				mCurveCoords->point.set1Value ( mCurveCoords->point.getNum (), pt );
				curvePoints.set1Value ( curvePoints.getNum (), pt );
				
				startNotify();
				//SoDebugError::post("MouseMove", "MouseMove! point pos. (%4.2f, %4.2f, %4.2f) \n", pt[0], pt[1], pt[2]);
			}
		}
		action->setHandled();
	}
	else if(SoMouseButtonEvent::isButtonReleaseEvent(event, SoMouseButtonEvent::BUTTON1))
	{
		startNotify();

		action->setHandled();
		action->releaseGrabber();

		if (type.getValue() == CONTOUR)
		{
			points.setValues(0, curvePoints.getNum(), curvePoints.getValues(0));

			mCurveCoords->point.setNum(0);
			curvePoints.setNum(0);
		}
	}
	else if(SoMouseButtonEvent::isButtonPressEvent(event, SoMouseButtonEvent::BUTTON2))
	{
		action->setHandled();
	}
}

SoXipEditableShape* SoMaskEditManip::getEditableShape ( SoNode* root )
{
	SoNodeList shapes = XipOverlayUtils::getManipulableShapes( root, FALSE );

	for( int i = 0; i < shapes.getLength(); ++ i )
	{
		SoXipEditableShape* shape = (SoXipEditableShape *) shapes[i];

		if( shape->isOfType( SoXipEditableShape::getClassTypeId() ) )//&& shape->isSelected() )
		{
			return shape;
		}
	}

	return 0;
}

void SoMaskEditManip::GLRender( SoGLRenderAction* action )
{
	if( !on.getValue() )
		return ;

	SoXipOverlayManipulatedElement::set( action->getState(), this, TRUE );

	glPushAttrib( GL_ENABLE_BIT );
	glDisable( GL_DEPTH_TEST );

	if( mCurveCoords->point.getNum() )
	{
		mCurveStyle->lineWidth.setValue(width.getValue());
		mCurveStyle->linePattern.setValue(style.getValue());
		mCurveColor->rgb.setValue(color.getValue());
		mCurveSeparator->GLRender( action );
	}

	glPopAttrib();
}
