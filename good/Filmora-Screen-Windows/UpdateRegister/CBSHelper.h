#pragma once

#include <Unknwn.h>

// �ύ��������
enum CBSRegCheckType
{
	// ����ʱ���
	rcCheckOnStart = 0,
	// ע��ʱ���
	rcCheckOnRegist = 1,
	// Ƶ�����
	rcCheckcontinually = 2
};

enum CBSRegCheckResult
{
	// �����û���������ʾע��ɹ�
	crOK,
	// �����û����ڵ���ע��ɹ���ʾ֮ǰ����������ʾ��������ʾ����ʾע��ɹ�
	crWarning,
	// �������Ӵ���
	crError,
	// �Ƿ��û������ע����Ϣ��������������ʾ���û������˳�����Ҳ�ɼ���ע��
	crQuit,
	// �˿��û����ɲ�Ʒ�����Ƿ����û�����ʹ��
	crRefund
};

typedef void(__stdcall * RegCheckCallBack)(CBSRegCheckResult checkResult, wchar_t* pszMessage);

class ICBSHelper : public IUnknown
{
public:
	virtual void __stdcall Init(int nProdId, wchar_t* pszVersion, wchar_t* pszEmail) = 0;
	virtual bool __stdcall Start() = 0;
	virtual void __stdcall LocalRegister(wchar_t* pszEmail, wchar_t* pszRegCode) = 0;
	virtual void __stdcall SetRegCheckCallBack(RegCheckCallBack pCallBack) = 0;
	virtual void __stdcall RegCheck(wchar_t* pszEmail, wchar_t* pszLang, CBSRegCheckType checkType) = 0;
};

typedef void(__stdcall * CreateCBSHelper)(ICBSHelper* &pCBSHelper);