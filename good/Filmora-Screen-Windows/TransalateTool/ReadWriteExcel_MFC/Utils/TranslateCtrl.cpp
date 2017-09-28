#include "stdafx.h"
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <algorithm>  
#include "Utils\FileFinderHelper.h"
#include "Utils\StringUtils.h"
#include "Utils\XMLUtil.h"
#include "tinyxml2.h"
#include "Resource.h"
#include "TranslateCtrl.h"
#include "MyProgressCtrl.h"
#include "Utils\ExcelUtil.h"
#include "InfoDiaglog.h"
#include "Cache.h"



using namespace std;
using namespace tinyxml2;
#pragma comment(lib,"tinyxml2.lib")



CTranslateCtrl::CTranslateCtrl(CWnd* pParentWnd) :m_pParentWnd(pParentWnd)
{
	InitData();
}

CTranslateCtrl::~CTranslateCtrl()
{
}

void CTranslateCtrl::DoTranslate(std::wstring strExcelFilePath, std::wstring strProjectPath, std::wstring strTranslateFilter)
{
	//��ԭ����
	RestoreParams();
	//��ȡ��ǰ·���µ�����excel�ļ�����
	string strExcelPath;
	CStringUtils::WStringToString(strExcelFilePath, strExcelPath);
	ReadAllExcelFile(strExcelFilePath);
	//��ȡts�ļ������Ϣ
	vector<string> m_AllTsFile;
	CFileFinderHelper::find(strProjectPath.c_str(), m_AllTsFile, L".ts");
	vector<string>::iterator iter = m_AllTsFile.begin();
	if (m_AllTsFile.size() == 0)
	{
		AfxMessageBox(L"�ף���ǰ����Ŀ¼��û���ҵ��������ts�ļ�");
		return;
	}
	progress->ShowWindow(SW_SHOW);
	for (; iter != m_AllTsFile.end(); ++iter)
	{
		iter - m_AllTsFile.begin();
		int iSize = (int)floor(((float)(iter - m_AllTsFile.begin() + 1) / (float)m_AllTsFile.size()) * 100.00);
		progress->SetPos(iSize);
		m_CurrentHandleTsFile = CStringUtils::getFileName(*iter).c_str();
		string  strLangugeType = CStringUtils::getFileName(*iter).c_str();
		m_CurrentHandleTsPath = (*iter).c_str();
		bool bIsFilter = FilterTranslateFile(strLangugeType, strTranslateFilter);
		if (bIsFilter)
		{
			continue;
		}
#ifdef _DEBUG
		//MessageBox(m_FilterValue);
#endif	
		TranslateSingleFile(*iter);
	}
	//������ɺ����ؽ������ؼ�
	Sleep(1000);
	progress->ShowWindow(SW_HIDE);
	SaveUnMatchFile();
	ReportTranslateResult();
}

bool CTranslateCtrl::FilterTranslateFile(const string &strLangugeType, const std::wstring &strTranslateFilter)
{
	bool bIsFilter = false;
	string strLangugeTypeTmp = strLangugeType;
	int iIndexUnderline = strLangugeTypeTmp.find_last_of("_");
	int iDotPos = strLangugeTypeTmp.find_last_of(".");
	strLangugeTypeTmp = strLangugeTypeTmp.substr(iIndexUnderline + 1, iDotPos - iIndexUnderline - 1);
	CString strTmp(strLangugeTypeTmp.c_str());
	if (!strTranslateFilter.empty() && strTmp.CompareNoCase(strTranslateFilter.c_str()) != 0)
	{
		bIsFilter = true;
	}
	//����ƥ�䲻��excel�ļ����͵�ts�ļ�
	list<CString>::iterator Listiter = m_ReplaceList.begin();
	bool bIsFindkey = false;
	for (; Listiter != m_ReplaceList.end(); ++Listiter)
	{
		if ((*Listiter).CompareNoCase(strTmp) == 0)
		{
			bIsFindkey = true;
		}
	}
	if (!bIsFindkey)
	{
		bIsFilter = true;
	}
	return bIsFilter;
}

