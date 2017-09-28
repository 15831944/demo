#ifndef UPDATECOMMON_H
#define UPDATECOMMON_H
#include "CommonWidgets.h"
#include <QWidget>

//�����ص�XML�ļ�����
class VersionInfo : public QObject
{
	Q_OBJECT

public:
	VersionInfo(QString xml, QObject *parent = 0);

	//���ð汾��Ϣ��XML�ļ�
	void SetXML(QString xml);

	//�Ƿ��пɸ��°汾
	bool HasUpdateVersion();

	//����WhatNews��ǩ����
	//QString GetWhatNews();
	QList<QPair<QString, QString>> GetWhatNews();

	//�����°汾����·��
	QString GetNewVersionPath();

	//�����°汾�ļ���
	QString GetNewVersionName();

private:
	void ParseXml();
	QString Normalization(QString text);

private:
	QString m_xml;
	QString m_newVersionPath;
	QList<QPair<QString, QString>> m_whatNews;  //QPair<Version, Text>
};

//������������
#include <QThread>
#include <QTimer>
class NetworkCheck : public QObject
{
	Q_OBJECT

public:
	NetworkCheck();
	~NetworkCheck();
	//���ü��ʱ��
	void SetInterval(int msec);
	//����bytesReceived
	void SetBytesReceived(int64_t bytesReceived);
	int64_t GetLastBytesReceived();
	//���
	void Check();
	//ֹͣ���
	void StopCheck();

signals:
	//��ʱ�ź�
	void TimeOut();

protected:
	Q_INVOKABLE void _StopCheck();
	Q_INVOKABLE void _Check();

private:
	QThread *m_pThread;
	QTimer *m_pTimer;
	int64_t m_bytesReceived;
};

//���ع�����
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QProcess>
class URMessageBox;
class DownloadMgr : public QObject
{
	Q_OBJECT

public:
	DownloadMgr(QObject *parent = 0);
	~DownloadMgr();
	//���ؽӿڣ������ļ�������·��
	void Download(QString filePath, QUrl url);
	//ȡ������
	void DownloadCancel();
	//��װ�°汾
	void Install();
	//��ȡ�����ļ�·��������·���������ļ�����
	QString GetSetupFilePath();
	//��װָ���ļ�
	void InstallSetupFile(QString path);

signals:
	//���ؽ�����Ϣ�ź�
	void DownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	//�����ź�
	void Error(QString error);
	//�رմ����ź�
	void Close();
	//��������ź�
	void DownloadFinished();
	//��ʼ��װ�ź�
	void BeginInstall();
	//ȡ����װ�ź�
	void CancelInstall();
	//�°汾��װ������ȫ�����ź�
	void InstallStarted();

protected:
	bool event(QEvent*) override;
	void ReTranslateUI();

private slots:
	void ReplyFinished(QNetworkReply *reply);
	void ReadyRead();
	void DownloadProgressMgr(qint64 bytesReceived, qint64 bytesTotal);
	void ReplyError(QNetworkReply::NetworkError code);	

private:
	QProcess *m_process;
	QFile m_file;
	QUrl m_downloadUrl;
	QNetworkAccessManager *m_networkMgr;
	QNetworkReply *m_reply;
	NetworkCheck *m_networkCheck;
	int64_t m_bytesReceived;
	URMessageBox *m_messageBox;
	bool m_bInstall;
	std::string m_errorString;
};

//��ʾ������Ϣ�Ĵ���
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>

class ProgressDisplay : public URBaseWidget
{
	Q_OBJECT
public:
	enum ShowState{ShowState_Normal, ShowState_Download};

public:
	ProgressDisplay(QWidget *parent = 0);
	//���ý�����Ϣ
	void SetText(QString info);
	//���ý�����ΪbusyЧ��
	void SetBusyEffect();
	//���ý��������ֵ
	void SetMaximum(qint64 max);
	//���ý�������Сֵ
	void SetMinimum(qint64 min);
	//���ý�������Χ
	void SetRange(qint64 min, qint64 max);
	//���ý�������ʾ��ʽ
	void SetFormat(const QString& format);
	//���ý�������ǰֵ
	void SetValue(qint64 value);
	//���õ�ǰ��ʾ״̬
	void SetShowState(ShowState state);
	ShowState GetCurrentState();

signals:
	//close��ť�ź�
	void Close();

protected:
	void resizeEvent(QResizeEvent *) override;
	virtual void RetranslateUi();

private:
	ShowState m_showState;
	QLabel *m_infoLabel;
	QLabel *m_valueLabel;
	QProgressBar *m_progressBar;
	QPushButton *m_closeBtn;
};

//��ʾ�ɸ��°汾��Ϣ�Ĵ���
#include <QPushButton>
#include <QScrollArea>
class VersionDisplay : public URBaseWidget
{
	Q_OBJECT

public:
	VersionDisplay(QWidget *parent = 0);
	//����չʾ������
	void SetText(QString text);

signals:
	//Update Now ��ť�����ź�
	void UpdateNow();
	//Remind Me Later ��ť�����ź�
	void RemindMeLater();

protected:
	void resizeEvent(QResizeEvent *) override;
	virtual void RetranslateUi();

private:
	QScrollArea *m_scrollArea;
	QLabel *m_versionsLabel;
	QPushButton *m_updateNowBtn;
	QPushButton *m_remindMeLaterBtn;
};

//��ʾ�����ظ��£��Լ����ִ�����ʾ�Ĵ���
class HintDisplay : public URBaseWidget
{
	Q_OBJECT

public:
	HintDisplay(QWidget *parent = 0);
	//������ʾ��Ϣ����
	void SetHint(QString hint);

protected:
	void resizeEvent(QResizeEvent *) override;
	virtual void RetranslateUi();

signals:
	//�رմ����ź�
	void Close();

private:
	QLabel *m_label;
	QPushButton *m_closeBtn;
};

class NetworkAccessManagerTimeout : public QThread
{
    // ���ż����QNetworkAccessManager->get����������
    // ���߳̽���get�������糬ʱֱ��TerminateThread�߳�
    Q_OBJECT
public:
    NetworkAccessManagerTimeout(QObject *parent = nullptr);
    ~NetworkAccessManagerTimeout();

    QByteArray get(QNetworkRequest request, int waittime = 5000);

    bool error();

protected:
    void run() override;

private:
    QNetworkRequest m_request;
    QNetworkReply *m_reply;
    QByteArray m_bypteArray;
    bool m_bError;
};
#endif // UPDATECOMMON_H
