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
*	@file    DCEPerfScanFill_Hazard..cpp
*	@brief   the implementation of utility functions to pixelize a 2D polygon into a 2D pixel buffer. Based on code from Graphics Gems I, Concave Polygon Scan Conversion by Paul S. Heckbert.
*	@author  Michael Caylus
**/

#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFInt32.h>

void scanFill( const SoMFVec2f& points2D, const SoMFInt32& index, short* pixelBuffer[], int width, int height );
