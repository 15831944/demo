
// ReadWriteExcel_MFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CReadWriteExcel_MFCApp: 
// �йش����ʵ�֣������ ReadWriteExcel_MFC.cpp
//

class CReadWriteExcel_MFCApp : public CWinApp
{
public:
	CReadWriteExcel_MFCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CReadWriteExcel_MFCApp theApp;