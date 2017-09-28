#include "stdafx.h"
#include <fstream>
#include <ostream>
#include <fstream>  
#include <iostream>  
#include <Windows.h>  
#include <io.h>  
#include <locale>
#include "tinyxml2.h"
#include "Utils/StringUtils.h"
#include "Utils/XMLUtil.h"
#include "Resource.h"
#include "ExtractorCtrl.h"
#include "Utils\FileFinderHelper.h"
#include "MyProgressCtrl.h"
#include "Utils/ExcelUtil.h"

using namespace std;
using namespace tinyxml2;
#pragma comment(lib,"tinyxml2.lib")

#ifdef  DEBUG
#define EXTRACT_WITH_FILENAME true   //�Ƿ���ģ����ȡ��Ĭ���ǲ���ȡģ���������ڵ����ã�
#else
#define EXTRACT_WITH_FILENAME false 
#endif

#define SUFFIX_NAME L".xlsx"

//ostream &operator << (ostream &os, const wchar_t *wstr)
//{
//	// ��ʱwstr��UTF-16����  
//	// ����ת��ΪUTF-8�����д���ļ�  
//	int n = WideCharToMultiByte(CP_UTF8, NULL, wstr, -1, NULL, NULL, NULL, NULL);
//	char *p = new char[n];
//	WideCharToMultiByte(CP_UTF8, NULL, wstr, -1, p, n, NULL, NULL);
//	os.write(p, n - 1);
//	delete[] p;
//	return os;
//}
//
//ostream &operator << (ostream &os, wstring &ws)
//{
//	os << ws.c_str();
//	return os;
//}


CExtractorCtrl::CExtractorCtrl(CWnd* pParentWnd) :m_ParentWnd(pParentWnd)
{
	InitData();
}

CExtractorCtrl::~CExtractorCtrl()
{
}

