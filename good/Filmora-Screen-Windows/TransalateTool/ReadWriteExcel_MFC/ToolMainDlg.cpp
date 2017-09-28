// ToolMainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReadWriteExcel_MFC.h"
#include "ToolMainDlg.h"
#include "afxdialogex.h"


// CToolMainDlg �Ի���

IMPLEMENT_DYNAMIC(CToolMainDlg, CDialogEx)

CToolMainDlg::CToolMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolMainDlg::IDD, pParent)
{

}

CToolMainDlg::~CToolMainDlg()
{
}

void CToolMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABCtl, m_TableCtl);
}


BEGIN_MESSAGE_MAP(CToolMainDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABCtl, &CToolMainDlg::OnTcnSelchangeTabctl)
END_MESSAGE_MAP()


// CToolMainDlg ��Ϣ�������


BOOL CToolMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_TableCtl.InsertItem(0, L"Translate");
	m_TableCtl.InsertItem(1, L"Extractor");

	m_ExtractorView.Create(IDD_EXTRACTORVIEW, GetDlgItem(IDC_TABCtl));
	m_TranslateView.Create(IDD_TRANSLATEVIEW, GetDlgItem(IDC_TABCtl));

	//���IDC_TABTEST�ͻ�����С 
	CRect rs;
	m_TableCtl.GetClientRect(&rs);
	//�����ӶԻ����ڸ������е�λ�� 
	rs.top += 20;
	//rs.bottom -= 60;
	//rs.left += 10;
	//rs.right -= 2;

	//�����ӶԻ���ߴ粢�ƶ���ָ��λ�� 
	m_ExtractorView.MoveWindow(&rs);
	m_TranslateView.MoveWindow(&rs);
	//�ֱ��������غ���ʾ 
	m_TranslateView.ShowWindow(true);
	m_ExtractorView.ShowWindow(false);
	//����Ĭ�ϵ�ѡ� 
	m_TableCtl.SetCurSel(0);

	//�޸��������С
	SetWindowPos(NULL, 0, 0, 650, 400, SWP_NOZORDER | SWP_NOMOVE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CToolMainDlg::OnTcnSelchangeTabctl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	int iCurSel = m_TableCtl.GetCurSel();
	switch (iCurSel)
	{
	case 0:
		m_TranslateView.ShowWindow(true);
		m_ExtractorView.ShowWindow(false);
		break;
	case 1:
		m_TranslateView.ShowWindow(false);
		m_ExtractorView.ShowWindow(true);
		break;
	default:
		break;
	}
}
