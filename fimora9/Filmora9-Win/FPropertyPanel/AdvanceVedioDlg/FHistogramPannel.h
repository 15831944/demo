#ifndef FHISTOGRAMPANNEL_H
#define FHISTOGRAMPANNEL_H

#include "inc_FCommonLib\FBaseWidget.h"

class FLabel;
class FMatrixDrawPannel;
class FHistogramPannel : public FBaseWidget
{
	Q_OBJECT

public:
	FHistogramPannel(QWidget *parent);
	~FHistogramPannel();

private:
	void InitUI();
	void InitConnections();

private:
	FLabel* m_pHeader; 
	FMatrixDrawPannel* m_pMatrixGraph; //����ͼ����
};


class FMatrixDrawPannel : public FBaseWidget
{
	Q_OBJECT

public:
	FMatrixDrawPannel(QWidget *parent);
	~FMatrixDrawPannel();

protected:
	void paintEvent(QPaintEvent *e)override;

private:
	void InitUI();
	void InitConnections();
	void GetGraphData();   //��ȡ���ƾ���ͼ��Ҫ������

private:

};

#endif // FHISTOGRAMPANNEL_H