void CExtractorCtrl::ExtractSingleFile(wstring strLanguangeType, wstring strFilePath)
{
	CString strExcelpath = m_ExtractResultPath.c_str();
	strExcelpath.Append(L"\\ExtractResult_");
	strExcelpath.Append(strLanguangeType.c_str());
	strExcelpath = strExcelpath.Trim();
	strExcelpath.Append(SUFFIX_NAME);
	if (m_AllResultFileMap.find(strLanguangeType) == m_AllResultFileMap.end())
	{
		m_AllResultFileMap.insert(make_pair(strLanguangeType, strExcelpath.GetBuffer()));
	}
	CExcelUtil resultExcel; //��ǰ��ȡ�������ɵ��ļ�
	resultExcel.Create(1); 
	int iCurCellLineNum = 0;
	//��ȡ��ǰ������������ts�ļ�
	vector<wstring>allFileInfo;
	map<wstring, vector<wstring>>::iterator iterMap = m_AllTsFileMap.find(strLanguangeType);
	if (iterMap != m_AllTsFileMap.end())
	{
		allFileInfo = (*iterMap).second;
	}
	vector<wstring>::iterator iter = allFileInfo.begin();
	//��յ�ǰ�ĵ��ļ���
	m_AllHaveExtractMap.clear();
	for (; iter != allFileInfo.end(); ++iter)
	{
		string strTsFilePath;
		CStringUtils::WStringToString(*iter, strTsFilePath);
		ifstream fileText(strTsFilePath);
		string strAllText((std::istreambuf_iterator<char>(fileText)), std::istreambuf_iterator<char>());
		string FileName = CStringUtils::getFileName(strTsFilePath);
		if (!m_IsRemoveDuplicate)
		{
			wstring wstrFileName;
			CStringUtils::StringToWString(FileName, wstrFileName);
			////����ģʽ�£�������ڵ��ļ�
			//Ԥ��һ�����ո�
			iCurCellLineNum+=2;
			CString strFileNameTmp(wstrFileName.c_str());
			CString strRawPos;
			strRawPos.Format(L"%s%d", L"A", iCurCellLineNum);
			pCellFormatInfo pCellFomat = new tagCellFormatInfo(RGB(255,0,0),"Microsoft YaHei UI","�Ӵ�",12);
			resultExcel.WriteExcelCell(strRawPos, strFileNameTmp, pCellFomat);
		}
		tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
		tinyxml2::XMLError error = doc->LoadFile((strTsFilePath).c_str());
		XMLElement* ele = doc->RootElement();
		if (ele != NULL)
		{
			ele = ele->FirstChildElement("context");
		}
		while (ele != NULL)
		{
			XMLNode* firstEle = ele->FirstChild();
			while (firstEle != NULL)
			{
				string strText = firstEle->ToElement()->Name();
				if (strText == "message")
				{
					XMLElement* child = firstEle->FirstChildElement();
					string strRawText;
					string strTraslateText;
					XMLElement* translateElement = NULL;
					bool bIsTraslated = false;
					bool bIsGetName = CXMLUtil::GetNodePointerByName(firstEle->ToElement(), string("translation"), translateElement);
					if (bIsGetName)
					{
						if (translateElement->FirstAttribute() == NULL)
						{
							//��ǰ������Ѿ����룬�����滻
							if (translateElement->Value() != NULL)
							{
								if (translateElement->GetText() != NULL)
								{
									strTraslateText = translateElement->GetText();
								}
								else
								{
									strTraslateText = "";
								}
								bIsTraslated = true;
							}
							else
							{
								bIsTraslated = false;
							}
						}
						else
						{
							string strtext = translateElement->Attribute("type");
							if (m_CurExtractType != Type_ExtractUnfinished)
							{
								//Ĭ����ȡģʽ
								strTraslateText = (translateElement->GetText() != NULL) ? translateElement->GetText() : "";
								if (strtext.compare("unfinished") != 0 || !strTraslateText.empty())
								{
									bIsTraslated = true;
								}
								else
								{
									strTraslateText = (translateElement->GetText() != NULL) ? translateElement->GetText() : "";
								}
							}
							else
							{
								//��ȡ����״̬����finished���ı�
								strTraslateText = (translateElement->GetText() != NULL) ? translateElement->GetText() : "";
								if (strtext.compare("finished") == 0 || !strTraslateText.empty())
								{
									bIsTraslated = true;
								}
								else
								{
									strTraslateText = (translateElement->GetText() != NULL) ? translateElement->GetText() : "";
								}
							}
						}
					}
					if (bIsTraslated && (m_CurExtractType != Type_ExtractAll))
					{
						firstEle = firstEle->NextSibling();
						continue;
						//������ǰ��Ҫ������ı�
					}
					while (child != NULL)
					{
						if (string(child->Name()) == "source")
						{
							strRawText = child->GetText();
							wstring wstrExtract;
							CStringUtils::StringToWString(strRawText, wstrExtract);
							CString cstrExtract = wstrExtract.c_str();
							cstrExtract = CStringUtils::ReplaceEntitySymbols(cstrExtract);
							strRawText = CStringA(cstrExtract);
							//��ȡ��ǰ�ķ����ı�
							wstring wstrTranslateText;
							wstrTranslateText = CStringUtils::Utf8ToUnicode(strTraslateText.c_str());
							if (IsDuplicate(cstrExtract))
							{
								//����ģʽ
								if (!m_IsRemoveDuplicate)
								{
									iCurCellLineNum++;
									wstring wstrRawText;
									CStringUtils::StringToWString(strRawText, wstrRawText);
									CString strRawTextTmp(wstrRawText.c_str());
									CString strTranslateTextTmp(wstrTranslateText.c_str());
									CString strRawPos, strTranslatePos;
									strRawPos.Format(L"%s%d", L"A", iCurCellLineNum);
									strTranslatePos.Format(L"%s%d", L"B", iCurCellLineNum);

									resultExcel.WriteExcelCell(strRawPos, strRawTextTmp);
									resultExcel.WriteExcelCell(strTranslatePos, strTranslateTextTmp);
								}
							}
							else
							{
								iCurCellLineNum++;
								wstring wstrRawText;
								CStringUtils::StringToWString(strRawText, wstrRawText);
								CString strRawTextTmp(wstrRawText.c_str());
								CString strTranslateTextTmp(wstrTranslateText.c_str());
								CString strRawPos,strTranslatePos;
								strRawPos.Format(L"%s%d", L"A", iCurCellLineNum);
								strTranslatePos.Format(L"%s%d", L"B", iCurCellLineNum);

								resultExcel.WriteExcelCell(strRawPos, strRawTextTmp);
								resultExcel.WriteExcelCell(strTranslatePos, strTranslateTextTmp);
							}
							AddExtractInfo(cstrExtract);
						}
						child = child->NextSiblingElement();
					}
				}
				firstEle = firstEle->NextSibling();
			}
			ele = ele->NextSiblingElement("context");
		}
	}
	resultExcel.SaveWorkbookAs(strExcelpath);
	resultExcel.CloseApp();
}

