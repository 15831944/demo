#pragma once
#include <string>
#include <vector>
#include <map>
#include "Cache.h"

using namespace std;

// CExtractorTabelView �Ի���
class CMyProgressCtrl;
class CExtractorCtrl;
class CExtractorTabelView : public CDialogEx
{
	DECLARE_DYNAMIC(CExtractorTabelView)

public:
	CExtractorTabelView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExtractorTabelView();

// �Ի�������
	enum { IDD = IDD_EXTRACTORVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSetResultpathBtn();
	afx_msg void OnBnClickedSetProjectpathBtn();
	afx_msg void OnBnClickedExtractor();
	afx_msg void OnEnChangeExtractfilter();
private:
	void InitData();
	bool preChcek();
	//���ػ�������
	void LoadCacheData(pExtactCacheInfo info);
	void SaveCache();//���滺��
private:
	CString m_ResultPath;
	CString m_ProjectPath;
	CString m_FilterValue;
	bool m_IsExtractAll; //�Ƿ���ȡ���е��ַ�
	CExtractorCtrl* m_ExtractorDataCtrl;
public:
	virtual BOOL OnInitDialog();
	BOOL m_ExtractCheckbox;
	CCache* m_Cache;
	BOOL m_bIsExtractUnfinished; //�Ƿ������ȡunfinished״̬���ı�
	afx_msg void OnBnClickedExtractUnfinished();
	afx_msg void OnBnClickedExtractAll();
	BOOL m_bIsRemoveDuplicate; //�Ƿ����ȡ������ȥ��
};