void CTranslateCtrl::TranslateSingleFile(string  strFilePath)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	tinyxml2::XMLError error = doc->LoadFile(strFilePath.c_str());
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
						if (strtext.compare("unfinished") != 0)
						{
							bIsTraslated = true;
							if (strtext.compare("vanished") == 0)
							{
								//������Ϣ���ı�
								//�ҵ���ǰ�ڵ�ĸ��ڵ�
								XMLElement* parentElement = (XMLElement*)translateElement->Parent();
								XMLElement* childElement = NULL;
								bool bIsGetChild = CXMLUtil::GetNodePointerByName(parentElement, string("source"), childElement);
								if (childElement != NULL)
								{
									string strCurText = (childElement->GetText() != NULL) ? childElement->GetText() : "";
									m_AllVanishTexts.insert(make_pair(strCurText, strFilePath));
								}
							}
						}
					}
				}
				//�ж��Ƿ�������Ҫ��ǿ���滻
				if (!bIsForcedReplace && bIsTraslated)
				{
					firstEle = firstEle->NextSibling();
					continue;
					//������ǰ��Ҫ������ı�
				}
				while (child != NULL)
				{
					if (string(child->Name()) == "source")
					{
						strRawText = (child->GetText() != NULL) ? child->GetText() : "";
						wstring strFileType = m_CurrentHandleTsFile.GetBuffer();
						string strFileTypeTmp;
						CStringUtils::WStringToString(strFileType, strFileTypeTmp);
						string strSuffix = getTsFileType(strFileTypeTmp);//
						CStringUtils::trim(strRawText);
						CStringUtils::trim(strSuffix);
						strTraslateText = TraslateRawData(strRawText, strSuffix);
					}
					if (string(child->Name()) == "translation" && !strTraslateText.empty())
					{
						child->SetText(strTraslateText.c_str());
						//����ɹ�������״̬Ϊ�Ѿ������״̬
						child->SetAttribute("type", "finished");
						//TODO:�������Լ�����-- �������ŵļ�⣩
					}
					else if (string(child->Name()) == "translation" && strTraslateText.empty())
					{
						string strCurTranslat = (child->GetText() != NULL) ? child->GetText() : "";
						if (strCurTranslat.empty())
						{
							child->SetAttribute("type", "unfinished");
							//��û�гɹ�ʵ�ַ�����ı�����¼
							m_UnFinishStateTexts.insert(make_pair(strRawText, strFilePath));
						}
					}
					child = child->NextSiblingElement();
				}
			}
			firstEle = firstEle->NextSibling();
		}
		ele = ele->NextSiblingElement("context");
	}
	//�޸���ɺ���н��޸ı���
	doc->SaveFile(strFilePath.c_str());
}

void CTranslateCtrl::InitData()
{
	progress = new CMyProgressCtrl();
	progress->Create(WS_VISIBLE | WS_CHILD, CRect(165, 250, 355, 265), m_pParentWnd, 99);
	progress->SetRange(0, 100);
	progress->ShowWindow(SW_HIDE);
	m_ExcelHelper = new CExcelUtil();
}

std::string CTranslateCtrl::getTsFileType(std::string strFileName)
{
	int iUnderlineIndex = strFileName.find_last_of("_");
	int iDotIndex = strFileName.find_last_of(".");
	string strFileType;
	strFileType = strFileName.substr(iUnderlineIndex + 1, iDotIndex - iUnderlineIndex - 1);
	return strFileType;
}

