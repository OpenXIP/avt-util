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