void CExtractorCtrl::DivideTsArray()
{
	vector<string>::iterator iter = m_AllTsFile.begin();
	string srtCurLanguage;
	wstring wstrCurLanguage;
	for (; iter != m_AllTsFile.end(); ++iter)
	{
		wstring wstrCurFilePath;
		CStringUtils::StringToWString((*iter), wstrCurFilePath);
		srtCurLanguage = CFileFinderHelper::getFileType(wstrCurFilePath);
		CStringUtils::StringToWString(srtCurLanguage, wstrCurLanguage);
		wstrCurLanguage = CStringUtils::trim(wstrCurLanguage);
		map<wstring, vector<wstring>>::iterator iterMap = m_AllTsFileMap.find(wstrCurLanguage);
		if (iterMap == m_AllTsFileMap.end())
		{
			vector<wstring> Fileinfo;
			Fileinfo.push_back(wstrCurFilePath);
			m_AllTsFileMap.insert(make_pair(wstrCurLanguage, Fileinfo));
		}
		else
		{
			(*iterMap).second.push_back(wstrCurFilePath);
		}

		if (find(m_AllLanguageType.begin(), m_AllLanguageType.end(), wstrCurLanguage) == m_AllLanguageType.end())
		{
			m_AllLanguageType.push_back(wstrCurLanguage);
		}
	}
}

void CExtractorCtrl::AddExtractInfo(CString strText)
{
		m_AllHaveExtractMap.insert(make_pair(strText, Flag_Exsit));
}

