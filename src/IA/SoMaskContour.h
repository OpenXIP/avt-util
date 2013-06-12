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
*	@file    SoMaskContour.h
*	@brief   extract and display the volume contour from the volume mask
*	@author  Jie Zheng
**/

#pragma once

#include <xip/inventor/core/SoXipKit.h>
#include <Inventor/SoLists.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoMFNode.h>
#include <xip/inventor/overlay/SoXipShape.h>

#include "Inventor/fields/SoSFMatrix.h"
#include "Inventor/fields/SoMFVec3f.h"
#include "Inventor/fields/SoMFVec2f.h"
#include "Inventor/Fields/SoSFUShort.h"
#include "Inventor/Fields/SoSFInt32.h"
#include "Inventor/SbLinear.h"

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>

#include <vector>
using namespace std;

class __declspec(dllexport) SoMaskContour : public SoXipKit
{
	SO_NODE_HEADER( SoMaskContour );

	SO_XIP_KIT_ENTRY_HEADER( mTopSeparator );
	SO_XIP_KIT_ENTRY_HEADER( mGeomSeparator );

	SO_XIP_KIT_TYPE_ENTRY_HEADER( mShapeSwitch, SoSwitch );
	SO_XIP_KIT_ENTRY_HEADER( mShapeList );

public:
	SoMaskContour(void);

    /// Class name of the next shape to be created
	SoSFString			shapeClassName;
    /// Label of the next shape to be created
	SoMFString			shapeLabel;
    /// Caption of the next shape to be created
	SoSFString			shapeCaption;

	SoXipSFDataImage	volMask;
	SoSFMatrix			refModelMatrix;
	SoSFInt32			refWidth;
	SoSFInt32			refHeight;
	SoSFInt32			refDepth;

	SoSFEnum			orientation;
	SoSFMatrix			plane;

	SoMFVec3f			concavePoints;
	SoSFBool			bInside;
	SoSFTrigger			undo;

	enum Orientation {
		AXIAL,
		SAGITTAL,
		CORONAL,
		NONE,
	};

    /// Class initialization
	static void initClass();

    /// Create a new shape given shapeClassName, shapeLabel and shapeCaption
	SoXipShape*  createNewShape();

    /// Internal.
    /// Get a pointer to the internal list of shape.
	virtual class SoXipShapeList* getCurrentList();	

private:
	~SoMaskContour(void);

	/// Point list of the shape
	SoMFVec3f			points;

	/// Compute the next rank available. Each overlay is enumerated starting from 1.
	/// Return the smallest available index.
	virtual int getNextRank();

    /// Set up the sensors on internal nodes 
    virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );	

    /// Event manager
	virtual void handleEvent( SoHandleEventAction* action );	

	/// Returns the picked shape, null if none were picked
	SoXipShape* isShapePicked( SoHandleEventAction* action );

    /// Current overlay selection
	SoNodeList			mSelection;
	int					mPickedControlPoint;
	SbVec2s				mMousePosition;
	SoNode*				mActionNode;

	virtual void addOverlays();
	virtual void clearOverlays();

private:	
	static void fieldSensorCB( void* userData, SoSensor* );

	SoFieldSensor*		mFieldSensors[4];

	//used for undo
	int					mPos;
	unsigned char*		mMaskBuffer;

protected:
	float			intersectVolume(SbMatrix &maskMat, SbMatrix &volMat, SbMatrix &planeMat, float uint, Orientation iType);
	bool			updateContour(SoMFVec3f &vertex, float fPosition, Orientation iType);

	template< typename T > bool	extractContour(SoMFVec2f &points, T *pVol,int nX, int nY, int nZ, float fPos, Orientation nType);
	bool			transformCoords(SoMFVec3f &vertexList, SoMFVec2f &points, SbMatrix &maskMatrix, SbMatrix &volMatrix, float position, Orientation iType);
	bool			sortPoints(SoMFVec2f &points);

	void			getPolarParams(SoMFVec2f &points, SbVec2f &center);
	bool			sortPoints(SoMFVec2f &points, SbVec2f &center);

protected:
	bool			processMask();
	float			intersectMask(SbMatrix &maskMat, SbMatrix &volMat, float uint, float fPosition);
	bool			convertPoints(SoMFVec2f &point2D, SoMFInt32 &coordIndex, const SoMFVec3f& points3D, SbMatrix &maskMat, SbMatrix &volMat, float uint);
	bool			updateMask(unsigned char* pMask, const SoMFVec2f& point2D, const SoMFInt32& coordIndex, int width, int height, int depth, float fPos);

protected:
	bool			undoEdit();
};
