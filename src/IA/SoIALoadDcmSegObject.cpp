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

#include "SoIALoadDcmSegObject.h"

const float EPSILON = 1e-6;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoIALoadDcmSegObject );

SoIALoadDcmSegObject::SoIALoadDcmSegObject(void)
{
	SO_ENGINE_CONSTRUCTOR( SoIALoadDcmSegObject );

	// Inputs
	SO_ENGINE_ADD_INPUT( inputDcmSeg, ("") );
	SO_ENGINE_ADD_INPUT( process, () );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( inputVolume, SoXipSFDataImage );

	mXipInputImage = 0;
}

void SoIALoadDcmSegObject::initClass()
{
	SO_ENGINE_INIT_CLASS( SoIALoadDcmSegObject, SoEngine, "SoEngine" );
}

SoIALoadDcmSegObject::~SoIALoadDcmSegObject(void)
{
	clearDataImages();
}

void SoIALoadDcmSegObject::inputChanged (SoField* whichField)
{
	if (whichField == &process)
	{
		loadVolume();
	}
}

void SoIALoadDcmSegObject::evaluate()
{	
	SO_ENGINE_OUTPUT( inputVolume, SoXipSFDataImage, setValue(mXipInputImage) );	
}

void SoIALoadDcmSegObject::clearDataImages()
{
	if( mXipInputImage )
	{
		mXipInputImage->unref();
		mXipInputImage = 0;
	}
}

void SoIALoadDcmSegObject::loadVolume()
{
	SbString inputSeg = inputDcmSeg.getValue();

	if (inputSeg.getLength() <= 0)
	{
		clearDataImages();
		return;
	}

	DcmFileFormat _input_fileformat;
	OFCondition status = _input_fileformat.loadFile(inputSeg.getString());
	if (!status.good())
	{
		clearDataImages();
		return;
	}
	DcmDataset *_input_dataset = _input_fileformat.getDataset();

	float _input_imgPosition[3];
	float _input_imgOrientation[6];
	int	  _input_imgDimension[3];
	float _input_imgSpacing[3];
	getPositionItems(_input_dataset, _input_imgPosition, _input_imgOrientation, _input_imgDimension, _input_imgSpacing);

	createXipDataImage(&mXipInputImage, _input_imgPosition, _input_imgOrientation, _input_imgDimension, _input_imgSpacing);
	updateXipDataImage(mXipInputImage, _input_dataset, _input_imgPosition, _input_imgDimension, _input_imgSpacing);
}

void SoIALoadDcmSegObject::createXipDataImage(SoXipDataImage **mXipImage, float imgPosition[3], float imgOrientation[6], int imgDimension[3], float imgSpacing[3])
{
	SbXipImageDimensions volDimensions;
	volDimensions[0] = imgDimension[0];
	volDimensions[1] = imgDimension[1];
	volDimensions[2] = imgDimension[2];

//	SbMatrix volModelMatrix = getModelMatrixFromDICOM(dataset);
	SbVec3f dir_col(imgOrientation[0], imgOrientation[1], imgOrientation[2]);
	SbVec3f dir_row(imgOrientation[3], imgOrientation[4], imgOrientation[5]);
	SbVec3f dir_nor = dir_col.cross(dir_row);

	SbMatrix volModelMatrix;
	volModelMatrix[0][0] = imgDimension[0]*imgSpacing[0]*dir_col[0];
	volModelMatrix[0][1] = imgDimension[0]*imgSpacing[0]*dir_col[1];
	volModelMatrix[0][2] = imgDimension[0]*imgSpacing[0]*dir_col[2];
	volModelMatrix[0][3] = 0;

	volModelMatrix[1][0] = imgDimension[1]*imgSpacing[1]*dir_row[0];
	volModelMatrix[1][1] = imgDimension[1]*imgSpacing[1]*dir_row[1];
	volModelMatrix[1][2] = imgDimension[1]*imgSpacing[1]*dir_row[2];
	volModelMatrix[1][3] = 0;

	volModelMatrix[2][0] = imgDimension[2]*imgSpacing[2]*dir_nor[0];
	volModelMatrix[2][1] = imgDimension[2]*imgSpacing[2]*dir_nor[1];
	volModelMatrix[2][2] = imgDimension[2]*imgSpacing[2]*dir_nor[2];
	volModelMatrix[2][3] = 0;

	volModelMatrix[3][0] = imgPosition[0];
	volModelMatrix[3][1] = imgPosition[1];
	volModelMatrix[3][2] = imgPosition[2];
	volModelMatrix[3][3] = 1.0;

	if ( (*mXipImage) && (*mXipImage)->get() )
	{
		if ( ((*mXipImage)->get()->getDimStored()   != volDimensions) ||
			((*mXipImage)->get()->getModelMatrix() != volModelMatrix) )
		{
			(*mXipImage)->unref();
			(*mXipImage) = 0;
		}	
	}	

	if ( !(*mXipImage) )
	{			
		(*mXipImage) = new SoXipDataImage();
		(*mXipImage)->ref();

		SbXipImage* ouputImage = new SbXipImage( volDimensions,
			SbXipImage::UNSIGNED_BYTE,
			8,
			1,								   
			SbXipImage::SEPARATE,
			SbXipImage::LUMINANCE,
			volModelMatrix);	

		ouputImage->zero();
		(*mXipImage)->set( ouputImage );	
	}
}