bool CExtractorCtrl::IsDuplicate(CString strKeyText)
{
	if (m_AllHaveExtractMap.empty())
	{
		return false;
	}
	map<CString, DuplicateFlag>::iterator iter = m_AllHaveExtractMap.end();
	if (m_AllHaveExtractMap.find(strKeyText) != iter)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CExtractorCtrl::SetCurNodeState(string strNodeText)
{
	if (m_CurExtractType != Type_ExtractUnfinished)
	{
		if (strNodeText.compare("unfinished") != 0)
		{
			return true;
		}
	}
	else
	{
		if (strNodeText.compare("finished") == 0)
		{
			return true;
		}
	}
	return false;
}

void CExtractorCtrl::DoExtract(std::wstring strProjectPath, std::wstring strResultPath, std::wstring strFilter)
{
	//��ԭ����
	m_ExtractResultPath = strResultPath;
	m_ExtractProjectPath = strProjectPath;
	m_ExtractFilter = strFilter;
	RestoreParams();
	CFileFinderHelper::find(strProjectPath.c_str(), m_AllTsFile, L".ts");
	string strFilterTmp;
	CStringUtils::WStringToString(strFilter, strFilterTmp);
	vector<wstring> CurFileInfo;
	//��ts�ļ��������
	DivideTsArray();
	if (strFilter.empty())
	{
		m_AllEnTsFile = m_AllTsFile;
		CurFileInfo = m_AllLanguageType;
	}
	else
	{
		CurFileInfo.push_back(strFilter);
		m_AllEnTsFile = getTsFileByLanguage(strFilterTmp);

	}
	//����ts�ļ�����ȡ����
	vector<wstring>::iterator iter = CurFileInfo.begin();
	//ʹ�ý�������ʾ����
	progress->SetPos(0);
	progress->ShowWindow(SW_SHOW);
	// ����xml����ȡ
	for (; iter != CurFileInfo.end(); ++iter)
	{
		//�����ļ�������
		int iCurPos = iter - CurFileInfo.begin();
		float fPos = (float)iCurPos / (float)CurFileInfo.size();
		string strFileType = CFileFinderHelper::getFileType(*iter);
		wstring wstrFileType;
		CStringUtils::StringToWString(strFileType, wstrFileType);
		wstrFileType = CStringUtils::trim(wstrFileType);
		ExtractSingleFile(wstrFileType, *iter);
		int iVlaue = (int)floor(fPos * 100);
		progress->SetPos(iVlaue);
	}
	progress->ShowWindow(SW_HIDE);
	MessageBox(NULL, L"Extract finish", L"Info", MB_OK);
	m_IsExtracted = true;
}

vector<string> CExtractorCtrl::getTsFileByLanguage(string strLanguageType)
{
	vector<string> resultRect;
	vector<string>::iterator iter = m_AllTsFile.begin();
	string strFileName;
	for (; iter != m_AllTsFile.end(); ++iter)
	{
		strFileName = CStringUtils::getFileName(*iter);
		wstring wstrFileName;
		CStringUtils::StringToWString(strFileName, wstrFileName);
		string strFileType;
		strFileType = getTsFileType(wstrFileName);
		strFileType = CStringUtils::trim(strFileType);
		strLanguageType = CStringUtils::trim(strLanguageType);
		if (strFileType.compare(strLanguageType) == 0)
		{
			resultRect.push_back(*iter);
		}
	}
	return resultRect;
}

void CExtractorCtrl::InitData()
{
	//CWnd* pParentWnd = CWnd::GetDlgItem(IDD_EXTRACTORVIEW);
	progress = new CMyProgressCtrl();
	progress->Create(WS_VISIBLE | WS_CHILD, CRect(165, 250, 355, 265), m_ParentWnd, 99);
	progress->SetRange(0, 100);
	progress->SetPos(0);
	progress->ShowWindow(SW_HIDE);
	m_bIsFullExtract = false;
	m_IsExtracted = false;
}

std::string CExtractorCtrl::getTsFileType(wstring strFileName)
{
	int iUnderlineIndex = strFileName.find_last_of(L"_");
	int iDotIndex = strFileName.find_last_of(L".");
	wstring strFileType;
	strFileType = strFileName.substr(iUnderlineIndex + 1, iDotIndex - iUnderlineIndex - 1);
	string strRec;
	CStringUtils::WStringToString(strFileType, strRec);
	return strRec;
}

void CExtractorCtrl::RestoreParams()
{
	m_AllTsFile.clear();
	m_AllEnTsFile.clear();
	m_AllLanguageType.clear();
	m_AllTsFileMap.clear();
}

void CExtractorCtrl::ClearResultFile()
{
	if (m_AllResultFileMap.size() > 0)
	{
		map<wstring, wstring>::iterator iter = m_AllResultFileMap.begin();
		wstring strFilePath = (*iter).second;
		int iIndex = strFilePath.find_last_of(L"\\");
		strFilePath = strFilePath.substr(0, iIndex);
		if (strFilePath.compare(m_ExtractResultPath) == 0)
		{
			//�����ǰ�Ľ��·��û�иı䣬��������еĽ���ļ�
			for (; iter != m_AllResultFileMap.end(); ++iter)
			{
				ofstream oFile;
				oFile.open((*iter).second, ios_base::out | ios_base::trunc);
				oFile << "";
				oFile.close();
			}
		}
		else
		{
			m_AllResultFileMap.clear();
		}
	}
}
