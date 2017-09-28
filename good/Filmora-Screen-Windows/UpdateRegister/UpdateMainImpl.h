#ifndef UPDATEMAINIMPL_H
#define UPDATEMAINIMPL_H

#include <QWidget>
#include <QStackedWidget>
#include "CommonWidgets.h"
class ProgressDisplay;
class VersionDisplay;
class HintDisplay;
class LiveUpdateMgr;
class TitleBar;

class UpdateMainImpl : public URBaseWidget
{
	Q_OBJECT

public:
	UpdateMainImpl(QWidget *parent = 0);
	~UpdateMainImpl();

	void LiveUpdate(QString productId, QString version, QString email);
	void LiveUpdate();
	bool IsNeedUpdate();
	void Install();

protected:
	void resizeEvent(QResizeEvent *) override;
	virtual void RetranslateUi();

signals:
	//�رմ����ź�
	void Close();
	//��ʼ��װ�ź�
	void BeginInstall();
	//ȡ����װ�ź�
	void CancelInstall();
	//�°汾��װ������ȫ�����ź�
	void InstallStarted();
	//Remind Me Later�ź�
	void RemindMeLater();
	//�����ƶ��ź�
	void Move(int x, int y);
	//resize�ź�
	void Resize(QSize);

private:
	TitleBar *m_titleBar;
	ProgressDisplay *m_progressDisplay;
	VersionDisplay *m_versionDisplay;
	HintDisplay *m_hintDisplay;
	LiveUpdateMgr *m_updateMgr;
	QStackedWidget *m_stackedWidget;
};

#endif // UPDATEMAINIMPL_H
