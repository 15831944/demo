#ifndef FAUDIOMIXERBASEWIDGET_H
#define FAUDIOMIXERBASEWIDGET_H

#include "inc_FCommonLib/FBaseWidget.h"
#include "inc_FCommonLib/FCommonWidgets.h"

class FColorGradientSlider : public FBaseWidget
{
	Q_OBJECT

public:
	FColorGradientSlider(Qt::Orientation orientation = Qt::Horizontal, QWidget *parent = 0);
	~FColorGradientSlider();
	
	// �Ƿ���Ӧ�������Ĭ�Ϸ�
	void SetMousePressEnabled(bool enabled);
	// ���÷�Χ
	void SetRange(float min, float max);
	// ���õ�ǰֵ
	void SetValue(float value);

protected:
	void paintEvent(QPaintEvent *) override;
	void mousePressEvent(QMouseEvent *) override;

private:
	float GetLen();

private:
	Qt::Orientation m_orientation;
	bool m_mousePressEnabled;
	float m_minValue;
	float m_maxValue;
	float m_curValue;
};

class FSoundChannelPanel : public FBaseWidget
{
	Q_OBJECT

public:
	enum SoundChannel{None_Channel, Left_Channel, Right_Channel};

public:
	FSoundChannelPanel(QWidget *parent = 0);
	~FSoundChannelPanel();
	void SetValue(float);
	float GetValue();

signals:
	void sigValueChanged(float);

protected:
	void mousePressEvent(QMouseEvent *) override;
	void mouseMoveEvent(QMouseEvent *) override;
	void mouseReleaseEvent(QMouseEvent *) override;
	void resizeEvent(QResizeEvent *) override;
	void paintEvent(QPaintEvent *) override;
	void showEvent(QShowEvent *) override;

private:
	void DrawArc(QPainter *p);

private:
	SoundChannel m_soundChannel;
	bool m_bPressed;
	QPointF m_center;  // ���ԲԲ�� 
	float m_centerRadius;  // ��Բ�뾶
	QPointF m_drag;  // �ԲԲ�� 
	float m_curValue;
	FLabel *m_pLeftLbl;
	FLabel *m_pRightLbl;
};

#include "FToolBarSlider.h"
class FMarkSlider : public FBaseWidget
{
	Q_OBJECT

public:
	FMarkSlider(QWidget *parent = 0);
	~FMarkSlider();

	void SetMarkValue(float *pValues);
	void SetValue(float);
	float GetValue();
	void SetSliderObjectName(QString);

signals:
	void sigValueChanged(float);

protected:
	void resizeEvent(QResizeEvent *) override;
	void paintEvent(QPaintEvent *) override;

private:
	void CalculateMarkValueInner();
	void slotValueChanged(float);

private:
	float m_curValue;
	float m_scale[8];
	float m_markValue[9];
	float m_markValueInner[9];
	ToolBarSlider *m_pSlider;
};

class FMarkSliderRuler : public FBaseWidget
{
	Q_OBJECT

public:
	FMarkSliderRuler(float *pValues = 0, QWidget *parent = 0);
	~FMarkSliderRuler();

protected:
	void resizeEvent(QResizeEvent *) override;
	void paintEvent(QPaintEvent *) override;

private:
	float m_values[9];
	float m_scales[8];
	QList<FLabel*> m_lstLbls;
};

class FAudioTrack : public FBaseWidget
{
	Q_OBJECT

public:
	FAudioTrack(QWidget *parent);
	~FAudioTrack();

	void SetText(QString);
	void SetMarkValue(float *);
	void SetValue(float);
	void SetImageLabelObjectName(QString);
	int GetMarkSliderHeight();

protected:
	void resizeEvent(QResizeEvent *) override;

private:
	void ConnectSignals();

private:
	FLabel *m_pTextLbl;
	FLabel *m_pImageLbl;
	FSoundChannelPanel *m_pSoundChannelPanel;
	FLineEdit *m_pLineEdit;
	FMarkSlider *m_pMarkSlider;
	FColorGradientSlider *m_pLeftAudioTrack;
	FColorGradientSlider *m_pRightAudioTrack;
};

#endif // FAUDIOMIXERBASEWIDGET_H



