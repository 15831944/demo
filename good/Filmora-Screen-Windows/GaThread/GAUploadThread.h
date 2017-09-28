#ifndef GATHREAD_H
#define GATHREAD_H

#include "gathread_global.h"
#include "gathread.h"
#include <QObject>

class GATHREAD_EXPORT GAUpload : public QObject
{
	Q_OBJECT

public:
	//����Ϊ����ģʽ������ȫ�ֻ�ȡ�̶߳���
	static GAUpload* GetInstance();
	//�����¼�����Ϣ
	virtual void SendEventinfo(QString strCategory, QString strAction, QString strLabel) = 0;
	//�����ٶ�����Ϣ
	virtual void SendAppSpeedInfo(QString strCategery, QString strVariable, int iValue) = 0;
	//������Ļ��Ϣ
	virtual void SendScreenInfo(QString strPageName) = 0;
	//�����û��Զ���ά����Ϣ
	virtual void SetDimensioninfo(int iIndex, QString strValue) = 0;
	//���ͳ���汾��Ϣ
	virtual void SendAppVersion(QString strVersion) = 0;
	//���ͳ���������Ϣ
	virtual void SendLanguageInfo(QString strLanguage) = 0;
	//����Ӧ�ó��򴰿ڴ�С
	virtual void SendViewSize(int Width, int Height) = 0;
	//�����Զ�����Ϣ
	virtual void SendUserMetric(int iIndex, int iValue) = 0;
	//�����û��罻��Ϊ
	virtual void SendSocialNetWorkInfo(QString strNetWork, QString strAction, QString strTarget) = 0;
	//��������쳣��Ϣ
	virtual void SendExceptionInfo(QString strDescription, int iFatal) = 0;
};
#endif // GATHREAD_H
