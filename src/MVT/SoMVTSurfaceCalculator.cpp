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

#include "SoMVTSurfaceCalculator.h"

typedef itk::Image<unsigned char, 3>					  SegmentationType;
typedef SegmentationType::Pointer                         SegmentationPointer;
typedef itk::ImageRegionIterator<SegmentationType>        IteratorType;

typedef itk::BinaryBallStructuringElement<char, 3>        StructuringType;
typedef itk::BinaryErodeImageFilter<SegmentationType, 
  SegmentationType, StructuringType>                      ErodeFilterType;
typedef itk::BinaryThresholdImageFilter< SegmentationType,
  SegmentationType>                                       ThreshFilterType;
typedef itk::SubtractImageFilter<SegmentationType, 
  SegmentationType, SegmentationType>                     SubFilterType;

typedef itk::Point<float,3>                               PointType;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoMVTSurfaceCalculator );

SoMVTSurfaceCalculator::SoMVTSurfaceCalculator(void)
{
	SO_ENGINE_CONSTRUCTOR( SoMVTSurfaceCalculator );

	// Inputs
	SO_ENGINE_ADD_INPUT( inputVolume, (0) );
	SO_ENGINE_ADD_INPUT( refVolume, (0) );
	SO_ENGINE_ADD_INPUT( process, () );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( avgDistance, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( avgSqrDistance, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( maxDistance, SoSFFloat );

	_avgDistance = 0.0;
	_avgSqrDistance = 0.0;
	_maxDistance = 0.0;
}

void 
SoMVTSurfaceCalculator::initClass()
{
	SO_ENGINE_INIT_CLASS( SoMVTSurfaceCalculator, SoEngine, "SoEngine" );
}

SoMVTSurfaceCalculator::~SoMVTSurfaceCalculator(void)
{
}

void SoMVTSurfaceCalculator::inputChanged (SoField* whichField)
{
	if (whichField == &process)
	{
		if (validateInput())
		{
			calculateSurfaceMeasures();
		}
	}
}

void
SoMVTSurfaceCalculator::evaluate()
{	
	SO_ENGINE_OUTPUT( avgDistance, SoSFFloat, setValue( _avgDistance ) );
	SO_ENGINE_OUTPUT( avgSqrDistance, SoSFFloat, setValue( _avgSqrDistance ) );
	SO_ENGINE_OUTPUT( maxDistance, SoSFFloat, setValue( _maxDistance ) );
}

bool SoMVTSurfaceCalculator::validateInput()
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
		SoDebugError::post( __FILE__, "Only works with UNSIGNED_CHAR" );
		return false;
	}

	return true;
}

