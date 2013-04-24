#if !defined(AFX_SoMVTBasicStatistic_H__351789GC_3AWE_43A3_9C82_7CAC0DB1F90C__INCLUDED_)
#define AFX_SoMVTBasicStatistic_H__351789GC_3AWE_43A3_9C82_7CAC0DB1F90C__INCLUDED_

#pragma once

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <vector>

using namespace std;

class SoMVTBasicStatistic : public SoEngine
{
	SO_ENGINE_HEADER(SoMVTBasicStatistic);

public:
	/// Initialization
	static void	initClass();
	SoMVTBasicStatistic(void);

public:
	SoSFInt32		 port;
	SoMFFloat		 data;
	SoMFFloat		 prob;

	SoSFTrigger		 update;

	SoEngineOutput	 mean;
	SoEngineOutput	 std;
	SoEngineOutput	 quantile;

protected:
	/// Destructor
	~SoMVTBasicStatistic(void);

	/// Evaluation
	virtual void			inputChanged (SoField* whichField);
	virtual void			evaluate ();

	void					enableOutputs (BOOL flag);
	bool					updateOutput();

private:
	float			fMean;
	float			fStd;
	vector<float>	fQuantile;
};

#endif // !defined(AFX_SoMVTBasicStatistic_H__351789GC_3AWE_43A3_9C82_7CAC0DB1F90C__INCLUDED_)
