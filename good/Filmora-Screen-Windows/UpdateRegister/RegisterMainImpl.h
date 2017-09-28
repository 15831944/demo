#ifndef REGISTERMAINIMPL_H
#define REGISTERMAINIMPL_H

#include <QDialog>
#include <QSettings>

#include "RegHelper.h"
#include "CBSHelper.h"
#include "CBSUrlReader.h"
#include "CommonWidgets.h"

class QLabel;
class QLineEdit;
class QPushButton;
class CheckTimer;
class TitleBar;
class URMessageBox;

#include <QThread>
class CheckTimer : public QObject
{
	Q_OBJECT

public:
	CheckTimer();
	~CheckTimer();
	//������ʱ���
	void Check();
	//�رռ��
	void StopCheck();

signals:
	void TimeOut();

private:
	Q_INVOKABLE void _Check();
	Q_INVOKABLE void _StopCheck();

private:
	QThread *m_pThread;
	QTimer *m_pTimer;
};


class LineEditInvalidInputAlert;

class RegisterMainImpl : public URBaseWidget
{
	Q_OBJECT

public:
	//������ͣ�CheckOnStart��������������ʱ����飻CheckOnRegist����ע��ʱ�����
	enum CheckType{ CheckOnStart, CheckOnRegist };

public:
	RegisterMainImpl(QWidget *parent = 0);
	~RegisterMainImpl();
	//����ģ�����������ע��DLL
	bool LoadRegisterDLL();
	//����ģ����Զ�����Ƿ�ע���
	bool CheckRegister();
	//����ʱ������ע����
	void RegisterCheckOnStart();
	//ȡ��ע��ӿ�
	void DoUnregistered();
	void RegCheckFunc(CBSRegCheckResult checkResult, wchar_t* pszMessage);
	//д��ע��ɹ��¼���Ϣ��ע�����
	void WriteRegDate();
	// ��ȡ��ǰ��������
	QString GetLocalLanguage();
	// ��ȡ��Ʒid����id�뵱ǰ���������й�
	int GetProductID();
	// ��ȡ��ǰ�汾��
	QString GetCurVersion();

Q_SIGNALS:  //for wb
	//����ע���ź�
	void singalStartRegister(const QDateTime time);
	void signalCheckOnStart(bool bResult);
	void signalCheckOnRegist(bool bResult, QDateTime time);

protected:
	void resizeEvent(QResizeEvent*) override;
	void showEvent(QShowEvent*) override;
	virtual void RetranslateUi();
	bool eventFilter(QObject *, QEvent *) override;

signals:
	//���̹����ź�
	void BuyNow();
	//free trial�ź�
	void FreeTrial();
	//�رմ����ź�
	void Close();
	//�˿��ź�
	void ReFund();
	//�ƶ������ź�
	void Move(int x, int y);
	//ע��ɹ���Ϣ
	void singnalSucessReg(QDateTime time);

private:
	void RegisterFunc();
	void BuyNowFunc();
	void TrialFunc();
	void CloseFunc();
    bool IsHex(QString text);
	// char* to wchar_t*
	wchar_t *AToW(char* src);
	// wchar_t * to char *
	char *WToA(wchar_t *src);
	// ���ð�ť״̬
	void SetButtonsEnable(bool enabled);
	wchar_t* _GetLocalLanguage();

private:
	bool m_bReturn;
	bool m_bDone;
	QSettings m_settings;
	CheckType m_checkType;
	CheckTimer *m_pCheckTimer;
	QString m_prodId;
	QString m_curVersion;
	HMODULE m_registerDLL;
	IRegHelper *m_regHelper;
	ICBSHelper *m_cbsHelper;
	CBSUrlReader *m_cbsUrlReader;
	QLabel *m_captionLabel;
	QLabel *m_emailLabel;
	QLabel *m_regCodeLabel;
    LineEditInvalidInputAlert *m_email;
    LineEditInvalidInputAlert *m_regCode;
    QPushButton *m_registerBtn;
	QPushButton *m_buyNowBtn;
	QPushButton *m_trialBtn;
	QPushButton *m_closeBtn;
	TitleBar *m_titleBar;
	URMessageBox *m_messageBox;
};

class LineEditInvalidInputAlert : public QLineEdit
{
    Q_OBJECT
public:
    LineEditInvalidInputAlert(QWidget *parent);
    
    void Invalid(bool invalid);
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *watcher, QEvent *event);
private:
    bool m_invalid;
    QWidget *m_alertWidget;
};


#endif // REGISTERMAINIMPL_H