void SoIALoadDcmSegObject::updateXipDataImage(SoXipDataImage* mXipImage, DcmDataset *dataset, float imgPosition[3], int imgDimension[3], float imgSpacing[3])
{
	SbXipImage* outputImage = mXipImage->get();
	BYTE* outImagePtr = (BYTE*) outputImage->refBufferPtr();

	int _slice_Size = imgDimension[0]*imgDimension[1];

	const Uint8 *pixelData = NULL; 
	unsigned long count = 0; 
	if (dataset->findAndGetUint8Array(DCM_PixelData, pixelData, &count).good()) 
	{ 
		for (int i = 0; i < imgDimension[2]; i++)
		{
			BYTE *_data = outImagePtr + i*_slice_Size;
			const Uint8 *_image = pixelData + i*_slice_Size;

			memcpy(_data, _image, sizeof(BYTE)*_slice_Size);
		}
	}

	outputImage->unrefBufferPtr();
}

void SoIALoadDcmSegObject::getPositionItems(DcmDataset *dataSet, float imgPosition[3], float imgOrientation[6], int imgDimension[3], float imgSpacing[3])
{
	DcmStack stack;
	DcmElement *element;

	unsigned short height, width;

	//depth
	OFString buffer;
	dataSet->findAndGetOFString(DCM_NumberOfFrames, buffer);
	imgDimension[2] = atoi(buffer.c_str());

	// column
	dataSet->findAndGetUint16(DCM_Columns, width);
	imgDimension[0] = width;

	// row
	dataSet->findAndGetUint16(DCM_Rows, height);
	imgDimension[1] = height;

	// slice thickness
	dataSet->findAndGetOFString(DCM_SliceThickness, buffer);
	imgSpacing[2] = atof(buffer.c_str());

	// pixel spacing
	dataSet->findAndGetOFStringArray(DCM_PixelSpacing, buffer);
	sscanf(buffer.c_str(), "%f\\%f", &imgSpacing[0], &imgSpacing[1]);

	// patient position
	dataSet->findAndGetOFStringArray(DCM_ImagePositionPatient, buffer);
	sscanf(buffer.c_str(), "%f\\%f\\%f", &imgPosition[0], &imgPosition[1], &imgPosition[2]);

	// patient position
	dataSet->findAndGetOFStringArray(DCM_ImageOrientationPatient, buffer);
	sscanf(buffer.c_str(), "%f\\%f\\%f\\%f\\%f\\%f", &imgOrientation[0], &imgOrientation[1], &imgOrientation[2], &imgOrientation[3], &imgOrientation[4], &imgOrientation[5]);
}