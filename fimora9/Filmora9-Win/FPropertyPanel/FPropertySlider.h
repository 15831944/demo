#ifndef FPROPERTYSLIDER_H
#define FPROPERTYSLIDER_H

#include "inc_FCommonLib/FBaseWidget.h"
#include "inc_FCommonLib/FCommonWidgets.h"
#include "inc_CommonLib/CommonWidgets.h"
#include "inc_FPropertyPanel/fpropertypanel_global.h"

class FToolBarSlider;

class FPROPERTYPANEL_EXPORT FPropertySlider : public FBaseWidget
{
	Q_OBJECT

public:
	FPropertySlider(QWidget *parent = 0);
	~FPropertySlider();
	// set value
	void SetValue(float);
	float GetValue();
	// ����property���뷽ʽ��Ĭ�������
	void SetAlignmentOfProperty(Qt::Alignment);
	// ��������label���
	void SetPropertyWidth(int);
	// ����value���뷽ʽ��Ĭ�������
	void SetAlignmentOfValue(Qt::Alignment);
	// ����value label���
	void SetValueWidth(int);
	// ����slider��ֵ��Χ
	void SetRange(float min, float max);
	// ����slider���
	void SetSliderWidth(int);
	// ����property name
	void SetPropertyName(QString);
	QString GetPropertyName();
	// ���� decimal places under Float_Format
	void SetDecimalPlaces(int);
	// ������ֵ��׺
	void SetSuffix(QString);
	// ����Slider Object Name
	void SetSliderObjectName(QString);

Q_SIGNAL
	void sigValueChanged(float value);

protected:
	void resizeEvent(QResizeEvent *) override;

private:
	int m_PropertyWidth;
	int m_SliderWidth;
	int m_ValueWidth;
	int m_DecimalPlaces;
	QString m_Suffix;
	QString m_PropertyName;
	FLabel *m_pPropertyLbl;
	FToolBarSlider *m_pSlider;
	FLabel *m_pValueLbl;
};

#endif // FPROPERTYSLIDER_H
