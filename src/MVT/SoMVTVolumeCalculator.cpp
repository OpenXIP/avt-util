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

#include "SoMVTVolumeCalculator.h"

typedef itk::Image<unsigned char, 3>					  SegmentationType;
typedef SegmentationType::Pointer                         SegmentationPointer;
typedef itk::ImageRegionIterator<SegmentationType>        IteratorType;

typedef itk::Point<float,3>                               PointType;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoMVTVolumeCalculator );

SoMVTVolumeCalculator::SoMVTVolumeCalculator(void)
{
	SO_ENGINE_CONSTRUCTOR( SoMVTVolumeCalculator );

	// Enumerations
	SO_ENGINE_DEFINE_ENUM_VALUE( DataType, UNSIGNED_SHORT );
	SO_ENGINE_DEFINE_ENUM_VALUE( DataType, UNSIGNED_CHAR );
	SO_ENGINE_SET_SF_ENUM_TYPE( Type, DataType );

	// Inputs
	SO_ENGINE_ADD_INPUT( inputVolume, (0) );
	SO_ENGINE_ADD_INPUT( refVolume, (0) );
	SO_ENGINE_ADD_INPUT( process, () );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( volumeSeg, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( volumeRef, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( volumeDif, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( volumeDifPerc, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( volumeDifPercAbs, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( tanimotoError, SoSFFloat );

	volumeFactor = 1.0;

	_volumeSeg = 0.0;
	_volumeRef = 0.0;
	_volumeDif = 0.0;
	_volumeDifPerc = 0.0;
	_volumeDifPercAbs = 0.0;
	_tanimotoError = 0.0;
}

void 
SoMVTVolumeCalculator::initClass()
{
	SO_ENGINE_INIT_CLASS( SoMVTVolumeCalculator, SoEngine, "SoEngine" );
}

SoMVTVolumeCalculator::~SoMVTVolumeCalculator(void)
{
}

void 
SoMVTVolumeCalculator::inputChanged (SoField* whichField)
{
	if (whichField == &process)
	{
		if (validateInput())
		{
			calculateVolumeMeasures();
		}
	}
}

void
SoMVTVolumeCalculator::evaluate()
{	
	SO_ENGINE_OUTPUT( volumeSeg, SoSFFloat, setValue( _volumeSeg ) );
	SO_ENGINE_OUTPUT( volumeRef, SoSFFloat, setValue( _volumeRef ) );
	SO_ENGINE_OUTPUT( volumeDif, SoSFFloat, setValue( _volumeDif ) );
	SO_ENGINE_OUTPUT( volumeDifPerc, SoSFFloat, setValue( _volumeDifPerc ) );
	SO_ENGINE_OUTPUT( volumeDifPercAbs, SoSFFloat, setValue( _volumeDifPercAbs ) );
	SO_ENGINE_OUTPUT( tanimotoError, SoSFFloat, setValue( _tanimotoError ) );
}

bool SoMVTVolumeCalculator::validateInput()
{
	if (!inputVolume.getValue() || !refVolume.getValue())
		return false;

	// check if images have the same size
    SoItkDataImage* resultImage = inputVolume.getValue();
    SoItkDataImage* referenceImage = refVolume.getValue();

	if( resultImage->getNumDimension() != 3 || referenceImage->getNumDimension() != 3 )
	{
		SoDebugError::post( __FILE__, "Image dimension not supported yet" );
		SoDebugError::post( __FILE__, "Only works with volume data" );
		return false;
	}

	SegmentationType* itkResultImage = static_cast< SegmentationType* >( resultImage->getPointer() );
	SegmentationType::RegionType resRegion = itkResultImage->GetLargestPossibleRegion();

	SegmentationType* itkValidationImage = static_cast< SegmentationType* >( referenceImage->getPointer() );
	SegmentationType::RegionType valRegion = itkValidationImage->GetLargestPossibleRegion();

	if (resRegion.GetSize() != valRegion.GetSize())
	{
		SoDebugError::post( __FILE__, "Image format not supported yet" );
		SoDebugError::post( __FILE__, "Only works with UNSIGNED_SHORT" );
		return false;
	}

	SegmentationType::SpacingType valSpacing = itkValidationImage->GetSpacing();
	volumeFactor = 0.001*valSpacing[0]*valSpacing[1]*valSpacing[2];
	SegmentationType::SpacingType resSpacing = itkResultImage->GetSpacing();
	if (resSpacing[0]!=valSpacing[0] || resSpacing[1]!=valSpacing[1] || resSpacing[2]!=valSpacing[2]) 
	{
		SoDebugError::post( __FILE__, "WARNING: Spacing of segmentation different from reference! Adjusting values..." );
	}

	return true;
}

void SoMVTVolumeCalculator::calculateVolumeMeasures()
{
	SoItkDataImage* resultImage = inputVolume.getValue();
	SegmentationType* itkResultImage = static_cast< SegmentationType* >( resultImage->getPointer() );

	SoItkDataImage* referenceImage = refVolume.getValue();
	SegmentationType* itkValidationImage = static_cast< SegmentationType* >( referenceImage->getPointer() );

	// Tanimoto overlap metric
	SegmentationType::RegionType resRegion = itkResultImage->GetLargestPossibleRegion();
	SegmentationType::RegionType valRegion = itkValidationImage->GetLargestPossibleRegion();

	unsigned long volume1=0, volume2=0, intersection=0;
	IteratorType resIt( itkResultImage, resRegion ), valIt( itkValidationImage, valRegion );
	for ( resIt.GoToBegin(), valIt.GoToBegin(); !resIt.IsAtEnd(); ++resIt, ++valIt ) {
	if (resIt.Get()!=0) {
	  volume1++;
	  if (valIt.Get()!=0) {
		volume2++;
		intersection++;
	  }
	}
	else {
	  if (valIt.Get()!=0) volume2++;
	}
	}
	float tanimotoVal = 100.0 * (double)(intersection) / ((double)(volume1+volume2-intersection));
	_tanimotoError = tanimotoVal;
	_volumeSeg = (double)volume1 * volumeFactor;
	_volumeRef = (double)volume2 * volumeFactor;
	_volumeDif = _volumeSeg - _volumeRef;
	_volumeDifPerc = 100.0 * _volumeDif / _volumeRef;
	_volumeDifPercAbs = fabs(_volumeDifPerc);
}
