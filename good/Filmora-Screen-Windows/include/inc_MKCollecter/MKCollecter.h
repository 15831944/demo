#ifndef MKCOLLECTER_H
#define MKCOLLECTER_H

#include "mkcollecter_global.h"
#include <QObject>
#include <QPoint>

class MKCOLLECTER_EXPORT MKCollecter : public QObject
{
	Q_OBJECT
public:
	enum ModifyKey
	{
		ModifyKey_Control = 0x01,
		ModifyKey_Shift = 0x02,
		ModifyKey_Alt = 0x04,
        ModifyKey_Win = 0x08,
	};

	static MKCollecter* GetInstance();
 	virtual bool SetMouseHook(bool bInstall) = 0;
	virtual bool SetKeyboardHook(bool bInstall) = 0;
    virtual bool GetMouseHook() = 0;
    virtual bool GetKeyboardHook() = 0;
	// ��ȡ��ǰ��HotKeystring, �ڰ���Control��ʱ���ã������磺Ctr+F1
	virtual QString GetHotKeyString() = 0;
	// �Ƿ����´��ݿ�ݼ�
	virtual void EnalbedHotKeyDeliver(bool enabled) = 0;
	virtual bool GetEnalbedHotKeyDeliver() = 0;

	// ��ȡvirtualKey��String
	virtual QString GetKeyString(int virtualKey) = 0;
	virtual void AddHotKey(QString key) = 0;
	virtual void ClearHotKey() = 0;
	virtual void RemoveHotKey(QString key) = 0;
Q_SIGNALS:
	void sigMouseMove(QPoint pt);
	void sigLButtonUp(QPoint pt);
    void sigLButtonDown(QPoint pt);
    void sigRButtonUp(QPoint pt);
    void sigRButtonDown(QPoint pt);
    void sigKeyPressed(int virtualKey, int modifyKey);   //�÷� ��modifyKey & ModifyKey_Control != 0 , ��ʾControl��������
	void sigKeyUp(int virtualKey);
};

#endif // MKCOLLECTER_H
