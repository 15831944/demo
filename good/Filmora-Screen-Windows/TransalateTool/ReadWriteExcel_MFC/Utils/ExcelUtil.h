#pragma once
#include ".\excelReader\Application.h"
#include ".\excelReader\Workbooks.h"
#include ".\excelReader\Workbook.h"
#include ".\excelReader\Worksheets.h"
#include ".\excelReader\Worksheet.h"
#include ".\excelReader\Range.h"
#include <string>
#include <map>

using namespace std;

//��Ԫ���ʽ��Ϣ
typedef struct tagCellFormatInfo
{
	DWORD  m_TextColor;   //���ֵ���ɫ
	string m_FontName;    //��������
	string m_FontStyle;   //������ʽ
	int    m_FontSize;    //�����С
	tagCellFormatInfo(DWORD dTextColor, string strFontName, string strFontStyle, int iFontSize)
	{
		m_TextColor = dTextColor;
		m_FontName = strFontName;
		m_FontStyle = strFontStyle;
		m_FontSize = iFontSize;
	}
}CellFormatInfo, *pCellFormatInfo;

class CExcelUtil
{
public:
	CExcelUtil();
	~CExcelUtil();

public:
//**********************�� д Excel ����*************************************  
    /*
    *  ���ܣ���ȡexcel��ǰ���е����ݣ������map�ṹ 
    /*  string strFilePath: excel �ļ����ڵ�·��
    */         
	void ReadExcelFile(string strFilePath, map<CString, CString>& resultMap);
    //���ض�λ��д���ض����ı���Ϣ
	void WriteExcelCell(CString strCellPos, CString strValue, pCellFormatInfo pTextFormat = nullptr);
	//���ض���������д�ı���Ϣ
	void WriteExcelRangeCell(CString strStartCellPos, CString strEndCellpos, void ** pDataArray, pCellFormatInfo pTextFormat = nullptr);



//**********************������EXCEL*******************************************  
	//����App����
	BOOL CreateApp();
	//�������������϶���
	BOOL CreateWorkbooks();
	//��������������
	BOOL CreateWorkbook();
	//������������
	BOOL CreateWorksheets();
	//����һ��������
	BOOL CreateWorksheet(short index);
	
	BOOL CreateSheet(short index);
	//�����µ�EXCELӦ�ó��򲢴���һ���¹������͹�����  
	BOOL Create(short index);
	void ShowApp(); //��ʾEXCEL�ĵ�  
	void HideApp(); //����EXCEL�ĵ�  

//**********************�����ĵ�*********************************************  
	BOOL SaveWorkbook();                   //Excel���Դ���ʽ�����档  
	BOOL SaveWorkbookAs(CString fileName); //Excel�Դ�����ʽ�����档  
	BOOL CloseWorkbook();
	void CloseApp();


private:
	void PreLoadSheet();
	CString GetCell(long iRow, long iColumn);
	int GetColumnCount();
	int GetRowCount();
	void QuitApp();

private:
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
	map<wstring, map<wstring, wstring>> m_TranslateRsult;
};

