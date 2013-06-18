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