void SoMVTSurfaceCalculator::calculateSurfaceMeasures()
{
	SoItkDataImage* resultImage = inputVolume.getValue();
	SegmentationType* itkResultImage = static_cast< SegmentationType* >( resultImage->getPointer() );

	SoItkDataImage* referenceImage = refVolume.getValue();
	SegmentationType* itkValidationImage = static_cast< SegmentationType* >( referenceImage->getPointer() );

	// initialization
	StructuringType structuringBall;
	structuringBall.SetRadius( 1 );
	structuringBall.CreateStructuringElement();
	ThreshFilterType::Pointer threshFilter1 = ThreshFilterType::New();
	threshFilter1->SetLowerThreshold(1);
	threshFilter1->SetUpperThreshold(255);
	threshFilter1->SetOutsideValue (0);
	threshFilter1->SetInsideValue (1);
	ErodeFilterType::Pointer erodeFilter1 = ErodeFilterType::New();
	erodeFilter1->SetInput( threshFilter1->GetOutput() );
	erodeFilter1->SetKernel( structuringBall );
	erodeFilter1->SetErodeValue( 1 );
	SubFilterType::Pointer subFilter1 = SubFilterType::New();
	subFilter1->SetInput2( erodeFilter1->GetOutput() );
	ThreshFilterType::Pointer threshFilter2 = ThreshFilterType::New();
	threshFilter2->SetLowerThreshold(1);
	threshFilter2->SetUpperThreshold(255);
	threshFilter2->SetOutsideValue (0);
	threshFilter2->SetInsideValue (1);
	ErodeFilterType::Pointer erodeFilter2 = ErodeFilterType::New();
	erodeFilter2->SetInput( threshFilter2->GetOutput() );
	erodeFilter2->SetKernel( structuringBall );
	erodeFilter2->SetErodeValue( 1 );
	SubFilterType::Pointer subFilter2 = SubFilterType::New();
	subFilter2->SetInput2( erodeFilter2->GetOutput() );

	PointType pnt;

	// compute border pixels and init kd-tree for image 1
	threshFilter1->SetInput( itkResultImage );
	subFilter1->SetInput1( threshFilter1->GetOutput() );
	subFilter1->UpdateLargestPossibleRegion();
	SegmentationPointer borderImg1 = subFilter1->GetOutput();

	IteratorType it1( borderImg1, borderImg1->GetLargestPossibleRegion() );
	unsigned int numBorderPts1 = 0;
	for ( it1.GoToBegin(); !it1.IsAtEnd(); ++it1 ) {
	if (it1.Get() != 0) numBorderPts1++;
	}
	ANNpointArray borderPts1 = annAllocPts( numBorderPts1, 3 );
	numBorderPts1 = 0;
	for ( it1.GoToBegin(); !it1.IsAtEnd(); ++it1 ) {
	if (it1.Get() != 0) {
	  itkValidationImage->TransformIndexToPhysicalPoint( it1.GetIndex(), pnt );
	  for (int d=0; d<3; d++) borderPts1[numBorderPts1][d] = pnt[d];
	  numBorderPts1++;
	}
	}
	ANNkd_tree *borderTree1 = new ANNkd_tree( borderPts1, numBorderPts1, 3 );

	// compute border pixels and init kd-tree for image 2
	threshFilter2->SetInput( itkValidationImage );
	subFilter2->SetInput1( threshFilter2->GetOutput() );
	subFilter2->UpdateLargestPossibleRegion();
	SegmentationPointer borderImg2 = subFilter2->GetOutput();
	IteratorType it2( borderImg2, borderImg2->GetLargestPossibleRegion() );
	unsigned int numBorderPts2 = 0;
	for ( it2.GoToBegin(); !it2.IsAtEnd(); ++it2 ) {
	if (it2.Get() != 0) numBorderPts2++;
	}
	ANNpointArray borderPts2 = annAllocPts( numBorderPts2, 3 );
	numBorderPts2 = 0;
	for ( it2.GoToBegin(); !it2.IsAtEnd(); ++it2 ) {
	if (it2.Get() != 0) {
	  itkValidationImage->TransformIndexToPhysicalPoint( it2.GetIndex(), pnt );
	  for (int d=0; d<3; d++) borderPts2[numBorderPts2][d] = pnt[d];
	  numBorderPts2++;
	}
	}
	ANNkd_tree *borderTree2 = new ANNkd_tree( borderPts2, numBorderPts2, 3 );

	// calculate surface distance measures
	_avgDistance = 0;
	_avgSqrDistance = 0;
	_maxDistance = 0;
	ANNidxArray  nnIdx = new ANNidx[1];
	ANNdistArray dists = new ANNdist[1];

	for(unsigned int idx1=0; idx1<numBorderPts1; idx1++) {
	borderTree2->annkSearch( borderPts1[idx1], 1, nnIdx, dists);
	_avgSqrDistance += dists[0];
	double d = sqrt( dists[0] );
	_avgDistance += d;
	if (d>_maxDistance) _maxDistance = d;
	}

	for(unsigned int idx2=0; idx2<numBorderPts2; idx2++) {
	borderTree1->annkSearch( borderPts2[idx2], 1, nnIdx, dists);
	_avgSqrDistance += dists[0];
	double d = sqrt( dists[0] );
	_avgDistance += d;
	if (d>_maxDistance) _maxDistance = d;
	}

	double numBorderPts = numBorderPts1 + numBorderPts2;
	_avgDistance /= numBorderPts;
	_avgSqrDistance /= numBorderPts;
	_avgSqrDistance = sqrt( _avgSqrDistance );

	// clean up
	annDeallocPts( borderPts1 );
	annDeallocPts( borderPts2 );
	delete borderTree1;
	delete borderTree2;
	delete[] nnIdx;
	delete[] dists;
}
