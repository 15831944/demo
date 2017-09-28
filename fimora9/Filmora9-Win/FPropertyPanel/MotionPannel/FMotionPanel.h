#ifndef FMOTIONPANNEL_H
#define FMOTIONPANNEL_H

#include "FPropertyPanel.h"
#include "inc_FPropertyPanel\fpropertypanel_global.h"

class FButton;
class QListWidget;
class FMotionPannelMgr;
class MediaPlayerView;
class FPROPERTYPANEL_EXPORT FMotionPanel : public FPropertyPanel
{
	Q_OBJECT

public:
	FMotionPanel(QWidget *parent);
	~FMotionPanel();
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

protected:
	void resizeEvent(QResizeEvent *event)override;

Q_SIGNALS:
	void  sigConfirmSetting();


private:
	void onPlayMotion(QString strFilePath);


private:
	void InitUI();
	void InitData();
	void InitConnections();

private:

	FButton* m_AdvanceBtn;
	FButton* m_OkBtn;
	QListWidget* m_ListWidget;
	FMotionPannelMgr* m_PannelMgr;
	MediaPlayerView* m_Player;
};

#endif // FMOTIONPANNEL_H
