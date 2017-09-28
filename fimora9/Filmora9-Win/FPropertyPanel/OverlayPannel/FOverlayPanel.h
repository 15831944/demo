#ifndef FOVERLAYPANEL_H
#define FOVERLAYPANEL_H

#include  "FPropertyPanel.h"
#include "..\include\inc_FPropertyPanel\fpropertypanel_global.h"

class FPropertySlider;
class BottomButtonBar;
class FPROPERTYPANEL_EXPORT FOverlayPanel : public FPropertyPanel
{
	Q_OBJECT

public:
	FOverlayPanel(QWidget *parent);
	~FOverlayPanel();
	// ���ڳ�ʼ��
	virtual void Init();
	// ���ڽ���ʾ
	virtual void Show();
	// ���ڽ�����
	virtual void Hide();
	// ����enable����
	virtual void SetEnabled(bool enabled);
	// ���ڽ�����
	virtual void Destory();
	// ���ڸ�������
	virtual void Update() override;

public Q_SLOTS:
	void slotAlphaValueChanged(int iValue);

Q_SIGNALS:
	void sigClickOkBtn();

private:
	void initUI();
private:
	FPropertySlider* m_AlphaSlider;
	BottomButtonBar* m_BottomBar;
};

#endif // FOVERLAYPANEL_H
