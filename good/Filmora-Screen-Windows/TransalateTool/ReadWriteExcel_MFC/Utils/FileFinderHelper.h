#pragma once
#include <string>
#include <vector>

using namespace std;
class CFileFinderHelper
{
public:
	CFileFinderHelper();
	~CFileFinderHelper();

public:
	//�����ض�·���£��ض���ʽ���ļ��ļ���
	static void GetAllFormatFiles(string path, vector<string>& files, string format);
	//��ȡ��ǰ������������е�ts�ļ���������һ���ض����ļ�����
	/*  wchar_t* lpPath                     --��Ҫ���ҵ�·��
    //  std::vector<std::string> &fileList  --��ѯ�Ľ��
	//  wchar_t* strFileType                --���������������ļ����ͣ�.exe .cpp .ts ...��
	*/
	static void find(const wchar_t* lpPath, std::vector<std::string> &fileList, wchar_t* strFileType);
    //�����ļ�����ȡ��Ӧ���ļ����ͣ��ļ���׺��
	static string getFileType(wstring strFileName);

	//��ȡ��ǰ���������ڵ�·��
	static wstring  GetAppPath();
	static bool IsFileExsit(string strFilePath);
};