std::string CTranslateCtrl::TraslateRawData(string strRawData, string strType)
{
	//ͳһת����Сд
	//return "$$$$$$$$$$$$$$$$$$$$$$";
	transform(strType.begin(), strType.end(), strType.begin(), ::tolower);
	CString cstrRawData(strRawData.c_str());
	wstring wstrRect;
	string  strRect;
	CStringUtils::trim(strType);
	map<CString, CString>  result = m_AllLanguageMap[strType];
	CString strInfo = cstrRawData;
	strInfo.Compare(L"Zoom in/out preview window");
	strInfo.Append(L"%%%%%%%%%");
	string watrInfo;
	CStringUtils::WStringToString(strInfo.GetString(), watrInfo);
	//TRACE("king*************is:%s\n", watrInfo.c_str());
	cstrRawData = cstrRawData.Trim();
	string watrInfoData;
	CStringUtils::WStringToString(cstrRawData.GetString(), watrInfoData);
	//TRACE("king*************is:%s\n", watrInfoData.c_str());
	CString strText = result[cstrRawData];
	//*********************test ********************************************
	CString strTranslate = m_AllLanguageMap[strType][cstrRawData];
	//TRACE(L"king*************is:%s\n", strTranslate);
	wstrRect = m_AllLanguageMap[strType][cstrRawData].GetString();
	if (wstrRect.empty())
	{
		m_UnMatchMap.insert(make_pair(cstrRawData, m_CurrentHandleTsFile));
		return strRect;
	}
	else
	{
		//������ҵ���Ӧ���룬���ʵ丱���ж�����ɾ��
		m_ExtraExcelTexts[strType].erase(cstrRawData);
	}
	//TRACE(L"king*************is:%s\n", wstrRect.c_str());
	//wstrRect = m_TranslateMap[cstrRawData].GetString();

	//strRect = ws2s(wstrRect);
	CStringUtils::WStringToString(wstrRect, strRect);
	strRect = CStringUtils::UnicodeToUtf8(wstrRect.c_str());
	//string_To_UTF8(strRect);
	return strRect;
}

void CTranslateCtrl::ReadAllExcelFile(wstring strExcelFilePath)
{
	string strSourceFilePath;
	CStringUtils::WStringToString(strExcelFilePath, strSourceFilePath);
	CFileFinderHelper::GetAllFormatFiles(strSourceFilePath, m_AllExcelFile, ".xlsx");
	vector<string>::iterator iter = m_AllExcelFile.begin();
	for (; iter != m_AllExcelFile.end(); ++iter)
	{
		map<CString, CString> resultMap;
		m_ExcelHelper->ReadExcelFile(*iter, resultMap);
		string strLanguageType = (*iter);
		strLanguageType = GetTranslateFileLanguage(strLanguageType);
		m_AllLanguageMap.insert(make_pair(strLanguageType, resultMap));
		wstring wstrLanguageType;
		CStringUtils::StringToWString(strLanguageType, wstrLanguageType);
		m_ReplaceList.push_back(wstrLanguageType.c_str());
	}
	//����ǰ�������
	m_ExtraExcelTexts = m_AllLanguageMap;
}

string CTranslateCtrl::GetTranslateFileLanguage(string strLanguageType)
{
	string strResult;
	int iIndex = strLanguageType.find_last_of("\\");
	strLanguageType = strLanguageType.substr(iIndex + 1);
	iIndex = strLanguageType.find_last_of("_");
	int iLastIndex = strLanguageType.find_last_of(".");
	strLanguageType = strLanguageType.substr(iIndex + 1, iLastIndex - iIndex - 1);
	transform(strLanguageType.begin(), strLanguageType.end(), strLanguageType.begin(), ::tolower);
	CStringUtils::trim(strLanguageType);
	strResult = strLanguageType;
	return strResult;
}


