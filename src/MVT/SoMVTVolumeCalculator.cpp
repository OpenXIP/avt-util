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
