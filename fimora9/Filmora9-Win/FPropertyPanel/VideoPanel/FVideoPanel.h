#ifndef FVIDEOPANEL_H
#define FVIDEOPANEL_H

#include "FPropertyPanel.h"
#include "FPropertyCommon.h"

class FPropertySlider;
class FVideoPanelMgr;
#include "inc_FPropertyPanel/fpropertypanel_global.h"
class FPROPERTYPANEL_EXPORT FVideoPanel : public FPropertyPanel
{
	Q_OBJECT

public:
	FVideoPanel(QWidget *parent = 0);
	~FVideoPanel();

	// ���ڳ�ʼ��
	void Init() override;
	// ���ڽ���ʾ
	void Show() override;
	// ���ڽ�����
	void Hide() override;
	// ���ڽ�����
	void Destory() override;
	// ���ڸ�������
	void Update() override;
	// �����Է���
	void TranslateText() override;
	void RetranslateUi() override;
	// ����enable����
	void SetEnabled(bool) override;

protected:
	void resizeEvent(QResizeEvent *) override;

private:
	void ConnectSignals();
	void Init3DLUTMenu();
	void slotShowMenu();
	void slotRotateChanged(FPropertyRotate::RotateMode);
	void slotContrastChanged(int);
	void slotSaturationChanged(int);
	void slotBrightnessChanged(int);
	void slotTintChanged(int);
	void slot3DLUTChanged(QAction*);
	void slotDefault3DLUT();
	void slotEnhanceChanged(bool);
	void slotSpeedChanged(float);
	void slotPlayInReverse(bool);
	void slotReset();
	void slotAdvanced();
	
private:
	FVideoPanelMgr *m_pPanelMgr;
	FPropertyRotate *m_pRotate;
	FPropertySlider *m_pContrast;
	FPropertySlider *m_pSaturation;
	FPropertySlider *m_pBrightness;
	FPropertySlider *m_pTint;
	FPropertyButton *m_p3DLUT;
	FPropertyCheckBox *m_pEnhance;
	FFiniteValuePropertySlider *m_pSpeed;
	FPropertyCheckBox *m_pPlayInReverse;
	BottomButtonBar *m_pButtonBar;
	QList<QAction*> m_lstActions;
	FMenu *m_pMenu;
};



#endif // FVIDEOPANEL_H
