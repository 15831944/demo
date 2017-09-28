#ifndef UPDATEHELPER_H
#define UPDATEHELPER_H

#include <QObject>
class UpdateMain;
class RegisterMain;
class CBSUrlReader;
class UpdateRegisterPurchaseHelper : public QObject
{
	Q_OBJECT
public:
	static UpdateRegisterPurchaseHelper* GetInstance();
	void DoAutoUpdate();
	void Register();
	void Purchase();
	//������ʱ������Ƿ�ע��ļ��
	void RegisterCheckOnStart();

	bool IsRegistered();
	void RebuildRegisterMain(bool bTellEditor = false);
private:
	UpdateRegisterPurchaseHelper(QObject *parent = 0);
	void OnBeginInstall();
	void OnInstallStarted();
	void OnAutoQuery();
	QString GetCurrentLang();

Q_SIGNALS:
	//�ɹ�ע����ź�
	void singnalSucessRegister(bool bResult);
	void singnalStartRegister(const QDateTime time);
	//����ʱ�ж�ע��
	void signalCheckOnStart(bool bResult);
	void sigRegisterResult(bool bResult);
private:
	UpdateMain *m_pUpdateMain;
	RegisterMain* m_pRegisterMain;
	QTimer m_timer;
	QSettings *m_pSetting;
	CBSUrlReader *m_pCBSUrlReader;
};

#endif // UPDATEHELPER_H
