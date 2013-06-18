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

// AvtUtil.cpp : Defines the entry point for the DLL application.
//

#include "SoIALoadDcmSegObject.h"
#include "SoIAParseString.h"

#include "SoROITransform.h"
#include "SoMaskContour.h"
#include "SoMaskEditManip.h"

#include "SoDrawLine.h"
#include "SoROIVolume.h"

#include "SoItkImageToXipMask.h"
#include "SoXipImageToItkImage.h"

#include "SoDcmSegObject.h"
#include "SoVolumeMetrics.h"
#include "SoResampleVolume.h"

#include "SoBiorthogonalLine.h"

#include "SoMap2ImagePt.h"
#include "SoNormalizeImagePt.h"

#include "SoNormalizeContour.h"
#include "SoAlignVolumeMask.h"
#include "SoContourVoxelizer.h"
#include "SoLoadContour.h"

#include "SoGetImageInfor.h"

#include "SoIABinaryDilate.h"
#include "SoIAPreprocess.h"
#include "SoIAPostprocess.h"

int init()
{
	SoIALoadDcmSegObject::initClass();
	SoIAParseString::initClass();
	SoROITransform::initClass();

	SoMaskContour::initClass();
	SoMaskEditManip::initClass();

	SoDrawLine::initClass();
	SoROIVolume::initClass();

	SoItkImageToXipMask::initClass();
	SoXipImageToItkImage::initClass();

	SoDcmSegObject::initClass();
	SoVolumeMetrics::initClass();
	SoResampleVolume::initClass();

	SoBiorthogonalLine::initClass();

	SoMap2ImagePt::initClass();
	SoNormalizeImagePt::initClass();

	SoNormalizeContour::initClass();
	SoAlignVolumeMask::initClass();

	SoContourVoxelizer::initClass();
	SoLoadContour::initClass();

	SoGetImageInfor::initClass();

	SoIABinaryDilate::initClass();
	SoIAPreprocess::initClass();
	SoIAPostprocess::initClass();

	return 0;
}

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
 	if( ul_reason_for_call == DLL_PROCESS_ATTACH )
		init();

	return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

