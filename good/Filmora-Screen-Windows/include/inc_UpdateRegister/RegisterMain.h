#ifndef REGISTERMAIN_H
#define REGISTERMAIN_H

#include "inc_UpdateRegister/UpdateRegister_global.h"

#include <QDialog>

class RegisterMainImpl;

//ע��ģ��
class UPDATEREGISTER_EXPORT RegisterMain : public QDialog
{
	Q_OBJECT

public:
	RegisterMain(QWidget *parent = 0);
	~RegisterMain();

	//ע��ӿ�
	void DoRegister();
	//����ʱע����
	void RegisterCheckOnStart();
	//ȡ��ע��
	void DoUnregistered();
	//����Ƿ�ע��
	bool CheckRegister();
	
signals:
	//���̹����ź�
	void BuyNow();
	//free trial�ź�
	void FreeTrial();
	//��⵽�û����˿��û�ʱ�����ʹ��ź�
	void ReFund();
	//ע���Ƿ�ɹ��ź�
	void RegisterResult(bool bSuccessfull);  // �رմ��ڣ����źŻᷢ��
	//����ע���ź�
	void singalStartRegister(const QDateTime time);
	void signalCheckOnStart(bool bResult);  // for wb
	void signalCheckOnRegist(bool bResult,  QDateTime time);  // for wb

private:
	RegisterMainImpl *m_pImpl;
};


class UPDATEREGISTER_EXPORT RegisterInit
{
public:
	static void SetBuyNowUrl(QString url);
	static QString GetBuyNowUrl();
};

#endif // REGISTERMAIN_H
