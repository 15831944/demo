#pragma once
#include "afxcmn.h"

class ImageManager;
class CPictureEx;
class CMyProgressCtrl :
    public CProgressCtrl
{
public:
    CMyProgressCtrl();
    ~CMyProgressCtrl();
    int SetPos(int nPos);
    void SetRange(int nLower, int nUpper);
    void setText(CString strText){ m_strText = strText; };
    void initData();

private:
    CImage m_ProgressGif; //��ʾ�Ѿ�������ɲ��ֵ�gifͼƬ
    COLORREF m_prgsColor; //���������Ȳ�����ɫ
    COLORREF m_freeColor;//������������ಿ����ɫ
    COLORREF m_prgsTextColor; //���Ȳ���������ɫ
    COLORREF m_freeTextColor; //�հײ���������ɫ
    int  m_iMin;    //����������Сֵ��ͨ����0
    int  m_iMax;    //�����������ֵ��ͨ����100
    int  m_iPos;    //��ǰ�Ľ���
    int  m_nBarWidth;  //���������
    CString m_strText;//��ǰ����ֵ
	//ImageManager* gifManager;   //gifͼƬ������
	CPictureEx*  m_gifHelper;
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

