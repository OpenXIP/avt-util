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