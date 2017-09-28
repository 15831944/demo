#pragma once
// CTranslatView �Ի���
#include "stdafx.h"
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
#include "afxcmn.h"

using namespace std;
class CMyProgressCtrl;
class CTranslatView : public CDialogEx
{
	DECLARE_DYNAMIC(CTranslatView)

public:
	CTranslatView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTranslatView();

// �Ի�������
	enum { IDD = IDD_TRANSLATE };

public:
	//��ȡexcel�ļ��е�����
	void ReadExcelFile();
	//��ȡts�е�����
	void ReadTsFile();
	//��ȡ��ǰ��Ŀ�µ�����ts�ļ�
	void GetAllTsFile();
	//��ȡ�ض����Ե�ts�ļ��ļ���
	vector<string> getTsFileByLanguage(string strLanguageType);
	//���з��빤��
	void DoTranslate();
	int GetColumnCount();
	int GetRowCount();
	CString GetCell(long iRow, long iColumn);
	void PreLoadSheet();
	void TranslateTsFile();
	std::string TraslateRawData(std::string strRawData, std::string strType);
	//���������ļ�ת����UTF8�����ʽ
	void ConvertTsFileToUTF8();
	void GetAllFormatFiles(string path, vector<string>& files, string format);

	
	//��ȡ��ǰ������������е�ts�ļ���������һ���ض����ļ�����
	void find(wchar_t* lpPath, std::vector<std::string> &fileList, wchar_t* strFileType);
	//��û��ƥ����ֶ�д���ļ���
	void saveUnMatchFile();
	string getTsFileType(wstring strFileName);

	//��ʼ����Ա����
	void initData();
	//��ʼ������
	void initUI();

	//��ʾ�ض���tooltip
	void setToolTip();
	//�Ż����滻ʵ�����
	CString ReplaceEntitySymbols(CString strText);
	//��ȡxml�ض��ڵ�Ԫ��
	bool GetNodePointerByName(tinyxml2::XMLElement* pRootEle, std::string &strNodeName, tinyxml2::XMLElement* &Node);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CString m_SourceFilePathName;//�洢�����Ӧ��ϵ��excel�ļ�
	CString m_ResultFilePathName; //��Ҫ�������ļ��ľ���·��
	map<std::string, map<CString, CString>> m_AllLanguageMap;//ȫ�����ֵ䣻
	map<CString, CString> m_TranslateMap;//�����Ӧ��ϵ��ֵ��
	multimap<CString, CString> m_UnMatchMap;//δƥ�䵽���ַ������ֵ�
	CApplication m_ExcelApp;
	CWorkbooks m_books;
	CWorkbook m_book;
	CWorksheets m_sheets;
	CWorksheet m_sheet;
	CRange m_range;
	///�Ƿ��Ѿ�Ԥ������ĳ��sheet������
	BOOL          already_preload_;
	///Create the SAFEARRAY from the VARIANT ret.
	COleSafeArray ole_safe_array_;
	vector<string> m_AllExcelFile;//���е�excel�ļ��ļ���
	vector<string> m_AllTsFile; //���е�ts�ļ��ļ���
	vector<string> m_AllEnTsFile; //��ǰ��Ŀ�����е�Ӣ�İ汾��ts�ļ�����
	CString        m_CurrentHandleTsFile;//��ǰ���ڴ����ts�ļ���
	CString        m_UnMatchTextFilePath;//����δƥ�䵽���ַ������ļ�·��
	CString        m_CurrentHandleTsPath;//��ǰ���ڱ������Ts���ļ���·��
	CString        m_FilterValue;       //��������ֵ�û������ض���ts�ļ�
	list<CString> m_AllFilter;         //��ǰ֧�ֵĹ��˲���
	CMyProgressCtrl* progress;
	bool             m_IsReOpenExcelFile; //�Ƿ����´�excel�ļ�
	bool             m_ISReoOpenTsFile; //�Ƿ����´�Ts�ļ�
	bool             m_IsExtrcted;     //��ǰts�ļ��Ƿ��Ѿ��滻��
	AppType             m_CurAppType;      //��ǰҳ������
	CButton*         m_ExtractorButton; //��ȡ��ť
	CToolTipCtrl     m_Tooltip;         //��ʾtooltip
	//// excel�ļ������ļ���
	CStatic m_SourcePathText;
	//// ts�ļ������ļ���
	CStatic m_ResultPathText;
	//��ǰ�߱�excel�ļ����������ͼ���
	list<CString> m_ReplaceList;
};
