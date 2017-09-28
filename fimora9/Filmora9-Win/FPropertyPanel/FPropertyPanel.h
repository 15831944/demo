#ifndef FPROPERTYPANEL_H
#define FPROPERTYPANEL_H


#include "inc_FCommonLib/FBaseWidget.h"
#include "inc_FPropertyPanel/fpropertypanel_global.h"

class FNLETimeline;
class FPROPERTYPANEL_EXPORT FPropertyPanel : public FUpdateBaseWidget
{
    Q_OBJECT
public:
    FPropertyPanel(QWidget *parent);

    FNLETimeline* GetTimeline();
    FNLETimeline* GetRootTimeline();
    
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
    
signals:
    // ֪ͨ�ⲿ�������ݣ�ʱ���ߣ�EditPanel�ȣ�
    void sigUpdate();
    // ֪ͨEditPanel��������
    void sigUpdateEditPanel();
	// OK��ť�����
	void sigOk();

//private:
public:
    void SetTimeline(FNLETimeline *timeline);
    void SetRootTimeline(FNLETimeline *timeline);

private:
    FNLETimeline *m_timeline;
    FNLETimeline *m_rootTimeline;
};

#endif // FPROPERTYPANEL_H
