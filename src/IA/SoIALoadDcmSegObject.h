#if !defined(AFX_SoIALoadDcmSegObject_H__353923CC_3ABE_43A3_9C56_7CAC0DB1F90C__INCLUDED_)
#define AFX_SoIALoadDcmSegObject_H__353923CC_3ABE_43A3_9C56_7CAC0DB1F90C__INCLUDED_

#include "Inventor/Engines/SoSubEngine.h"
#include "Inventor/fields/SoSFString.h"
#include "Inventor/fields/SoSFTrigger.h"
#include "Inventor/SbString.h"

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/dicom/xipivDicomUtils.h>
#include <xip/inventor/core/SbXipImage.h>

#include <dcmtk/dcmdata/dcmetinf.h>
#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmdata/dcdebug.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmdata/dcdict.h>
#include <dcmtk/dcmdata/cmdlnarg.h>
#include <dcmtk/ofstd/ofconapp.h>
#include <dcmtk/ofstd/ofstd.h>
#include <dcmtk/ofstd/ofdatime.h>
#include <dcmtk/dcmdata/dcuid.h>         /* for dcmtk version name */
#include <dcmtk/dcmdata/dcdeftag.h>      /* for DCM_StudyInstanceUID */

class __declspec(dllexport) SoIALoadDcmSegObject :	public SoEngine
{
	SO_ENGINE_HEADER( SoIALoadDcmSegObject);

public:
	SoIALoadDcmSegObject(void);
	static void initClass();

	SoSFString		inputDcmSeg;
		// Input Dcm seg Image

	SoSFTrigger		process; 

	SoEngineOutput		inputVolume; // 

private:
	~SoIALoadDcmSegObject(void);

	virtual void evaluate();
		// Evaluation method

	void loadVolume();

	virtual void inputChanged (SoField* whichField);

protected:
	SoXipDataImage* mXipInputImage;

	void clearDataImages();

	void getPositionItems(DcmDataset *dataset, float imgPosition[3], float imgOrientation[6], int imgDimension[3], float imgSpacing[3]);

	void createXipDataImage(SoXipDataImage **mXipImage, float imgPosition[3], float imgOrientation[6], int imgDimension[3], float imgSpacing[3]);
	void updateXipDataImage(SoXipDataImage* mXipImage, DcmDataset *dataset, float imgPosition[3], int imgDimension[3], float imgSpacing[3]);
};

#endif // !defined(AFX_SoIALoadDcmSegObject_H__353923CC_3ABE_43A3_9C56_7CAC0DB1F90C__INCLUDED_)
