#ifndef FTRANSITIONPANEL_H
#define FTRANSITIONPANEL_H

#include "FPropertyPanel.h"
#include "FPropertyCommon.h"
#include "FTransitionPanelMgr.h"
#include "inc_FPropertyPanel/fpropertypanel_global.h"

class TransitionModeWidget : public FBaseWidget
{
	Q_OBJECT

public:
	enum TransitionMode{ Overlap_Mode, Prefix_Mode, Postfix_Mode };

public:
	TransitionModeWidget(TransitionMode mode = Overlap_Mode, QWidget *parent = 0);
	~TransitionModeWidget();
	void SetText(QString);
	void SetImageLblObjectName(QString);
	// ѡ��
	void Select(bool);
	TransitionMode GetTransitionMode();

signals:
	void Clicked(TransitionMode);

protected:
	void mousePressEvent(QMouseEvent *) override;
	void resizeEvent(QResizeEvent *) override;
	void paintEvent(QPaintEvent *) override;

private:
	TransitionMode m_Mode;
	bool m_bSelected;
	FLabel *m_pImageLbl;
	FLabel *m_pTextLbl;
};


class FPROPERTYPANEL_EXPORT FTransitionPanel : public FPropertyPanel
{
	Q_OBJECT

public:
	enum RadioButtonState{ TrimmedFrames_State, RepeatFrames_State };

public:
	FTransitionPanel(QWidget *parent = 0);
	~FTransitionPanel();

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
	// ����Transition Mode
	void SetTransitionMode(TransitionModeWidget::TransitionMode);

signals:
	void sigTransitionModeClicked(TransitionModeWidget::TransitionMode);
	void sigRadioButtonChanged(RadioButtonState);

protected:
	void resizeEvent(QResizeEvent *) override;

private:
	void ConnectSignals();

private:
	FTransitionPanelMgr *m_pPanelMgr;
	FLabel *m_pDurationLbl;
	FSpinBox *m_pSpinBox;
	FButton *m_pApplyToAllBtn;
	FLabel *m_pModeLbl;
	TransitionModeWidget *m_pOverlap;
	TransitionModeWidget *m_pPrefix;
	TransitionModeWidget *m_pPostfix;
	FLabel *m_pRadioBtnHintLbl;
	FRadioButton *m_pRadioBtn_First;
	FRadioButton *m_pRadioBtn_Second;
	BottomButtonBar *m_pButtonBar;
};


#endif // FTRANSITIONPANEL_H
