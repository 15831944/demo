#ifndef FPHOTOPANELMGR_H
#define FPHOTOPANELMGR_H

#include "FPanelMgr.h"
#include "FPropertyCommon.h"
#include "inc_FCommonLib/FCommonWidgets.h"
#include "inc_FProject/FNLETimelineFactory.h"

class FPhotoPanelMgr : public FPanelMgr
{
	Q_OBJECT

public:
	FPhotoPanelMgr(QObject *parent);
	~FPhotoPanelMgr();

	// Rotate����
	void RotateReset();
	void SetRotate(FPropertyRotate::RotateMode);
	// Contrast����
	int GetContrastValue();
	void SetContrastValue(int);
	// Saturation����
	int GetSaturationValue();
	void SetSaturationValue(int);
	// Brightness����
	int GetBrightnessValue();
	void SetBrightnessValue(int);
	// Tint����
	int GetTintValue();
	void SetTintValue(int);
	// 3D LUT����

	// Enhance����
	bool Enhanced();
	void EnableEnhance(bool);
	// Duration����
	int GetDuration();
	void SetDuration(INT64);
	void DurationApplyToAll();

private:
	void RotateFlipHorizontal();
	void RotateFlipVertical();

private:
	NLEComPtr<FNLETimeline> m_pFilter;
};

#endif // FPHOTOPANELMGR_H
