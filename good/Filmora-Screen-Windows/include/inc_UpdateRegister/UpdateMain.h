#ifndef UPDATEMAIN_H
#define UPDATEMAIN_H

#include "inc_UpdateRegister/UpdateRegister_global.h"

#include <QWidget>

class UpdateMainImpl;

//��������ģ��
class UPDATEREGISTER_EXPORT UpdateMain : public QDialog
{
	Q_OBJECT

public:
	UpdateMain(QWidget *parent = 0);
	/**
	 *@brief     �����������������ں󣬼����ô˷���
	 *@param     productId ��ǰ��Ʒid
	 *@param     version   ��ǰ��Ʒ�汾��
	 *@param     email     �û�����
	 */
	void LiveUpdate(QString productId, QString version, QString email);

	//����������productId��version��email�Ȳ�����Ĭ�ϴ������ļ������ж���
	void LiveUpdate();

	//�ж��Ƿ��пɸ��°汾�������������⣬ͬ������false
	bool IsNeedUpdate();

	//��װ�°汾����Ҫ�������������ã��ŻῪʼ��װ�°汾
	void Install();

signals:
	//��ʼ��װ�ź�
	void BeginInstall();
	//ȡ����װ�ź�
	void CancelInstall();
	//�°汾��װ������ȫ�����źš��߼��ϣ���������յ����źź󣬾Ϳ����˳��ˡ�
	void InstallStarted();
	//�رմ����ź�
	void Close();
	//Remind Me Later�ź�
	void RemindMeLater();

private:
	UpdateMainImpl *m_pImpl;
};

class UPDATEREGISTER_EXPORT UpdateInit
{
public:
	static void SetUpdateUrl(QString url);
	static QString GetUpdateUrl();
};

#endif // UPDATEMAIN_H
