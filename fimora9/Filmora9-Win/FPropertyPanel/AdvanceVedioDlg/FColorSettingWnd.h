#ifndef FCOLORSETTINGWND_H
#define FCOLORSETTINGWND_H


#include "..\include\inc_FCommonLib\FBaseWidget.h"
#include "..\include\inc_FCommonLib\FCommonWidgets.h"
#include "..\include\inc_FPropertyPanel\fpropertypanel_global.h"

class FPresentWnd;
class FColorAdjustPanel;
class FNLETimeline;
class FPROPERTYPANEL_EXPORT FColorSettingWnd : public FBaseWidget
{
	Q_OBJECT
public:
	typedef enum AdjustType
	{
		type_Preset,  //Ԥ������
		type_Adjust   //�Զ�������
	};
	FColorSettingWnd(QWidget *parent);
	~FColorSettingWnd();
public:
	void SetTimeline(FNLETimeline* timeline);

public Q_SLOTS:
	void slotOnTabChanged(AdjustType type);
	
Q_SIGNALS:
	void sigOnTimelineChange();

private:
	void InitUI();
	void InitConnections();
	void InitData();

private:
	FButton* m_PresentBtn;
	FButton* m_AdjsutBtn;
	FPresentWnd* m_PresentWnd;
	FColorAdjustPanel* m_AdjustWnd;
	QStackedWidget* m_StackWidget; 
};

#endif // FCOLORSETTINGWND_H
