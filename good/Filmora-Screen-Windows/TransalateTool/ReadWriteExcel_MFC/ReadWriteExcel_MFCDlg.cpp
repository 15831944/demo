
// ReadWriteExcel_MFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <io.h>  
#include <algorithm>  
#include <locale>
#include <codecvt>
#include "Resource.h"
#include "ReadWriteExcel_MFC.h"
#include "ReadWriteExcel_MFCDlg.h"
#include "tinyxml2.h"
#include "afxdialogex.h"
#include "InfoDiaglog.h"
#include "MyProgressCtrl.h"
//#include "ImageEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace  std;
using namespace tinyxml2;
#pragma comment(lib,"tinyxml2.lib")


//ʹ��gdi+����gifͼƬ
#include <gdiplus.h>
#include "Utils\TranslateCtrl.h"
#include "Utils\FileFinderHelper.h"
#include "Cache.h"
#include "Utils\StringUtils.h"
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

#define PROGRESS_GIF   0
#define PROGRESS_VALUE 1




class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReadWriteExcel_MFCDlg �Ի���



CReadWriteExcel_MFCDlg::CReadWriteExcel_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReadWriteExcel_MFCDlg::IDD, pParent)
	, m_IsReplaceAll(FALSE)
	, m_strExcelPath(_T(""))
	, m_strProjectPath(_T(""))
	, m_strFilter(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadWriteExcel_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOURCETEXT, m_SourcePathText);
	DDX_Control(pDX, ID_RESULTPATHTEXT, m_ResultPathText);
	DDX_Check(pDX, IDC_FORCE_REPLACE, m_IsReplaceAll);
	DDX_Text(pDX, IDC_SETTARGETPATH, m_strExcelPath);
	DDX_Text(pDX, IDC_SETRESULTPATH_EDIT, m_strProjectPath);
	DDX_Text(pDX, IDC_FILTERBOX, m_strFilter);
}

BEGIN_MESSAGE_MAP(CReadWriteExcel_MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_FINDSOURCE, &CReadWriteExcel_MFCDlg::OnBnClickedFindsource)
	ON_BN_CLICKED(ID_SETRESULTPATH, &CReadWriteExcel_MFCDlg::OnBnClickedSetresultpath)
	ON_BN_CLICKED(ID_TRANSLATE, &CReadWriteExcel_MFCDlg::OnBnClickedTranslate)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_FILTERBOX, &CReadWriteExcel_MFCDlg::OnChangeFilterbox)
END_MESSAGE_MAP()

// CReadWriteExcel_MFCDlg ��Ϣ�������

BOOL CReadWriteExcel_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//��ʼ��combobox
	initUI();
	initData();
	LoadCacheData(m_TranslateCache->GetTranslateCache());
	//m_ExtractorButton->SetWindowTextW(L"11");
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CReadWriteExcel_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CReadWriteExcel_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CReadWriteExcel_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CReadWriteExcel_MFCDlg::OnBnClickedFindsource()
{
	CString workingDirectory;
	// OPTOINAL: Let's initialize the directory to the users home directory, assuming a max of 256 characters for path name:  
	wchar_t temp[256];
	GetEnvironmentVariable(_T("userprofile"), temp, 256);
	workingDirectory = temp;
	CFolderPickerDialog dlg(workingDirectory, 0, NULL, 0);
	if (dlg.DoModal())
	{
		if (dlg.GetPathName().CompareNoCase(m_SourceFilePathName))
		{
			//����û�����������excel·�������û��ٴη���
			GetDlgItem(ID_TRANSLATE)->EnableWindow(TRUE);
		}
		m_SourceFilePathName = dlg.GetPathName();
		//AfxMessageBox(m_SourceFilePathName);
	}

	//���������ؼ���ֵ
	GetDlgItem(IDC_SETTARGETPATH)->SetWindowText(m_SourceFilePathName);
	UpdateData(TRUE);
}

