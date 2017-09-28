#include "stdafx.h"

#include "inc_FSTimelineView/fstimelineview.h"
#include "TimelineViewPrivate.h"
#include "inc_FSCommonlib/gathread.h"

FSTimelineView::FSTimelineView(QWidget *parent)
:QWidget(parent)
{
	m_p = new TimelineViewPrivate(this);
	QVBoxLayout *layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(m_p);
	setLayout(layout);
}

FSTimelineView::~FSTimelineView()
{

}

IPlayerEditorManager* FSTimelineView::GetPlayerEditManager()
{
	return m_p->GetPlayerEditManager();
}

ITimelineViewManager* FSTimelineView::GetTimelineViewManager()
{
	return m_p->GetTimelineViewManager();
}

ITitleBarManager* FSTimelineView::GetTitleBarManager()
{
	return m_p->GetTitleBarManager();
}

void FSTimelineView::TransFromGaInfo()
{
	m_p->TransFromGaInfo();
	//�ϴ��û���Ϣ
	int iSeekCount = GAThread::getInstance()->getSeekCount();
	GAThread::getInstance()->insertEventItem(Clip_Edit, "SeekCount", QString::number(iSeekCount));
	//�ϴ�GA��Ϣ
	QString strAverageTime = GAThread::getInstance()->getAverageTime();
	if (strAverageTime.compare("0"))
	{
		//��seek������ʱ����ϴ�seek����ƽ��ʱ��
		GAThread::getInstance()->insertEventItem(ClipsSeekSpeed, "SeekAverageTime", strAverageTime);
	}	
}
