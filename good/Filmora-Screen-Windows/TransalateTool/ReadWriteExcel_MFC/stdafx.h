
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


//#import "C:\\Program Files (x86)\\Common Files\\Microsoft Shared\\OFFICE12\\MSO.DLL" \
//	rename("RGB", "MSORGB") \
//	rename("DocumentProperties", "MSODocumentProperties")
//using namespace Office;
//#import "C:\\Program Files (x86)\\Common Files\\Microsoft Shared\\VBA\VBA6\\VBE6EXT.OLB"
//
//using namespace VBIDE;
//#import "E:\\Program Files (x86)\\Microsoft Office\\Office12\\EXCEL.EXE" \
//	rename("DialogBox", "ExcelDialogBox") \
//	rename("RGB", "ExcelRGB") \
//	rename("CopyFile", "ExcelCopyFile") \
//	rename("ReplaceText", "ExcelReplaceText") \
//	no_auto_exclude
//using namespace Excel;




#if 1
#import "C:\\Program Files (x86)\\Common Files\\microsoft shared\\OFFICE14\\MSO.DLL" \
	rename("RGB", "MSORGB") \
	rename("DocumentProperties", "MSODocumentProperties")
using namespace Office;
#import "C:\\Program Files (x86)\\Common Files\\microsoft shared\\VBA\\VBA6\\VBE6EXT.OLB"

using namespace VBIDE;
#import "C:\\Program Files (x86)\\Microsoft Office\\Office14\\EXCEL.EXE" \
	rename("DialogBox", "ExcelDialogBox") \
	rename("RGB", "ExcelRGB") \
	rename("CopyFile", "ExcelCopyFile") \
	rename("ReplaceText", "ExcelReplaceText") \
	no_auto_exclude
using namespace Excel;
#else if 0

#import "C:\\Program Files (x86)\\Common Files\\Microsoft Shared\\OFFICE12\\MSO.DLL" \
	rename("RGB", "MSORGB") \
	rename("DocumentProperties", "MSODocumentProperties")
using namespace Office;
#import "C:\\Program Files (x86)\\Common Files\\Microsoft Shared\\VBA\VBA6\\VBE6EXT.OLB"

using namespace VBIDE;
#import "E:\\Program Files (x86)\\Microsoft Office\\Office12\\EXCEL.EXE" \
	rename("DialogBox", "ExcelDialogBox") \
	rename("RGB", "ExcelRGB") \
	rename("CopyFile", "ExcelCopyFile") \
	rename("ReplaceText", "ExcelReplaceText") \
	no_auto_exclude
using namespace Excel;
#endif


//ʹ��gdi+����gifͼƬ
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")


enum AppType
{
	Type_Translator,   //�滻��
	Type_Extrctor      //�ı���ȡ��
};

enum ExtractType
{
   Type_Default = 0,      //Ĭ����ȡģʽ
   Type_ExtractAll,       //��ȡ����
   Type_ExtractUnfinished,//��ȡ״̬ΪUnfinished״̬
};

//�����С��־
typedef struct
{
	long lWidth;
	long lHeight;
}FontFlag;

#define  CONFIG_FILENAME L"UserParam.xml"