void CReadWriteExcel_MFCDlg::OnBnClickedSetresultpath()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString workingDirectory;
	// OPTOINAL: Let's initialize the directory to the users home directory, assuming a max of 256 characters for path name:  
	wchar_t temp[256];
	GetEnvironmentVariable(_T("userprofile"), temp, 256);
	workingDirectory = temp;
	CFolderPickerDialog dlg(workingDirectory, 0, NULL, 0);
	if (dlg.DoModal())
	{
		if (dlg.GetPathName().CompareNoCase(m_ResultFilePathName))
		{
			GetDlgItem(ID_TRANSLATE)->EnableWindow(TRUE);
		}
		m_ResultFilePathName = dlg.GetPathName();
	}
	//���������ؼ���ֵ
	GetDlgItem(IDC_SETRESULTPATH_EDIT)->SetWindowText(m_ResultFilePathName);
	UpdateData(TRUE);
}

void CReadWriteExcel_MFCDlg::OnBnClickedTranslate()
{	
	UpdateData(TRUE);
	m_TranslateCtrl->SetReplaceType((m_IsReplaceAll == TRUE)?true:false);
	if (!preChcek())
	{
		return;
	}
	m_TranslateCtrl->DoTranslate(m_strExcelPath.GetBuffer(), m_strProjectPath.GetBuffer(), m_strFilter.GetBuffer());
	//���û�ƫ��д�뻺��
	SaveCache();
}

void CReadWriteExcel_MFCDlg::SaveCache()
{
	string strExcelFile;
	string strProjectPathTmp;
	string strFilter;
	CStringUtils::WStringToString(m_strExcelPath.GetBuffer(), strExcelFile);
	CStringUtils::WStringToString(m_strProjectPath.GetBuffer(), strProjectPathTmp);
	CStringUtils::WStringToString(m_strFilter.GetBuffer(), strFilter);
	m_TranslateCache->SaveTranslateCache(strExcelFile, strProjectPathTmp, strFilter, (m_IsReplaceAll == TRUE)?true : false);
}

void CReadWriteExcel_MFCDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//SendMessage(WM_QUIT);
	//DestroyWindow();
	EndDialog(0);
	// CDialogEx::OnCancel();
	CDialogEx::OnClose();
}

void CReadWriteExcel_MFCDlg::initData()
{
	m_FilterValue = "";
	CString strTmp[8] = { L"ch", L"de", L"en", L"es", L"fr", L"it", L"pt", L"ja" };
	m_AllFilter.insert(m_AllFilter.begin(), &strTmp[0], &strTmp[7] + 1);

	//��ȡ��ǰ��������·��
	wstring strAppPath = CFileFinderHelper::GetAppPath();
	strAppPath = strAppPath + L"\\" + CONFIG_FILENAME;
	m_TranslateCache = new CCache(strAppPath.c_str());
}

void CReadWriteExcel_MFCDlg::initUI()
{
	m_ExtractorButton = new CButton();
	m_ExtractorButton->Create(L"Extractor", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, CRect(40, 40, 140, 100), this, 101);
	m_ExtractorButton->ShowWindow(false);
	SetDlgItemText(IDC_SOURCETEXT, L"Translate Excel Folder:");
	SetDlgItemText(ID_RESULTPATHTEXT, L"Translate Ts Folder:");
	//����Ӧ�ؼ���С �̶����ڴ�С  ����tooltip
	FontFlag fontSize = getStringSize(L"Translate Excel Folder:");
	//��ȡ�ؼ��ĵ�ǰλ��
	CRect rectPos;
	GetDlgItem(IDC_SOURCETEXT)->GetWindowRect(rectPos);
	GetDlgItem(IDC_SOURCETEXT)->SetWindowPos(NULL, rectPos.left, rectPos.top, fontSize.lWidth, fontSize.lHeight, SWP_NOZORDER | SWP_NOMOVE);
	GetDlgItem(ID_RESULTPATHTEXT)->GetWindowRect(rectPos);
	fontSize = getStringSize(L"Translate Ts Folder:");
	GetDlgItem(IDC_SOURCETEXT)->SetWindowPos(NULL, rectPos.left, rectPos.top, fontSize.lWidth, fontSize.lHeight, SWP_NOZORDER | SWP_NOMOVE);
	//::SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX); 
	//m_Tooltip.Create(this);
	//setToolTip(IDC_SOURCETEXT,L"��������excel��Ӧ���ļ���"); ��������Ts�ļ���Ӧ���ļ���
	EnableToolTips(TRUE);
	setToolTip();
	//���ô��ڵ����ƣ�
	SetWindowText(L"Translate tool");
	//�������Ʋ�
	m_TranslateCtrl = new CTranslateCtrl(this);
}

