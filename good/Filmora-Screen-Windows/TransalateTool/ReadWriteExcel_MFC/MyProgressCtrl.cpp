#include "stdafx.h"
//#include "ImageEx.h"
#include "Resource.h"
#include "gifHelper/PictureEx.h"
#include "MyProgressCtrl.h"




CMyProgressCtrl::CMyProgressCtrl()
{
    initData();
}


CMyProgressCtrl::~CMyProgressCtrl()
{
}

int CMyProgressCtrl::SetPos(int nPos)
{
    if (nPos < m_iMin)
    {
        m_iPos = m_iMin;
    }
    else if (nPos > m_iMax)
    {
        m_iPos = m_iMax;
    }
    else
    {
        m_iPos = nPos;
    }
	Invalidate();
	UpdateWindow();
    return m_iPos;
}

void CMyProgressCtrl::SetRange(int nLower, int nUpper)
{
    m_iMax = nUpper;
    m_iMin = nLower;
    m_iPos = nLower;
    m_nBarWidth = 0;
}

void CMyProgressCtrl::initData()
{
    m_freeColor = RGB(255,255,255);
    m_prgsColor = RGB(0,0,255);
    m_prgsTextColor = RGB(255,0,0);
    m_freeTextColor = RGB(0,255,0);
	SetRange(0,100);//Ĭ�ϵ�ȡֵ��Χ�� 0-100
	m_gifHelper = new CPictureEx();
	//BOOL bRec = m_gifHelper->Create(NULL, WS_CHILD | WS_VISIBLE | SS_CENTER,
	//	CRect(10, 10, 150, 30), this);
	// DWORD dRec = GetLastError();
	//int a = 0;
	//gifManager->AddGifImage(0, IDR_GIF);
}

BEGIN_MESSAGE_MAP(CMyProgressCtrl, CProgressCtrl)
    ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()


void CMyProgressCtrl::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO:  �ڴ˴������Ϣ����������
    // ��Ϊ��ͼ��Ϣ���� CProgressCtrl::OnPaint()
    CRect LeftRect, RightRect, ClientRect;
    GetClientRect(ClientRect);
    LeftRect = RightRect = ClientRect;
    double dFraction = (double)(m_iPos - m_iMin) / ((double)(m_iMax - m_iMin));
    //���ƽ���������ɲ���
    LeftRect.right = LeftRect.left + (int)((LeftRect.right - LeftRect.left) * dFraction);
    //����GifͼƬ
    //dc.FillSolidRect(LeftRect, m_prgsColor);
	int iTotalWidth = ClientRect.right - ClientRect.left;
	int iWidth = dFraction* iTotalWidth;
	if (iWidth != 0)
	{
		//�����ǰû�н��ȣ������
		m_gifHelper->SetPaintRect(CRect(0, 0, iWidth, 20));
	}
	else
	{
		m_gifHelper->SetPaintRect(CRect(0, 0, 1, 20));
	}
	
    //����ʣ�ಿ��
    RightRect.left = LeftRect.right;
    dc.FillSolidRect(RightRect, m_freeColor);
    //�����ı�
    m_strText.Format(_T("%d%%"), (int)(dFraction*100.00));
    dc.SetBkMode(TRANSPARENT);
    CRgn rgn;
    rgn.CreateRectRgn(LeftRect.left, LeftRect.top, LeftRect.right, LeftRect.bottom);
    dc.SelectClipRgn(&rgn);
    dc.SetTextColor(m_prgsTextColor);
    dc.DrawText(m_strText, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    rgn.DeleteObject();
    rgn.CreateRectRgn(RightRect.left, RightRect.top, RightRect.right, RightRect.bottom);
    dc.SelectClipRgn(&rgn);
    dc.SetTextColor(m_freeTextColor);
    dc.DrawText(m_strText, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rgn.DeleteObject();
}

int CMyProgressCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CProgressCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  �ڴ������ר�õĴ�������
	BOOL bRec = m_gifHelper->Create(NULL, WS_VISIBLE | SS_CENTER,
		CRect(0, 0, 0, 0), this);
	DWORD dRec = GetLastError();
	m_gifHelper->Load(MAKEINTRESOURCE(IDR_GIF), _T("Gif"));
	m_gifHelper->Draw();
	return 0;
}
