#pragma once
#include <string>
#include <windows.h>
using namespace std;


class CStringUtils
{
public:
	CStringUtils();
	~CStringUtils();

public:
	//�ַ�������
	static BOOL WStringToString(const std::wstring &wstr, std::string &str);
	static BOOL StringToWString(const std::string &str, std::wstring &wstr);
	static string string_To_UTF8(const std::string & str);
	static string trim(string& s);
	static wstring trim(wstring& s);
	static string getFileName(string strFilePath);
	static string ws2s(const std::wstring& wstr);
	static char* UnicodeToUtf8(const wchar_t* unicode);
	//string ת cstring
	static CString stringToCString(string strInput);
	//unicode תutf8
	static const wchar_t* Utf8ToUnicode(const char* utf8Str);
	//��ȡ�ض�����ĳ���
	//static FontFlag getStringSize(CString strText);
	//�Ż����滻ʵ�����
	static CString ReplaceEntitySymbols(CString strText);
	//ȥ���ַ����еĻ��з�
	static wstring RemoveLineBreaks(wstring wstrInput);
};

