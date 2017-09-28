#ifndef GAUPLOADWORKTHREAD_H
#define GAUPLOADWORKTHREAD_H

#include <stdafx.h>
#include "GAUploadThread.h"

class GAUploadWorkThread : public GAUpload
{
	Q_OBJECT

public:
	//�����߳�
	virtual void Start();
	//����ǰ���߳�
	virtual void SuspendThread();
	//�ָ��߳�ִ��
	virtual void  ResumThread();
	//�����¼�����Ϣ
	virtual void SendEventinfo(QString strCategory, QString strAction, QString strLabel);
	//�����ٶ�����Ϣ
	virtual void SendAppSpeedInfo(QString strCategery, QString strVariable, int iValue);
	//������Ļ��Ϣ
	virtual void SendScreenInfo(QString strPageName);
	//�����û��Զ���ά����Ϣ
	virtual void SetDimensioninfo(int iIndex, QString strValue);
	//���ͳ���汾��Ϣ
	virtual void SendAppVersion(QString strVersion);
	//���ͳ���������Ϣ
	virtual void SendLanguageInfo(QString strLanguage);
	//����Ӧ�ó��򴰿ڴ�С
	virtual void SendViewSize(int Width, int Height);
	//�����Զ�����Ϣ
	virtual void SendUserMetric(int iIndex, int iValue);
	//�����û��罻��Ϊ
	virtual void SendSocialNetWorkInfo(QString strNetWork, QString strAction, QString strTarget);
	//��������쳣��Ϣ
	virtual void SendExceptionInfo(QString strDescription, int iFatal);
	//���������̵߳ȴ���ʱ��
	virtual void SetWaitRunTime(int iWaitTime);
	//���캯��
	GAUploadWorkThread(QObject *parent);
public:
	static GAUpload* m_pWorkThread;
	static QMutex m_Mutex;
protected:
	GAThread* m_pThread;
};
#endif // GAUPLOADWORKTHREAD_H