FontFlag CReadWriteExcel_MFCDlg::getStringSize(CString strText)
{
	//�����ı�������  
	CFont* ptf = GetDlgItem(IDC_SOURCETEXT)->GetFont(); // �õ�ԭ��������    
	LOGFONT lf;
	ptf->GetLogFont(&lf);
	FontFlag fontSize;
	CSize strSize;
	CDC *pDC = GetDC();
	strSize = pDC->GetTextExtent(strText);
	ReleaseDC(pDC);
	fontSize.lWidth = strSize.cx;
	fontSize.lHeight = strSize.cy;
	return fontSize;
}

void CReadWriteExcel_MFCDlg::setToolTip()
{
	BOOL bRec = m_Tooltip.Create(this);
	m_Tooltip.Activate(TRUE);
	m_Tooltip.AddTool(&m_SourcePathText, L"������excel �ļ����ڵ��ļ���");
	m_Tooltip.AddTool(&m_ResultPathText, L"������.TS �ļ����ڵ��ļ���");
	m_Tooltip.AddTool(GetDlgItem(IDC_FILTER), L"��������Ҫ������ض����ԣ��磺en pt fr��");
	//m_Tooltip.SetMaxTipWidth(123);
	m_Tooltip.SetTipTextColor(RGB(255, 0, 0));
	m_Tooltip.SetTipBkColor(RGB(255, 0, 255));
	//m_Tooltip.SetDelayTime(2500);
}

bool CReadWriteExcel_MFCDlg::preChcek()
{
	if (m_strExcelPath.IsEmpty() || m_strProjectPath.IsEmpty())
	{
		MessageBox(L"������Excel�ļ���ts�ļ�����·��", L"��ʾ", MB_OK);
		return false;
	}
	return true;
}

void CReadWriteExcel_MFCDlg::LoadCacheData(pTranslateCacheInfo info)
{
	m_strProjectPath = CStringUtils::stringToCString(info->strProjectPath);   
	m_strExcelPath = CStringUtils::stringToCString(info->strExcelPath);
	m_strFilter = CStringUtils::stringToCString(info->strFilter);
	m_IsReplaceAll = (CStringUtils::stringToCString(info->strIsForceReplace) == "true") ? TRUE : FALSE;
	UpdateData(FALSE);
	delete info;
}

void CReadWriteExcel_MFCDlg::OnChangeFilterbox()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strCurValue;
	GetDlgItemText(IDC_FILTERBOX, strCurValue);
	strCurValue.Trim();
	if (strCurValue.CompareNoCase(m_FilterValue) != 0)
	{
		GetDlgItem(ID_TRANSLATE)->EnableWindow(TRUE);
	}
	UpdateData(TRUE);
}

BOOL CReadWriteExcel_MFCDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	ASSERT(pMsg != NULL);
	if (pMsg->message == WM_MOUSEMOVE || pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONUP)
		if (m_Tooltip.m_hWnd != NULL)
		{
		m_Tooltip.RelayEvent(pMsg);
		}
	return CDialogEx::PreTranslateMessage(pMsg);
}

