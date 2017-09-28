#pragma once
#include <string>
#include <vector>
#include <map>

class CMyProgressCtrl;
class CWnd;
class CExtractorCtrl: public CObject
{
public:
	enum DuplicateFlag
	{
        Flag_None = 0, //�������ظ�
		Flag_Exsit    //�����ظ�
	};
	CExtractorCtrl(CWnd* pParentWnd);
	~CExtractorCtrl();
public:
	void DoExtract(std::wstring strProjectPath, std::wstring strResultPath, std::wstring strFilter);
	vector<string> getTsFileByLanguage(string strLanguageType);
	void SetExtractMode(ExtractType type){ m_CurExtractType = type; };
	void SetIsRemoveDuplicate(bool bIsRemoveDuplicate){ m_IsRemoveDuplicate = bIsRemoveDuplicate; };


private:
	void InitData();
	std::string getTsFileType(wstring strFileName);
	void RestoreParams();//��ԭ����
	void ClearResultFile();
	void ExtractSingleFile(wstring strLanguangeType, wstring strFilePath);
	void DivideTsArray(); //�����е�ts�ļ������������������
	void AddExtractInfo(CString strText); //����ǰ�Ѿ���ȡ����Ϣ����
	bool IsDuplicate(CString strKeyText);
	bool SetCurNodeState(string strNodeText);

private:
	//�ڲ��߼����ַ���ʹ��wstring ����ʹ��
	std::wstring m_ExtractProjectPath;
	std::wstring m_ExtractResultPath;
	std::wstring m_ExtractFilter;

	vector<string> m_AllEnTsFile; //��ǰ��Ŀ�����е�Ӣ�İ汾��ts�ļ�����
	vector<string> m_AllTsFile; //���е�ts�ļ��ļ���
	CMyProgressCtrl* progress;
	ExtractType m_CurExtractType; //��ǰ����ȡ����
	bool  m_bIsFullExtract; //�Ƿ���ȡ���д�������ı�
	CWnd* m_ParentWnd;
	bool m_IsExtracted; //�Ƿ���������ȡ��
	map<wstring,wstring> m_AllResultFileMap;//��ǰ���еķ������ļ����ڵ�λ�ã�key: �������ͣ�value: �ļ����ڵ�·����
	map<wstring, vector<wstring>> m_AllTsFileMap;
	vector<wstring>  m_AllLanguageType;
	map<CString, DuplicateFlag>  m_AllHaveExtractMap; //��ǰ�Ѿ���ȡ���ı�
	bool m_IsRemoveDuplicate; //��ȡ�ı���ʱ���Ƿ�ʹ��ȥ��ģʽ
};

