// TranslatView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReadWriteExcel_MFC.h"
#include "TranslatView.h"
#include "afxdialogex.h"


// CTranslatView �Ի���

IMPLEMENT_DYNAMIC(CTranslatView, CDialogEx)

CTranslatView::CTranslatView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTranslatView::IDD, pParent)
{

}

CTranslatView::~CTranslatView()
{
}

void CTranslatView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTranslatView, CDialogEx)
END_MESSAGE_MAP()


// CTranslatView ��Ϣ�������
