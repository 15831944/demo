
// ReadWriteExcel_MFCDlg.h : ͷ�ļ�
//

#pragma once
#include <map>
#include <list>
#include <vector>
#include ".\excelReader\Application.h"
#include ".\excelReader\Workbooks.h"
#include ".\excelReader\Workbook.h"
#include ".\excelReader\Worksheets.h"
#include ".\excelReader\Worksheet.h"
#include ".\excelReader\Range.h"
#include "tinyxml2.h"
#include "afxwin.h"
#include "Cache.h"
using namespace std;
class CMyProgressCtrl;
class CTranslateCtrl;

#define WM_UNMATCH_TEXT (WM_USER+100)


// CReadWriteExcel_MFCDlg �Ի���
class CReadWriteExcel_MFCDlg : public CDialogEx
{
// ����
public:
	CReadWriteExcel_MFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TRANSLATEVIEW };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedFindsource();
    afx_msg void OnBnClickedSetresultpath();
    afx_msg void OnBnClickedTranslate();

	

	afx_msg void OnClose();
private:
	//��ʼ����Ա����
	void initData();
	//��ʼ������
	void initUI();
	//��ȡ�ض�����ĳ���
	FontFlag getStringSize(CString strText);
	//��ʾ�ض���tooltip
	void setToolTip();
   //����ǰ��Ԥ���
	bool preChcek();
	//���ػ�������
	void LoadCacheData(pTranslateCacheInfo info);
	//���浱ǰ�Ļ�������
	void SaveCache();

private:
    CString m_SourceFilePathName;//�洢�����Ӧ��ϵ��excel�ļ�
    CString m_ResultFilePathName; //��Ҫ�������ļ��ľ���·��
	CString        m_FilterValue;       //��������ֵ�û������ض���ts�ļ�
	list<CString>  m_AllFilter;         //��ǰ֧�ֵĹ��˲���
	CButton*         m_ExtractorButton; //��ȡ��ť
	CToolTipCtrl     m_Tooltip;         //��ʾtooltip
	// excel�ļ������ļ���
	CStatic m_SourcePathText;
	// ts�ļ������ļ���
	CStatic m_ResultPathText;
public:
	afx_msg void OnChangeFilterbox();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	CTranslateCtrl* m_TranslateCtrl;
	BOOL m_IsReplaceAll;      
	CString m_strExcelPath;
	CString m_strProjectPath;
	CString m_strFilter;
	CCache* m_TranslateCache; //�������
};
