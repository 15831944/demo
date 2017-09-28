#pragma once 
#include <map>
#include <string>

class CWnd;
class CMyProgressCtrl;
class CExcelUtil;
class CCache;
class CTranslateCtrl
{
public:
	CTranslateCtrl(CWnd* pParentWnd);
	~CTranslateCtrl();

public:
	void DoTranslate(std::wstring strExcelFilePath, std::wstring strProjectPath, std::wstring strTranslateFilter);
	void SetReplaceType(bool bType){ bIsForcedReplace = bType; };//�����滻ģʽ


private:
	void InitData();
	std::string getTsFileType(std::string strFileName);
	std::string TraslateRawData(std::string strRawData, std::string strType);
	//��ȡ�ض�·���µ�����ts�ļ�������
	void ReadAllExcelFile(wstring strExcelFilePath);
    //��ȡ�����ļ���Ӧ����������
	std::string GetTranslateFileLanguage(std::string strLanguageType);
	//�����ض���ts�ļ�
	void TranslateSingleFile(string strFilePath);
	//���˲����Ѿ���������ļ�
	bool FilterTranslateFile(const string &strLangugeType, const std::wstring &strTranslateFilter);
	void SaveUnMatchFile();//����û�гɹ��滻���ı�
	void ReportTranslateResult();//�����滻���
	void RestoreParams();//�ٴη����ʱ��ϵͳ������ԭ
	void GetExcelExtraData();//ͳ��Excel�д��ڵ�����ts�ļ��в������ı�

private:
	CWnd* m_pParentWnd;
	CMyProgressCtrl* progress;
	CString m_CurrentHandleTsFile;
	CString m_CurrentHandleTsPath;
	list<CString> m_ReplaceList;   //��ǰ�߱�excel�ļ����������ͼ���
	vector<string> m_AllExcelFile; //���е�excel�ļ��ļ���
	map<std::string, map<CString, CString>> m_AllLanguageMap;
	map<std::string, map<CString, CString>> m_ExtraExcelTexts;//Excel�ĵ������Ts�ļ��ж���ı��ļ���
	multimap<CString, CString> m_UnMatchMap;//δƥ�䵽���ַ������ֵ�
	multimap<string, string> m_UnFinishStateTexts; //��ǰ����״̬����ȷ���ı��ļ���
	multimap<string, string>  m_AllVanishTexts;//ts�д��ڵ����ڴ����б�ɾ�����ַ�������
	bool bIsForcedReplace;
	CExcelUtil* m_ExcelHelper;
	wstring m_UnMatchTextFilePath;
};
