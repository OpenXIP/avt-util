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

#include "SoNormalizeContour.h"

const float EPSILON = 0.000001;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoNormalizeContour );

SoNormalizeContour::SoNormalizeContour(void)
{
	SO_ENGINE_CONSTRUCTOR( SoNormalizeContour );

	// Inputs
	SO_ENGINE_ADD_INPUT( voxelPosition, (SbVec3f(0, 0, 0)) );
	SO_ENGINE_ADD_INPUT( voxelDirection, (SbVec3f(0, 0, 0)) );
	SO_ENGINE_ADD_INPUT( voxelSpacing, (SbVec3f(0, 0, 0)) );
	SO_ENGINE_ADD_INPUT( width, (512) );
	SO_ENGINE_ADD_INPUT( height, (512) );
	SO_ENGINE_ADD_INPUT( depth, (0) );
	SO_ENGINE_ADD_INPUT( point, (SbVec2f(0, 0)) );
	SO_ENGINE_ADD_INPUT( coordIndex, (0) );
	SO_ENGINE_ADD_INPUT( execute, () );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( modelMatrix, SoSFMatrix );
	SO_ENGINE_ADD_OUTPUT( maskWidth,   SoSFInt32 );
	SO_ENGINE_ADD_OUTPUT( maskHeight,  SoSFInt32 );
	SO_ENGINE_ADD_OUTPUT( maskDepth,   SoSFInt32 );
	SO_ENGINE_ADD_OUTPUT( pointList,   SoMFVec3f );
	SO_ENGINE_ADD_OUTPUT( pointIndex,   SoMFInt32 );
}

void SoNormalizeContour::initClass()
{
	SO_ENGINE_INIT_CLASS( SoNormalizeContour, SoEngine, "SoEngine" );
}

SoNormalizeContour::~SoNormalizeContour(void)
{
}

void SoNormalizeContour::inputChanged (SoField* whichField)
{
	if (whichField == &execute)
	{
		if (validateInputs())
		{
			int _width = 0, _height = 0, _depth = 0;
			SbVec3f _position = SbVec3f(0, 0, 0);
			if (normailzePoints(_position, _width, _height, _depth))
				buildModelmatrix(_position, _width, _height, _depth);
		}
	}
}

void SoNormalizeContour::evaluate()
{
}

bool SoNormalizeContour::validateInputs()
{
	if (voxelPosition.getValue() == SbVec3f(0, 0, 0) || voxelDirection.getNum() != 2 || voxelSpacing.getValue() == SbVec3f(0, 0, 0))
		return false;

	if (width.getValue() * height.getValue() * depth.getValue() == 0)
		return false;

	if (point.getNum() < 3 || coordIndex.getNum() < 3)
		return false;

	return true;
}

bool SoNormalizeContour::buildModelmatrix(SbVec3f &_position, int _width, int _height, int _depth)
{
	SbMatrix _modelMatrix = SbMatrix::identity();

	SbVec3f colDir = voxelDirection[0];
	SbVec3f rowDir = voxelDirection[1];
	SbVec3f norDir = colDir.cross(rowDir);

	SbVec3f spacing = voxelSpacing.getValue();
	_modelMatrix[0][0] = _width * spacing[0] * colDir[0];
	_modelMatrix[0][1] = _width * spacing[0] * colDir[1];
	_modelMatrix[0][2] = _width * spacing[0] * colDir[2];
	_modelMatrix[0][3] = 0;

	_modelMatrix[1][0] = _height * spacing[1] * rowDir[0];
	_modelMatrix[1][1] = _height * spacing[1] * rowDir[1];
	_modelMatrix[1][2] = _height * spacing[1] * rowDir[2];
	_modelMatrix[1][3] = 0;

	_modelMatrix[2][0] = _depth * spacing[2] * norDir[0];
	_modelMatrix[2][1] = _depth * spacing[2] * norDir[1];
	_modelMatrix[2][2] = _depth * spacing[2] * norDir[2];
	_modelMatrix[2][3] = 0;

	_modelMatrix[3][0] = _position[0];
	_modelMatrix[3][1] = _position[1];
	_modelMatrix[3][2] = _position[2];
	_modelMatrix[3][3] = 0;

	SO_ENGINE_OUTPUT( modelMatrix, SoSFMatrix, setValue( _modelMatrix ) );

	return true;
}

bool SoNormalizeContour::normailzePoints(SbVec3f &_position, int &_width, int &_height, int &_depth)
{
	int nSize = point.getNum();
	SbVec3f _volSpacing = voxelSpacing.getValue();
	SbVec3f _volPosition = voxelPosition.getValue();

	SbVec2f offset = SbVec2f(16, 16);

	SbVec2f range_min = SbVec2f(width.getValue(), height.getValue());
	SbVec2f range_max = SbVec2f(0, 0);

	for (int i = 0; i < nSize; i++)
	{
		if (point[i].length() - range_min.length() < EPSILON)
			range_min = point[i];

		if (point[i].length() - range_max.length() > EPSILON)
			range_max = point[i];
	}

	range_min -= offset;
	if (range_min[0] < EPSILON)
		range_min[0] = 0;
	if (range_min[1] < EPSILON)
		range_min[1] = 0;

	range_max += offset;
	if (range_max[0] > width.getValue())
		range_max[0] = width.getValue();
	if (range_max[1] > height.getValue())
		range_max[1] = height.getValue();

	_position[0] = range_min[0] * _volSpacing[0] + _volPosition[0];
	_position[1] = range_min[1] * _volSpacing[1] + _volPosition[1];
	_position[2] = _volPosition[2];

	_width = range_max[0] - range_min[0];
	_height = range_max[1] - range_min[1];
	_depth = depth.getValue();

	SoMFVec3f _points;
	SoMFInt32 _coordIndex;
	int index = 0;
	for (int i = 0; i < nSize; i++)
	{
		SbVec3f _point;
		_point[0] = (float)(point[i][0] - range_min[0]) / (float)_width;
		_point[1] = (float)(point[i][1] - range_min[1]) / (float)_height;
		_point[2] = (float)(coordIndex[i]) / (float)_depth;

		_points.set1Value(_points.getNum(), _point);

		index++;

		if ((i+1) < nSize)
		{
			if (coordIndex[i+1] != coordIndex[i])
			{
				_coordIndex.set1Value(_coordIndex.getNum(), index);
				index = 0;
			}
		}
	}
	_coordIndex.set1Value(_coordIndex.getNum(), index);

	SO_ENGINE_OUTPUT( pointList, SoMFVec3f, setNum(_points.getNum()) );	
	SO_ENGINE_OUTPUT( pointList, SoMFVec3f, setValues(0, _points.getNum(), _points.getValues(0)) );	

	SO_ENGINE_OUTPUT( pointIndex, SoMFInt32, setNum(_coordIndex.getNum()) );	
	SO_ENGINE_OUTPUT( pointIndex, SoMFInt32, setValues(0, _coordIndex.getNum(), _coordIndex.getValues(0)) );	

	SO_ENGINE_OUTPUT( maskWidth, SoSFInt32, setValue( _width ) );
	SO_ENGINE_OUTPUT( maskHeight, SoSFInt32, setValue( _height ) );
	SO_ENGINE_OUTPUT( maskDepth, SoSFInt32, setValue( _depth ) );

	return true;
}
