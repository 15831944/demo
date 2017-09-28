#pragma once
#include "stdafx.h"
#include "tinyxml2.h"
#include <string>

typedef void(*pFun)(PVOID pParam);

class CXMLUtil
{
public:
	CXMLUtil();
	~CXMLUtil();

	//��ȡxml�ض��ڵ�Ԫ��
	static bool GetNodePointerByName(tinyxml2::XMLElement* pRootEle, std::string &strNodeName, tinyxml2::XMLElement* &Node);
	//��������xml��  --����������ȱ���
	static bool TravelXMLTree(std::string strXmlPath, pFun func);
    //����xml  --�����ǰxml�Ѿ������������ز���
	bool CreateXML(const char* xmlPath);
	//����½ڵ�(�ڸ��ڵ�������µ��ӽڵ�)
	tinyxml2::XMLNode* InsertNode(const char* elementName);
    //���ض��Ľڵ�����ӽڵ�
	tinyxml2::XMLNode* InsertRightNode(tinyxml2::XMLElement* parentElement, const char* elementName);

	tinyxml2::XMLNode* InsertLeftNode(tinyxml2::XMLElement* parentElement, const char* elementName);

	//��ѯ�ڵ���Ϣ-- ���ݽڵ���������Ʋ�ѯ���Զ�Ӧ��ֵ
	std::string QueryNodeInfo(const char* nodeName,const char* attributeName);
	//�޸Ľڵ���Ϣ
	bool UpdatePathData(const char* xmlPath, const char* newElementValue);
	//ɾ���ض��ڵ����Ϣ��������µ��ӽڵ㣩
	bool DeleteNodeInfo(const char* nodeName);
	//ɾ���ض��ڵ����Ϣ���Ǹ�����µ��ӽڵ㣩
	bool DeleteNodeInfo(tinyxml2::XMLElement* parentElement, const char* nodeName);
	//����������ļ����޸�
	void SaveFile(const char* strFilepath = "");
	//ͨ���ڵ����ƹ�ȥ��Ӧ��Ԫ��(--��ȡһ���ڵ�)
	bool GetNodePointerByName(std::string &strNodeName, tinyxml2::XMLElement* &Node);

private:
	tinyxml2::XMLDocument m_doc; //��ǰ���ص�xml�ĵ�
	tinyxml2::XMLElement* m_RootElement; //�ĵ��ĸ��ڵ�Ԫ��

	tinyxml2::XMLElement* m_RootNode;//�����ڵ�
	const char* m_xmlPath;
};

