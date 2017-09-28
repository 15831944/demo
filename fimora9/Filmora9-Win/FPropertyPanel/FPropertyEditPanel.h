#ifndef FPROPERTYEDITPANEL_H
#define FPROPERTYEDITPANEL_H

#include <QtWidgets/QWidget>

#include "FPropertyPanel.h"

class FPropertyEditPanel : public FPropertyPanel
{
    Q_OBJECT

public:
    FPropertyEditPanel(QWidget *parent);
    ~FPropertyEditPanel();


    QObject* GetTimelineManager();

public:
    void GetTimelineManager(QObject *manager);

signals:
    // ֪ͨ�ⲿ�������ݣ�ʱ���ߣ�EditPanle�ȣ�
    void sigUpdate();
    // ֪ͨ��������������
    void sigUpdatePropertyPanel();

private:
    QObject *m_timelineManager;
};

#endif // FPROPERTYEDITPANEL_H
