#include "stdafx.h"
#include "inc_FSCommonlib/CBSUrlReader.h"
#include "inc_CommonLib/PathOperation.h"

CBSUrlReader::CBSUrlReader(QObject *parent)
	: QObject(parent)
	, m_LibModual(0)
{
	Init();
}

CBSUrlReader::~CBSUrlReader()
{
	FreeLibrary(m_LibModual);
}

QString CBSUrlReader::ReadCustomerUrl(const QString &langName, const QString &key)
{
	typedef int(__stdcall *ReadInfoFunc)(wchar_t* lpKey, wchar_t* lpLangName, wchar_t* lpValue, int valueLen, wchar_t* lpType, int typeLen);
	ReadInfoFunc func = (ReadInfoFunc)GetProcAddress(m_LibModual, "ReadCustomizeInfoW");
	Q_ASSERT(func);
	if (!func) return "";
	std::wstring wslang = langName.toStdWString();
	std::wstring wskey = key.toStdWString();
	wchar_t value[256] = { L'0' };
	bool bSucc = func((wchar_t*)wskey.c_str(), (wchar_t*)wslang.c_str(), value, 256, 0, 0);
	//Q_ASSERT(bSucc);
	if (!bSucc) return "";
	return QString::fromStdWString(value);
}

bool CBSUrlReader::LoadUtilitiesLib()
{
	if (m_LibModual) return true;
	QString dllpath = PathOperation::MakeWorkPath("WSUtilities.dll");
	std::wstring wspath = dllpath.toStdWString();
	m_LibModual = LoadLibrary(wspath.c_str());
	return m_LibModual != 0;
}


bool CBSUrlReader::LoadXmlFile()
{
	typedef int(__stdcall *LoadXmlFunc)(wchar_t*);
	LoadXmlFunc func = (LoadXmlFunc)GetProcAddress(m_LibModual, "LoadCustomizeXMLFileW");
	Q_ASSERT(func);
	if (!func) return false;
	QString xmlPath = PathOperation::MakeWorkPath("Customization.xml");
	std::wstring wspath = xmlPath.toStdWString();
	return func((wchar_t*)wspath.c_str());
}

void CBSUrlReader::Init()
{
	bool bSucc = LoadUtilitiesLib();
	Q_ASSERT(bSucc);
	bSucc = LoadXmlFile();
	Q_ASSERT(bSucc);
}