void CTranslateCtrl::SaveUnMatchFile()
{
	wchar_t chpath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, (LPWSTR)chpath, sizeof(chpath));
	m_UnMatchTextFilePath = chpath;
	int iIndex = m_UnMatchTextFilePath.find_last_of(L"\\");
	m_UnMatchTextFilePath = m_UnMatchTextFilePath.substr(0, iIndex);
	m_UnMatchTextFilePath.append(L"\\UnTranslateText.txt");

	multimap<string, string>::iterator iter = m_UnFinishStateTexts.begin();
	ofstream out(m_UnMatchTextFilePath);
	//д�뵱ǰû�гɹ�������ı�
	out << "******************************  UnFinished Text ***************************************" << endl;
	out << "UnFinished Text Number:   " << m_UnFinishStateTexts.size() << endl;
	out << endl;
	if (out.is_open())
	{
		for (; iter != m_UnFinishStateTexts.end(); ++iter)
		{
			out << (iter->first).c_str() << "   ***   " << (iter->second).c_str() << endl;
		}
	}

	out << endl;
	out << "******************************  Excel Extra Text ***************************************" << endl;	
	if (out.is_open())
	{
		map<std::string, map<CString, CString>>::iterator iterExtra = m_ExtraExcelTexts.begin();
		for (; iterExtra != m_ExtraExcelTexts.end(); ++iterExtra)
		{
			//�����ǰ����
			out << "Current Translate Language:  "  <<(iterExtra->first).c_str() << endl;
			map<CString, CString> innerMap = iterExtra->second;
			map<CString, CString>::iterator iterInner = innerMap.begin();
			out << "Excel Extra Text Number: " << innerMap.size() << endl<<endl;
			for (; iterInner != innerMap.end(); ++iterInner)
			{
				wstring strValueTmp = (iterInner->second);
				string strTranslateValue;
				CStringUtils::WStringToString(strValueTmp, strTranslateValue);

				wstring strkeyTmp = (iterInner->first);
				string strTranslateKey;
				CStringUtils::WStringToString(strkeyTmp, strTranslateKey);
				out << strTranslateKey.c_str() << "   ***   " << strTranslateValue.c_str() << endl;
			}
		}
	}

	out << endl;
	out << "****************************** Vanish Text    ***************************************" << endl;
	out << "Vanish Text Number:   " << m_AllVanishTexts.size() << endl<<endl;
	if (out.is_open())
	{
		multimap<string, string>::iterator iterVanish = m_AllVanishTexts.begin();
		for (; iterVanish != m_AllVanishTexts.end(); ++iterVanish)
		{
			out << (iterVanish->first).c_str() << "   ***   " << (iterVanish->second).c_str() << endl;
		}
	}
	out.close();
}

void CTranslateCtrl::ReportTranslateResult()
{
	int iCount = m_UnFinishStateTexts.size();
	wchar_t strInfo[255] = { 0 };
	wsprintf(strInfo, L"Translate finish, total %d string not found in the excel file.", iCount);
	CString strInfoText = strInfo;
	//��ʾ�û����
	CInfoDiaglog *dlg = new CInfoDiaglog(m_pParentWnd);
	dlg->Create(IDD_INFO_DIAOG);
	CString strUnMatchTextFilePath = m_UnMatchTextFilePath.c_str();
	HWND hWnd = FindWindow(NULL, _T("Info"));
	::SendMessage(
		hWnd            //FindWInd(NULL,_T(***))ͨ�����������ش��ڵľ��ָ��
		, WM_UNMATCH_TEXT
		, (WPARAM)&strInfoText
		, (LPARAM)&strUnMatchTextFilePath);//��Ϣ�ĵ�ַ
	dlg->ShowWindow(SW_NORMAL);
}

void CTranslateCtrl::RestoreParams()
{
	m_UnMatchMap.clear();
	m_AllExcelFile.clear();
	m_ReplaceList.clear();
	m_AllLanguageMap.clear();
	m_ExtraExcelTexts.clear();
	m_UnFinishStateTexts.clear();
	m_AllVanishTexts.clear();
}

void CTranslateCtrl::GetExcelExtraData()
{

}
