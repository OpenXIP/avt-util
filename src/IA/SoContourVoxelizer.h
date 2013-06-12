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
*	@file    SoContourVoxelizer.h
*	@brief   Convert the volume contour to the volume mask
*	@author  Jie Zheng
**/

#ifndef SOCONTOURVOXELIZER_H
#define SOCONTOURVOXELIZER_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFEnum.h>
#include <xip/inventor/core/SbXipImage.h>

class SoXipDataImage;


class SoContourVoxelizer : public SoEngine
{
	SO_ENGINE_HEADER( SoContourVoxelizer );

public:
	SoContourVoxelizer();

	enum PixelType
	{
		BIT_MASK,
		BYTE_MASK
	};
    
    SoMFVec3f			point;
	SoMFInt32			coordIndex;
    SoSFEnum            maskType;
	SoSFShort			width;
	SoSFShort			height;
	SoSFShort			depth;
	SoSFMatrix			modelMatrix;
	SoSFTrigger			execute;

	SoEngineOutput		mask;	// SoRadSFDataImage

	static void initClass();

protected:
	~SoContourVoxelizer();

	virtual void evaluate();	
	virtual void inputChanged( SoField* whichField );

	void getLineSpan(int &xl, int &xr, int line, SoMFVec2f &points);

private:
	SoXipDataImage*		 mMaskOutput;
	SbXipImage*			 m_maskImage;
	SbXipImageDimensions m_maskImageDimensions;
	SbBool				 m_actionNeeded;

};

#endif // SOCONTOURVOXELIZER_H
