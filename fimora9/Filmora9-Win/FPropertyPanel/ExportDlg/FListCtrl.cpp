#include "stdafx.h"
#include "FListCtrl.h"
#include "FTypeLabel.h"

FListCtrl::FListCtrl(QWidget *parent)
	: FBaseWidget(parent)
{
	initUI();
}

FListCtrl::~FListCtrl()
{

}

void FListCtrl::setHeader(QString strText)
{
	m_pTitle->setText(strText);
}

void FListCtrl::setListData(const QList<QString>& listData)
{
	m_strList = listData;
}

void FListCtrl::initUI()
{
	m_pTitle = new FLabel(this);
	m_pTitle->setObjectName("FListCtrl_Title");
}

void FListCtrl::showEvent(QShowEvent *e)
{

}

void FListCtrl::paintEvent(QPaintEvent *event)
{
	m_pTitle->setGeometry(0, 0, width(), 30);
	QList<QString>::iterator iter = m_strList.begin();
	iter = ++iter;
	QPainter painter(this);
	painter.save();
	QPen pen(QColor("#71C8D1"));
	QBrush brush(QColor("#71C8D1"));
	for (; iter != m_strList.end(); ++iter)
	{
		int index = iter - m_strList.begin();
		//���ƶ��ߺ͵���
		pen.setWidth(1);
		painter.setPen(pen);
		painter.drawLine(15, 23 + index * 30, 200, 23 + index * 30);
		painter.drawLine(15, 23 + (index + 1) * 30, 200, 23 + (index + 1) * 30);
		//������ͣЧ��
		//painter.setBrush(brush);
		//painter.drawRoundRect(0, 23 + index * 30, 210, 30,25,25);
	}
	painter.restore();
}

void FListCtrl::resizeEvent(QResizeEvent *event)
{
	m_pTitle->setGeometry(0, 0, width(), 30);
	QList<QString>::iterator iter = m_strList.begin();
	for (; iter != m_strList.end(); ++iter)
	{
		FTypeLabel* label = new FTypeLabel(this);
		label->setText(*iter);
		int index = iter - m_strList.begin();
		label->setGeometry(0, 23 + index * 30, 230, 30);
		//�������þ��п������
		label->setAlignment(Qt::AlignVCenter);
		//��ǰ�ѡ�е�ʱ�����ź�ͨ����������
		connect(label, &FTypeLabel::sigClicked, this, [&](QString strType){
			emit sigItemSelect(strType);
		});
	}
}
