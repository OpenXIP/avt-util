#if !defined(AFX_SoMVTSegementConvert_H__353923CC_3ABE_43A3_9C56_7CAC0DB1F90C__INCLUDED_)
#define AFX_SoMVTSegementConvert_H__353923CC_3ABE_43A3_9C56_7CAC0DB1F90C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Inventor/Engines/SoSubEngine.h"
#include "Inventor/fields/SoSFString.h"
#include "Inventor/fields/SoSFTrigger.h"
#include "Inventor/SbString.h"

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/itk/SoItkSFDataImage.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include <xip/inventor/dicom/xipivDicomUtils.h>

#include <xip/inventor/itk/SoItkSFDataImage.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/itk/SoItkSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>

#include "dcmtk/dcmdata/dcmetinf.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmdata/dcdebug.h"
#include "dcmtk/dcmdata/dcuid.h"
#include "dcmtk/dcmdata/dcdict.h"
#include "dcmtk/dcmdata/cmdlnarg.h"
#include "dcmtk/ofstd/ofconapp.h"
#include "dcmtk/ofstd/ofstd.h"
#include "dcmtk/ofstd/ofdatime.h"
#include "dcmtk/dcmdata/dcuid.h"         /* for dcmtk version name */
#include "dcmtk/dcmdata/dcdeftag.h"      /* for DCM_StudyInstanceUID */
#include "dcmtk/dcmdata/dcostrmz.h"      /* for dcmZlibCompressionLevel */

class __declspec(dllexport) SoMVTDcmSegConvert : public SoEngine
{
	SO_ENGINE_HEADER( SoMVTDcmSegConvert);

public:
	SoMVTDcmSegConvert(void);
	static void initClass();

	SoSFString		inputDcmSeg;
		// Input Dcm seg Image

	SoSFString		refDcmSeg;
		// reference Dcm seg Image

	SoSFTrigger		process; 

	SoEngineOutput		inputVolume; // 
	SoEngineOutput		refVolume; // 

private:
	~SoMVTDcmSegConvert(void);
		// Destructor

	virtual void evaluate();
		// Evaluation method

	void resampleVolume();

	virtual void inputChanged (SoField* whichField);

protected:
	SoXipDataImage* mXipInputImage;
	SoXipDataImage* mXipRefImage;

	void clearDataImages();

	bool validateDataImages(DcmDataset *dataset0, DcmDataset *dataset1);
	void getPositionItems(DcmDataset *dataset, double imgPosition[3], int imgDimension[3], double imgSpacing[3]);

	void createXipDataImage(SoXipDataImage **mXipImage, DcmDataset *dataset, int bufDimension[3]);
	void updateXipDataImage(SoXipDataImage* mXipImage, DcmDataset *dataset, double _begin_SlicePos,double imgPosition[3], int imgDimension[3], double imgSpacing[3]);
};

#endif // !defined(AFX_SoMVTSegementConvert_H__353923CC_3ABE_43A3_9C56_7CAC0DB1F90C__INCLUDED_)
