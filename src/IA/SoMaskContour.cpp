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

/* author Jie Zheng */
/* 2009-12-09 */

#include "SoMaskContour.h"

#include <assert.h>
#include <vector>

#include <xip/system/standard.h>

#ifdef WIN32
# include <winuser.h>
#endif

#include <xip/inventor/core/SoXipCursor.h>

#include <Inventor/SoPickedPoint.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/errors/SoMemoryError.h>

#include <xip/inventor/overlay/SoXipEditableShape.h>
#include <xip/inventor/overlay/SoXipOverlayManipBase.h>
#include <xip/inventor/overlay/XipOverlayUtils.h>
#include <xip/system/defines.h>

#include "SoXipShapeList.h"
#include "DCEPerfScanFill_Hazard.h"

#include <map>
#include <algorithm>
using namespace std;



const float EPSILON = 0.0000001;
const float PI = 3.1415962;
#define SAFE_DELETE_ARRAY(ptr) if( ptr ) { delete [] ptr; ptr = 0; }

bool compare_theta(const float theta1, const float theta2)
{
	if (fabs(theta1 - theta2) > EPSILON)
		return true;

	return false;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_NODE_SOURCE( SoMaskContour );

void SoMaskContour::initClass()
{
	SO_NODE_INIT_CLASS( SoMaskContour, SoXipKit, "SoXipKit" );
}

SoMaskContour::SoMaskContour(void)
{
	SO_NODE_CONSTRUCTOR( SoMaskContour );

	// Main separators
	SO_XIP_KIT_ADD_ENTRY( mTopSeparator, SoSeparator, this );
	SO_XIP_KIT_ADD_ENTRY( mGeomSeparator, SoSeparator, mTopSeparator );
	// Shapes
	SO_XIP_KIT_ADD_TYPE_ENTRY( mShapeSwitch, SoSwitch, mGeomSeparator );
	SO_XIP_KIT_ADD_ENTRY( mShapeList, SoXipShapeList, mShapeSwitch );

	mShapeSwitch->whichChild.setValue(0);

	SO_NODE_ADD_FIELD( shapeClassName, ("SoXipContour") );
	SO_NODE_ADD_FIELD(     shapeLabel,             ("") );
	SO_NODE_ADD_FIELD(   shapeCaption,             ("") );

	SO_NODE_ADD_FIELD( volMask, (NULL) );
	SO_NODE_ADD_FIELD( refModelMatrix, (SbMatrix::identity()) );
	SO_NODE_ADD_FIELD( refWidth, (0) );
	SO_NODE_ADD_FIELD( refHeight, (0) );
	SO_NODE_ADD_FIELD( refDepth, (0) );

	SO_NODE_ADD_FIELD(orientation, (AXIAL));

	SO_NODE_DEFINE_ENUM_VALUE(Orientation, AXIAL);
	SO_NODE_DEFINE_ENUM_VALUE(Orientation, SAGITTAL);
	SO_NODE_DEFINE_ENUM_VALUE(Orientation, CORONAL);
	SO_NODE_SET_SF_ENUM_TYPE(orientation, Orientation);

	SO_NODE_ADD_FIELD( plane, (SbMatrix::identity()) );

	SO_NODE_ADD_FIELD( concavePoints, (SbVec3f(0,0,0)) );
	concavePoints.setNum(0);

	SO_NODE_ADD_FIELD( bInside, (true) );
	SO_NODE_ADD_FIELD( undo, () );

	shapeLabel.setNum(0);
//	points.setNum(0);

	SoField* watchFields[] = { &volMask, &plane, &concavePoints, &undo };

	for( int i = 0; i < 4; ++ i )
	{
		mFieldSensors[i] = new SoFieldSensor( fieldSensorCB, this );
		mFieldSensors[i]->attach( watchFields[i] );
		mFieldSensors[i]->setPriority(0);
	}

	mPos = 0;
	mMaskBuffer = NULL;

	setUpConnections( TRUE, TRUE );

	mActionNode = 0;

	// Force the manager to propagate the search action through its children
	// This allows the manipulators to get the overlays by using a search action
	//
	setSearchingChildren( TRUE );
}

SoMaskContour::~SoMaskContour(void)
{
	for( int i = 0; i < 4; ++ i )
	{
		delete mFieldSensors[i];
		mFieldSensors[i] = 0;
	}

	SAFE_DELETE_ARRAY(mMaskBuffer);
}

SbBool SoMaskContour::setUpConnections( SbBool onOff, SbBool doItAlways )
{
    if( !doItAlways && connectionsSetUp == onOff )
		return onOff;

	try
	{
		if ( onOff )
		{
			// We connect AFTER base class.
			SoXipKit::setUpConnections( onOff, FALSE );
		}
		else
		{
			// We disconnect BEFORE base class.
			SoXipKit::setUpConnections( onOff, FALSE );
		}
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Cannot setup connections" );
		return true;
	}

    return !( connectionsSetUp = onOff );
}

SoXipShape* SoMaskContour::isShapePicked( SoHandleEventAction* action )
{
	SoRayPickAction pa( action->getViewportRegion() );
	pa.setPoint( action->getEvent()->getPosition() );
	pa.setRadius( 3 );
	pa.setPickAll( TRUE );
	pa.enableCulling( FALSE );
	pa.apply( action->getNodeAppliedTo() );

	SoPickedPointList pickedPoints = pa.getPickedPointList();
	for( int i = 0; i < pickedPoints.getLength(); ++ i )
	{
		SoPath* path = pickedPoints[i]->getPath();
		if( !path->containsNode( this ) )
			continue ;
		
		SoFullPath* fullpath = (SoFullPath *) path;
		for( int i = 0; i < fullpath->getLength(); ++ i )
		{
			if( fullpath->getNode(i)->isOfType( SoXipShape::getClassTypeId() ) )
				return (SoXipShape *) fullpath->getNode(i);
		}
	}
	return 0;
}

void SoMaskContour::handleEvent( SoHandleEventAction* action )
{
	if( action->isHandled() )
		return ;

	const SoEvent* event = action->getEvent();
	if( !event )
		return ;

	SoNode::handleEvent( action );
}

int SoMaskContour::getNextRank()
{
	SoNodeList shapes = XipOverlayUtils::getTopLevelShapes( getCurrentList() );

	int numShapes = shapes.getLength();
	if( numShapes == 0 )
		return 1;
	
	std::vector< int > ranks(numShapes, 1);
	for( int i = 0; i < numShapes; ++ i )
	{
		ranks[i] = ((SoXipShape *) shapes[i])->rank.getValue();
	}

	std::sort( ranks.begin(), ranks.end() );

	for( int j = 0 ; j < numShapes; ++ j )
	{
		if( ranks[j] > j + 1 )
			return j + 1;
	}

	return numShapes + 1;
}

SoXipShape* SoMaskContour::createNewShape()
{
	const SbString& classname = shapeClassName.getValue();

	SoXipShapeList* currentList = getCurrentList();

	if( currentList )
	{
		SoType type = SoType::fromName( classname );
		if( !type.canCreateInstance() )
		{
			SoDebugError::post( __FILE__, "Unknown shape type '%s'", classname  );
			return 0;
		}

		if( !type.isDerivedFrom( SoXipShape::getClassTypeId() ) )
		{
			SoDebugError::post( __FILE__, "Invalid shape class '%s'", classname );
			return 0;
		}

		SoXipEditableShape* newShape = (SoXipEditableShape *) type.createInstance();
		if( !newShape )
		{
			SoDebugError::post( __FILE__, "Shape creation failed" );
			return 0;
		}
		newShape->point.setNum( points.getNum() );
		newShape->point.setValues( 0, points.getNum(), points.getValues(0) );

		newShape->closed = true;
		
		currentList->addChild( newShape );

		return newShape;
	}

	return 0;
}

void SoMaskContour::fieldSensorCB( void* userData, SoSensor* sensor )
{
	SoMaskContour* manager = (SoMaskContour *) userData;
	SoField* whichField = ((SoFieldSensor *) sensor)->getAttachedField();

	if( whichField == &manager->plane || whichField == &manager->volMask )
		manager->addOverlays();

	if( whichField == &manager->concavePoints )
		manager->processMask();

	if( whichField == &manager->undo )
		manager->undoEdit();
}

SoXipShapeList* SoMaskContour::getCurrentList()
{
	return (SoXipShapeList *) mShapeList;
}

void SoMaskContour::addOverlays()
{
	clearOverlays();
	points.setNum(0);

	SoXipDataImage* maskData = volMask.getValue();
	if (!maskData || !maskData->get())
		return;

	SbMatrix matMask = maskData->get()->getModelMatrix();
	SbMatrix matVolume = refModelMatrix.getValue();
	SbMatrix matPlane = plane.getValue();

	int iWidth = refWidth.getValue();
	int iHeight = refHeight.getValue();
	int iDepth = refDepth.getValue();

	float fPosition = 0;
	float uint = 0;

	Orientation type = NONE;
	switch(orientation.getValue())
	{
	case AXIAL:
		type = AXIAL;
		uint = matVolume[2][2] / (float)iDepth;
		fPosition = intersectVolume(matMask, matVolume, matPlane, uint, AXIAL);
		break;

	case SAGITTAL:
		type = SAGITTAL;
		uint = matVolume[0][0] / (float)iWidth;
		fPosition = intersectVolume(matMask, matVolume, matPlane, uint, SAGITTAL);
		break;

	case CORONAL:
		type = CORONAL;
		uint = matVolume[1][1] / (float)iHeight;
		fPosition = intersectVolume(matMask, matVolume, matPlane, uint, CORONAL);
		break;

	default:
		break;
	}

	if (fPosition > EPSILON)
		updateContour(points, fPosition, type);

	if (points.getNum() > 0)
	{
		int nextRank = getNextRank();

		SoXipShape* shape = createNewShape();
		if( shape )
		{
			shape->setLabel( shapeLabel );
			shape->setRank( nextRank );
			shape->setCaption( shapeCaption.getValue() );
		}
	}
}

void SoMaskContour::clearOverlays()
{
	((SoXipShapeList *) mShapeList)->removeAllChildren();
}

float SoMaskContour::intersectVolume(SbMatrix &maskMat, SbMatrix &volMat, SbMatrix &planeMat, float uint, Orientation iType)
{
	float position = 0;

	switch (iType)
	{
	case AXIAL://axial
 		position = planeMat[3][2] * volMat[2][2] + volMat[3][2] - maskMat[3][2];

		if (position > EPSILON && (position-maskMat[2][2]) < EPSILON)
			position /= uint;
		else
			position = 0;

		break;

	case SAGITTAL://sagittal
		position = planeMat[3][0] * volMat[0][0] + volMat[3][0] - maskMat[3][0];

		if (position > EPSILON && (position-maskMat[0][0]) < EPSILON)
			position /= uint;
		else
			position = 0;

		break;

	case CORONAL://coronal
		position = planeMat[3][1] * volMat[1][1] + volMat[3][1] - maskMat[3][1];

		if (position > EPSILON && (position-maskMat[1][1]) < EPSILON)
			position /= uint;
		else
			position = 0;

		break;

	default:
		break;
	}

	return position;
}

bool SoMaskContour::updateContour(SoMFVec3f &vertex, float fPosition, Orientation iType)
{
	SoXipDataImage* maskData = volMask.getValue();
	SbXipImage* mask = maskData->get();
	if (!mask)
		return false;

	if (mask->getType() != SbXipImage::UNSIGNED_BYTE && mask->getType() != SbXipImage::UNSIGNED_SHORT)
	{
		SoDebugError::post(__FILE__, "only support the unsigned byte and unsigned short type");
		return false;
	}

	bool bRet = false;

	SbXipImageDimensions volDimension = mask->getDimStored();
	SbMatrix maskModelMatrix = mask->getModelMatrix();

	SoMFVec2f pointlist;

	if (mask->getType() == SbXipImage::UNSIGNED_BYTE)
	{
		unsigned char* maskImagePtr = (unsigned char*)mask->refBufferPtr();

		if (!extractContour(pointlist, maskImagePtr, volDimension[0], volDimension[1] , volDimension[2], fPosition, iType))
			return false;
	}
	else if (mask->getType() == SbXipImage::UNSIGNED_SHORT)
	{
		unsigned short* maskImagePtr = (unsigned short*)mask->refBufferPtr();

		if (!extractContour(pointlist, maskImagePtr, volDimension[0], volDimension[1] , volDimension[2], fPosition, iType))
			return false;
	}


	SbMatrix matPlane = plane.getValue();
	SbMatrix volMatrix = refModelMatrix.getValue();

	float pos = 0;

	switch(iType)
	{
	case AXIAL:
		pos = matPlane[3][2];
		break;

	case SAGITTAL:
		pos = matPlane[3][0];
		break;

	case CORONAL:
		pos = matPlane[3][1];
		break;

	default:
		break;
	}

	bRet = transformCoords(vertex, pointlist, maskModelMatrix, volMatrix, pos, iType);

	mask->unrefBufferPtr();
	
	return bRet;
}

//use a 3x3 template to extract the contour
////////////////////////////////////////////
//	0	-1	0
//	-1	0	1
//	0	1	0
/////////////////////////////////////////////
template< typename T > bool SoMaskContour::extractContour(SoMFVec2f &points, T *pVol,int nX, int nY, int nZ, float fPos, Orientation nType)
{
	int iPos0 = (int)floor(fPos);
	int iPos1 = (int)ceil(fPos);

	//boundary handling
	if (iPos0 == 0)
		iPos0 = 0;
	if (iPos1 == nZ)
		iPos1 = iPos0;

	switch (nType)
	{
	case AXIAL:
		if (iPos0 < 0 || iPos1 >= nZ)
			return false;
		break;

	case SAGITTAL:
		if (iPos0 < 0 || iPos1 >= nY)
			return false;
		break;

	case CORONAL:
		if (iPos0 < 0 || iPos1 >= nX)
			return false;
		break;
	}

	float fRatio = fPos - floor(fPos);

	int pos = iPos0;
//	if (fabs(fPos-iPos0) - fabs(fPos-iPos1) < EPSILON)
//		pos = iPos1;

	int nSize = nX * nY;
	T *pSlice0 = NULL;
	T *pSlice1 = NULL;
	T *pSlice = NULL;

	switch (nType)
	{
	case AXIAL://axial
		//use near neighbor interpolation 
		pSlice = pVol + pos * nSize;
		for (int j = 1; j < nY-1; j++)
		{
			for (int i = 1; i < nX-1; i++)
			{
				T y0 = *(pSlice + (j-1)*nX + i);
				T y1 = *(pSlice + (j+1)*nX + i);

				T x0 = *(pSlice + j*nX + i-1);
				T x1 = *(pSlice + j*nX + i+1);

				if ((x0 - x1) != 0 && (y0 - y1) != 0)
				{
					SbVec2f point;
					point[0] = float(i) / float(nX);
					point[1] = float(j) / float(nY);

					points.set1Value(points.getNum(), point);
				}
			}
		}

		//the linear interpolation
		//pSlice0 = pVol + iPos0 * nSize;
		//pSlice1 = pVol + iPos1 * nSize;

		//for (int j = 1; j < nY-1; j++)
		//{
		//	for (int i = 1; i < nX-1; i++)
		//	{
		//		//get the 4 neighborhoods by the linear interpolation
		//		T y00 = *(pSlice0 + (j-1)*nX + i);
		//		T y01 = *(pSlice1 + (j-1)*nX + i);
		//		T y0 = T(y00*fPos + (1.0-fPos)*y01);

		//		y00 = *(pSlice0 + (j+1)*nX + i);
		//		y01 = *(pSlice1 + (j+1)*nX + i);
		//		T y1 = T(y00*fPos + (1.0-fPos)*y01);

		//		T x00 = *(pSlice0 + j*nX + i-1);
		//		T x01 = *(pSlice1 + j*nX + i-1);
		//		T x0 = T(x00*fPos + (1.0-fPos)*x01);

		//		x00 = *(pSlice0 + j*nX + i+1);
		//		x01 = *(pSlice1 + j*nX + i+1);
		//		T x1 = T(x00*fPos + (1.0-fPos)*x01);

		//		if ((x0 - x1) != 0 || (y0 - y1) != 0)
		//		{
		//			SbVec2f point;
		//			point[0] = float(i) / float(nX);
		//			point[1] = float(j) / float(nY);

		//			points.set1Value(points.getNum(), point);
		//		}
		//	}
		//}
		break;

	case SAGITTAL: //sagittal
		for (int j = 1; j < nZ-1; j++)
		{
			pSlice0 = pVol + (j-1) * nSize;
			pSlice1 = pVol + (j+1) * nSize;
			pSlice = pVol + j * nSize;
			for (int i = 1; i < nY-1; i++)
			{
				T y0 = *(pSlice0 + i*nX + pos + 1) + *(pSlice0 + i*nX + pos - 1);
				T y1 = *(pSlice1 + i*nX + pos + 1) + *(pSlice1 + i*nX + pos - 1);

				T x0 = *(pSlice + (i-1)*nX + pos);
				T x1 = *(pSlice + (i+1)*nX + pos);

				////the linear interpolation
				//T y00 = *(pSlice0 + i*nX + iPos0);
				//T y01 = *(pSlice0 + i*nX + iPos1);
				//T y0 = T(y00*fPos + (1.0-fPos)*y01);

				//y00 = *(pSlice1 + i*nX + iPos0);
				//y01 = *(pSlice1 + i*nX + iPos1);
				//T y1 = T(y00*fPos + (1.0-fPos)*y01);

				//T x00 = *(pSlice + (i-1)*nX + iPos0);
				//T x01 = *(pSlice + (i-1)*nX + iPos1);
				//T x0 = T(x00*fPos + (1.0-fPos)*x01);

				//x00 = *(pSlice + (i+1)*nX + iPos0);
				//x01 = *(pSlice + (i+1)*nX + iPos1);
				//T x1 = T(x00*fPos + (1.0-fPos)*x01);

				if ((x0 - x1) != 0 && (y0 - y1) != 0)
				{
					SbVec2f point;
					point[0] = float(i) / float(nY);
					point[1] = float(j) / float(nZ);

					points.set1Value(points.getNum(), point);
				}
			}
		}

		break;

	case CORONAL: //coronal
		for (int j = 1; j < nZ-1; j++)
		{
			pSlice0 = pVol + (j-1) * nSize;
			pSlice1 = pVol + (j+1) * nSize;
			pSlice = pVol + j * nSize;

			for (int i = 1; i < nX-1; i++)
			{
				T y0 = *(pSlice0 + i + (pos+1)*nX) + *(pSlice0 + i + (pos-1)*nX);
				T y1 = *(pSlice1 + i + (pos+1)*nX) + *(pSlice1 + i + (pos-1)*nX);

				T x0 = *(pSlice + i-1 + pos*nX);
				T x1 = *(pSlice + i+1 + pos*nX);

				////the linear interpolation
				//T y00 = *(pSlice0 + i + iPos0*nX);
				//T y01 = *(pSlice0 + i + iPos1*nX);
				//T y0 = T(y00*fPos + (1.0-fPos)*y01);

				//y00 = *(pSlice1 + i + iPos0*nX);
				//y01 = *(pSlice1 + i + iPos1*nX);
				//T y1 = T(y00*fPos + (1.0-fPos)*y01);

				//T x00 = *(pSlice + i-1 + iPos0*nX);
				//T x01 = *(pSlice + i-1 + iPos1*nX);
				//T x0 = T(x00*fPos + (1.0-fPos)*x01);

				//x00 = *(pSlice + i+1 + iPos0*nX);
				//x01 = *(pSlice + i+1 + iPos1*nX);
				//T x1 = T(x00*fPos + (1.0-fPos)*x01);

				if ((x0 - x1) != 0 && (y0 - y1) != 0)
				{
					SbVec2f point;
					point[0] = float(i) / float(nX);
					point[1] = float(j) / float(nZ);

					points.set1Value(points.getNum(), point);
				}
			}
		}

		break;

	default:
		break;
	}

	SbVec2f centerPoint;
	getPolarParams(points, centerPoint);
	if (!sortPoints(points, centerPoint))
		return false;

	//if (!sortPoints(points))
	//	return false;

	return true;
}

//find the two end points for each horizonal line and sort them for rendering
bool SoMaskContour::sortPoints(SoMFVec2f &pointList)
{
	int iSize = pointList.getNum();
	if (iSize <= 0)
	{
//		SoDebugError::postInfo(__FILE__, "extracted point list has zero size");
		return false;
	}

	SoMFVec2f points0;
	SoMFVec2f points1;

	float xMin = pointList[0][0];
	float xMax = pointList[0][0];
	float y = pointList[0][1];

	for (int i = 1; i < iSize; i++)
	{
		SbVec2f point = pointList[i];

		if (fabs(y - point[1]) <= EPSILON)
		{
			if (xMax - point[0] < EPSILON)
				xMax = point[0];
		}
		else
		{
			points0.set1Value(points0.getNum(), SbVec2f(xMin, y));
			points1.set1Value(points1.getNum(), SbVec2f(xMax, y));

			xMin = point[0];
			xMax = point[0];
			y = point[1];
		}
	}

	int size0 = points0.getNum();
	int size1 = points1.getNum();
	if (size0 * size1 != 0)
	{
//		SoDebugError::postInfo(__FILE__, "sorting points");
		pointList.setNum(0);

		pointList.setValues(0, size0, points0.getValues(0));
		for (int i = 0; i < size1; i++)
			pointList.set1Value(pointList.getNum(), points1[size1-i-1]);

		pointList.set1Value(pointList.getNum(), points0[0]);

		return true;
	}

	return false;
}

//convert to the ploar coordinate system and sort them for rendering
bool SoMaskContour::sortPoints(SoMFVec2f &pointList, SbVec2f &center)
{
	int iSize = pointList.getNum();

	typedef pair <float, SbVec2f> Pt_Pair;
	map<float, SbVec2f, greater<float>> point_Index;
	map<float, SbVec2f, greater<float>>::iterator iter;

	for (int i = 0; i < iSize; i++)
	{
		SbVec2f vec = pointList[i] - center;
		float len = vec.length();
		float theta = atan2(vec[1], vec[0]) + PI;

		point_Index.insert(Pt_Pair(theta, pointList[i]));
	}

	pointList.setNum(0);
	for (iter = point_Index.begin(); iter != point_Index.end(); iter++)
		pointList.set1Value(pointList.getNum(), iter->second);
	
	return true;
}

void SoMaskContour::getPolarParams(SoMFVec2f &points, SbVec2f &center)
{
	SbVec2f point = SbVec2f(0, 0);
	int iSize = points.getNum();
	for (int i = 0; i < iSize; i++)
	{
		point[0] += points[i][0];
		point[1] += points[i][1];
	}

	if (iSize > 0)
	{
		point[0] /= (float)iSize;
		point[1] /= (float)iSize;
	}

	center = point;
}

bool SoMaskContour::transformCoords(SoMFVec3f &vertexList, SoMFVec2f &pointList, SbMatrix &maskMatrix, SbMatrix &volMatrix, float position, Orientation iType)
{
	int iSize = pointList.getNum();
	if (iSize <= 0)
	{
//		SoDebugError::postInfo(__FILE__, "extracted point list has zero size");
		return false;
	}

	vertexList.setNum(iSize);

	for (int i = 0; i < pointList.getNum(); i++)
	{
		SbVec3f vertex;
		SbVec2f point = pointList[i];

		float xPosition = 0, yPosition = 0, zPosition = 0;
		float xCoord = 0, yCoord = 0, zCoord = 0;

		switch (iType)
		{
		case AXIAL:
			xPosition = maskMatrix[0][0] * point[0] + maskMatrix[3][0];
			yPosition = maskMatrix[1][1] * point[1] + maskMatrix[3][1];

			xCoord = (xPosition - volMatrix[3][0]) / volMatrix[0][0];
			yCoord = (yPosition - volMatrix[3][1]) / volMatrix[1][1];
			zCoord = position;

			break;

		case SAGITTAL:
			yPosition = maskMatrix[1][1] * point[0] + maskMatrix[3][1];
			zPosition = maskMatrix[2][2] * point[1] + maskMatrix[3][2];

			xCoord = position;
			yCoord = (yPosition - volMatrix[3][1]) / volMatrix[1][1];
			zCoord = (zPosition - volMatrix[3][2]) / volMatrix[2][2];

			break;

		case CORONAL:
			xPosition = maskMatrix[0][0] * point[0] + maskMatrix[3][0];
			zPosition = maskMatrix[2][2] * point[1] + maskMatrix[3][2];

			xCoord = (xPosition - volMatrix[3][0]) / volMatrix[0][0];
			yCoord = position;
			zCoord = (zPosition - volMatrix[3][2]) / volMatrix[2][2];

			break;

		default:
			break;
		}

		vertex[0] = xCoord;
		vertex[1] = yCoord;
		vertex[2] = zCoord;

		vertexList.set1Value(i, vertex);
	}

	return true;
}

bool SoMaskContour::processMask()
{
	SbMatrix matVolume = refModelMatrix.getValue();
	
	SoXipDataImage* maskData = volMask.getValue();
	if (!maskData || !maskData->get())
	{
//		SoDebugError::postInfo(__FILE__, "input mask data is NULL");
		return false;
	}

	SbXipImage* mask = maskData->get();
	SbMatrix matMask = mask->getModelMatrix();
	SbXipImageDimensions maskDimension = mask->getDimStored();

	int nPointNum = concavePoints.getNum();
	if (nPointNum < 3)
	{
//		SoDebugError::postInfo(__FILE__, "input contour is empty");
		return false;
	}

	if (fabs(concavePoints[0][2] - concavePoints[nPointNum-1][2]) > EPSILON)
	{
		SoDebugError::postInfo(__FILE__, "input contour is invalidate");
		return false;
	}

	float uint = matVolume[2][2] / (float)refDepth.getValue();
	float pos = intersectMask(matMask, matVolume, uint, concavePoints[0][2]);
	if (pos < EPSILON)
	{
		SoDebugError::postInfo(__FILE__, "input contour is out of the mask ROI");
		return false;
	}

	SoMFVec3f _points;
	_points.setValues(0, concavePoints.getNum(), concavePoints.getValues(0));
	_points.set1Value(_points.getNum(), concavePoints[0]);

	SoMFVec2f point2D;
	SoMFInt32 coordIndex;
	uint = matVolume[0][0] / (float)refWidth.getValue();
	if (!convertPoints(point2D, coordIndex, concavePoints, matMask, matVolume, uint))
	{
		SoDebugError::postInfo(__FILE__, "input contour is out of the mask ROI");
		return false;
	}

	SAFE_DELETE_ARRAY(mMaskBuffer);

	mMaskBuffer = new unsigned char[maskDimension[0]*maskDimension[1]];

	unsigned char* pMask = (unsigned char*)mask->refBufferPtr();
	bool ret = updateMask(pMask, point2D, coordIndex, maskDimension[0], maskDimension[1], maskDimension[2], pos);
	mask->unrefBufferPtr();

	if (ret)
	{
		addOverlays();
		volMask.touch();
	}

	return ret;
}

float SoMaskContour::intersectMask(SbMatrix &maskMat, SbMatrix &volMat, float uint, float fPosition)
{
	float position = fPosition * volMat[2][2] + volMat[3][2] - maskMat[3][2];

	if (position > EPSILON && (position-maskMat[2][2]) < EPSILON)
		return (position / uint);

	return 0;
}

//convert to image space
bool SoMaskContour::convertPoints(SoMFVec2f &point2D, SoMFInt32 &coordIndex, const SoMFVec3f& points3D, SbMatrix &maskMat, SbMatrix &volMat, float uint)
{
	point2D.setNum(0);
	coordIndex.setNum(0);

	int nWidth = (int)(maskMat[0][0] / uint);
	int nHeight = (int)(maskMat[1][1] / uint);
	unsigned int numPoints = points3D.getNum();
	for (int i = 0; i < numPoints; i++)
	{
		int posX = (int)(.5 + (points3D[i][0] * volMat[0][0] + volMat[3][0] - maskMat[3][0]) / uint);
		if (posX < 0 || posX >= nWidth)
			continue;

		int posY = (int)(.5 + (points3D[i][1] * volMat[1][1] + volMat[3][1] - maskMat[3][1]) / uint);
		if (posY < 0 || posY >= nHeight)
			continue;

		SbVec2f tmp;
		tmp[0] = posX;
		tmp[1] = posY;

		point2D.set1Value(point2D.getNum(), tmp);
		coordIndex.set1Value(coordIndex.getNum(), i);
	}

	if (point2D.getNum() < 4)
		return false;

	return true;
}

bool SoMaskContour::updateMask(unsigned char* pMask, const SoMFVec2f& point2D, const SoMFInt32& coordIndex, int width, int height, int depth, float fPos)
{
	int pos0 = (int)floor(fPos);
	int pos1 = (int)ceil(fPos);
	if (pos0 < 0 || pos1 >= depth)
	{
		SoDebugError::postInfo(__FILE__, "contour's location is invalidate");
		return false;
	}

	int pos = pos0;
	//if (fabs(fPos-pos0) - fabs(fPos-pos1) < EPSILON)
	//	pos = pos1;

	// Allocate memory for pixelized image
	short *imageBuffer = new short[width * height];
	if( !imageBuffer )
	{
		SoMemoryError::post( "Image buffer" );
		return false;				
	}

	short** imageRows = new short *[height];
	if( !imageRows )
	{
		SoMemoryError::post( "Image row vectors" );

		SAFE_DELETE_ARRAY( imageRows );
		SAFE_DELETE_ARRAY( imageBuffer );
		return false;				
	}

	for( int r = 0; r < height; ++ r )
	{
		imageRows[r] = imageBuffer + (r * width);
	}

	// Reset buffer
	int nSize = width * height;
	memset( imageBuffer, 0, nSize * sizeof(unsigned short) );

	scanFill( point2D, coordIndex, imageRows, width - 1, height - 1) ;

	unsigned char *pMaskSlice = pMask + nSize * pos;
	//store to the undo buffer
	if (mMaskBuffer)
	{
		mPos = pos;
		memcpy(mMaskBuffer, pMaskSlice, nSize*sizeof(unsigned char));
	}

//	unsigned char *pBuffer = new unsigned char[nSize];
//	memset( pBuffer, 0, nSize * sizeof(unsigned char) );

	for( int r = 0; r < height; ++ r )
	for( int c = 0; c < width; ++ c )
	{
		if (imageRows[r][c])
		{
			if (bInside.getValue())
				pMaskSlice[r*width+c] = 255;
			else
				pMaskSlice[r*width+c] = 0;

//			pBuffer[r*width+c] = 255;
		}
	}

	//FILE *stream;
	//fopen_s(&stream, "C:\\temp\\mask.raw", "w+");
	//fwrite(pBuffer, sizeof(unsigned char), nSize, stream);
	//fclose(stream);

	//SAFE_DELETE_ARRAY( pBuffer );

	SAFE_DELETE_ARRAY( imageRows );
	SAFE_DELETE_ARRAY( imageBuffer );

	return true;
}

bool SoMaskContour::undoEdit()
{
	if (mMaskBuffer == NULL)
		return false;

	SoXipDataImage* maskData = volMask.getValue();
	if (!maskData || !maskData->get())
	{
		SoDebugError::postInfo(__FILE__, "input mask data is NULL");
		return false;
	}

	SbXipImage* mask = maskData->get();
	unsigned char* pMask = (unsigned char*)mask->refBufferPtr();
	SbXipImageDimensions maskDimension = mask->getDimStored();

	int nSize = maskDimension[0] * maskDimension[1];
	unsigned char *pMaskSlice = pMask + nSize * mPos;
	memcpy(pMaskSlice, mMaskBuffer, nSize*sizeof(unsigned char));
	mask->unrefBufferPtr();

	addOverlays();

	return true;
}