#ifndef LIVEUPDATEMGR_H
#define LIVEUPDATEMGR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSettings>

class ProgressDisplay;
class VersionDisplay;
class HintDisplay;
class VersionInfo;
class DownloadMgr;

class LiveUpdateMgr : public QObject
{
	Q_OBJECT

public:
	enum CheckType{AutoCheck, ManualCheck};

public:
	LiveUpdateMgr(ProgressDisplay *progressDisplay, VersionDisplay *versionDisplay, HintDisplay *hintDisplay, QObject *parent = 0);
	~LiveUpdateMgr();

	//������
	void LiveUpdate(QString productId, QString version, QString email);
	void LiveUpdate();
	bool IsNeedUpdate();
	//cancel ȡ������
	void Cancel();
	//��װ�°汾
	void Install();

signals:
	void SetCurrentWidget(QWidget *);
	void Close();
	//��ʼ��װ�ź�
	void BeginInstall();
	//ȡ����װ�ź�
	void CancelInstall();
	//�°汾��װ������ȫ�����ź�
	void InstallStarted();
	//Remind Me Latter�ź�
	void RemindMeLater();

private:
	void _LiveUpdate();
	void _LiveUpdate(QString productId, QString version, QString email);
	void UpdateNow();
	void ReplyFinished(QNetworkReply *);
	QUrl FormatURL(const QString& productId, const QString& version, const QString& email);
	void DownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	QString BytesToString(qint64 bytes);
	void DownloadXML();

private:
	CheckType m_checkType;
	QString m_updateUrl;
	QSettings m_settings;
	QNetworkAccessManager *m_networkMgr;
	QNetworkRequest m_request;
	ProgressDisplay *m_progressDisplay;
	VersionDisplay *m_versionDisplay;
	HintDisplay *m_hintDisplay;
	VersionInfo *m_versionInfo;
	QNetworkReply *m_reply;
	qint64 m_bytesTotal;
	DownloadMgr *m_downloadMgr;
};

#endif // LIVEUPDATEMGR_H
