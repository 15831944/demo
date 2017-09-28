#pragma once
#include <QMutex>
/************************************************************************/
/* ���ߣ�wangbiao
   ���ܣ���װGoolgle �����ϴ����ݽӿڣ��������
   ˵������Ϊ�ڲ���Ҫ�ϴ������ݱȽ϶࣬���ÿ���ϴ���new һ���������ɱȽϴ��
         ��Դ���ģ��ʴ�����Ƴ�Ϊ����ģʽ
   ʱ�䣺2017/06/19
*/
/************************************************************************/
typedef void* ua_tracker;
class TUATracker
{
public:
	~TUATracker();
	void createTracker(const char* tracking_id, const char* client_id, const char* app_name);
	//���ͳ���汾��Ϣ
	void setAppVerion(QString strVersion);
	//����Ӧ�ó���������Ϣ
	void SetLanguageAndLocate(QString string);
	//����Ӧ�ó��򴰿ڴ�С��Ϣ
	void  SetViewSize(int Width, int Height);
	//�����Զ���ά����Ϣ
	void SetDimension(int iIndex, QString strValue);
	//�����Զ���ָ����Ϣ
	void SetMetric(int iIndex, int iValue);
	//�����û��¼�
	void SendEvent(QString  strCategory, QString strAction, QString strLabel,int iValue = 0);
	//�����û��л�������Ϣ
	void SendScreenName(QString strName);
	//����Ӧ���ٶȵĲ���
	void SendAppSpeed(QString  strCategory, QString strVariable, int iValue, QString strLable = "");
	//�����û��罻��Ϊ
	void SendSocialNetWorkInfo(QString strNetWork,QString strAction,QString strTarget);
	//��������쳣��Ϣ
	void SendExceptionInfo(QString strDescription,int iFatal);
	//QString ת��Ϊ char* ����
	char* QStr2Char(QString strInput);
public:
	static TUATracker *getInstance();
	static TUATracker *m_pInstance;
	static QMutex  m_Mutex;

private:
	ua_tracker m_Tracker;
private:
	QString getClientId();
private:
	TUATracker();
	//���⸳ֵ����Ӱ�쵥������ֵ��������Ϊ˽�У���ո�ֵ����
	TUATracker(const TUATracker &);
	TUATracker& operator = (const TUATracker &);
};

