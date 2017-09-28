#ifndef GAINNERTHREAD_H
#define GAINNERTHREAD_H

#include <QThread>

class GAThread;
class TUATracker;

//�ӿ�����
enum interfaceType
{
	type_AppVersion,  //�ϴ�app�汾
	type_AppLanguage, //�ϴ�app����
	type_AppViewSize, //�ϴ�app�����С
	type_UserDimension,//�ϴ��û��Զ���ά��
	type_UserMetic,   //�ϴ��û��Զ���
	type_Event,       //�ϴ��¼���Ϣ
	type_Page,         //�ϴ�ҳ���л�
	type_AppSpeed,    //�ϴ�ʱ�������
	type_UserSocial,  //�ϴ��û����罻��Ϊ������
	type_Exception    //�ϴ�appʹ�ù����е��쳣��Ϣ
};

//�ϴ������ݽṹ��
typedef struct
{
	interfaceType eventTypeInfo; // �ӿ����
	QString strCategory;  // ���
	QString strAction;    //������Ϊ
	QString strLabel;    //��ǩ
	QString strPageName;//ҳ������
	QString strVariable;//��������
	int iValue;        //��ֵ
	int iIndex;       //���
	QString strValue;
	QString strVersion;
	QString strLanguage;
    int Width;
    int Height;
	QString strNetWork;
	QString strTarget;
	QString strDescription;
	int iFatal;
	void gaInfo()
	{
		strCategory = "";
		strCategory = "";
		strAction = "";
		strLabel = "";
		strPageName = "";
		strVariable = "";
		iValue = 0;        
		iIndex = 0;
		strValue = "";
		strVersion = "";
		strLanguage = "";
		Width = 0;
		Height = 0;
		strNetWork = "";
		strAction = "";
		strTarget = "";
		strDescription = "";
		iFatal = 0;
	};
}*pGaInfo, gaInfo;

class  GAThread : public QThread
{
	Q_OBJECT

public:
	//����Ϊ����ģʽ������ȫ�ֻ�ȡ�̶߳���
	static GAThread* getInstance();
	//�����߳�
	void start();
	//����ǰ���߳�
	void suspendThread();
	//�ָ��߳�ִ��
	void  resumThread();
	//�����¼�����Ϣ
	void sendEventinfo(QString strCategory,QString strAction,QString strLabel);
	//�����ٶ�����Ϣ
	void sendAppSpeedInfo(QString strCategery,QString strVariable,int iValue);
	//������Ļ��Ϣ
	void sendScreenInfo(QString strPageName);
	//�����û��Զ���ά����Ϣ
	void setDimensioninfo(int iIndex, QString strValue);
	//���ͳ���汾��Ϣ
	void sendAppVersion(QString strVersion);
	//���ͳ���������Ϣ
	void sendLanguageInfo(QString strLanguage);
	//����Ӧ�ó��򴰿ڴ�С
	void sendViewSize(int Width, int Height);
	//�����Զ�����Ϣ
	void sendUserMetric(int iIndex, int iValue);
	//�����û��罻��Ϊ
	void SendSocialNetWorkInfo(QString strNetWork, QString strAction, QString strTarget);
	//��������쳣��Ϣ
	void SendExceptionInfo(QString strDescription, int iFatal);
	//���������̵߳ȴ���ʱ��
	void setWaitRunTime(int iWaitTime){ m_iWaitRunTime = iWaitTime; };

protected:
	//�߳�ִ����
	void run();
private:
	GAThread(QObject *parent);
	bool IsOn();
public:
	~GAThread();
private:
	QQueue <gaInfo> m_EventList;   //�¼�����
	QMutex m_SyncMutext;//���ڶԶ�����ͬ�����ʵĻ������
	QMutex m_TheadSuspendMutext;//�����߳���ͣ�Ļ������
	TUATracker* m_DataTraker;
	static QMutex m_Mutex;
	static GAThread* m_sGaThread;
	static QWaitCondition m_sWaitCondition;
	QSettings* m_Setting;
	bool m_bOn;
	int  m_iWaitRunTime; //�ȴ�������ʱ�䣬��λΪms
};
#endif // GATHREAD_H
