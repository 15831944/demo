#include "stdafx.h"
#include "TUATracker.h"
#include "..\GoogleAnalyze\UniversalAnalytics.h"
#include <QDebug>
#include <tchar.h>

#pragma  comment(lib,"UniversalAnalytics.lib")
const char* strAppName = "FimoraScreen";         //app 名称
const char*  strTrackingId = "UA-100550138-1";   //GA TrackerId
//const char*  strTrackingId = "UA-101101396-1";
char*  cClientId = "0";                         //标记用户的Id参数

//初始化静态成员
TUATracker* TUATracker::m_pInstance = nullptr;
QMutex TUATracker::m_Mutex;
TUATracker::~TUATracker()
{
	ua_destroy_tracker(m_Tracker);
}

void TUATracker::createTracker(const char* tracking_id, const char* client_id, const char* app_name)
{
	m_Tracker = ua_create_tracker(tracking_id, client_id, app_name);
}

void TUATracker::setAppVerion(QString strVersion)
{
	std::string strVersionTmp = strVersion.toStdString();
	ua_tracker_set_app_ver(m_Tracker, strVersionTmp.c_str());
}

void TUATracker::SetLanguageAndLocate(QString strInput)
{
	std::string strInputTmp = strInput.toStdString();
	ua_tracker_set_language(m_Tracker, strInputTmp.c_str());
}

void  TUATracker::SetViewSize(int iWidth, int iHeight)
{
	ua_tracker_set_viewport_size(m_Tracker, iWidth, iHeight);
}

void TUATracker::SetDimension(int iIndex, QString strValue)
{
	std::string strValueTmp = strValue.toStdString();
	ua_tracker_set_custom_dimension(m_Tracker, iIndex, strValueTmp.c_str());
}

void TUATracker::SetMetric(int iIndex, int iValue)
{
	ua_tracker_set_custom_metric(m_Tracker, iIndex, iValue);
}

void TUATracker::SendEvent(QString  strCategory, QString strAction, QString strLabel, int iValue)
{
	std::string strCategoryTmp = strCategory.toStdString();
	std::string strAcionTmp = strAction.toStdString();
	std::string strLabelTmp = strLabel.toStdString();
	ua_hit event_hit = ua_create_event_hit(strCategoryTmp.c_str(), strAcionTmp.c_str(), strLabelTmp.c_str(), iValue);
	ua_send_hit(m_Tracker, event_hit);
	ua_destroy_hit(event_hit);
}

void TUATracker::SendScreenName(QString strName)
{
	std::string strNameTmp = strName.toStdString();
	ua_hit screenview_hit = ua_create_screenview_hit(strNameTmp.c_str());
	ua_send_hit(m_Tracker, screenview_hit);
	ua_destroy_hit(screenview_hit);
}

void TUATracker::SendAppSpeed(QString  strCategory, QString strVariable, int iValue, QString strLable)
{
	std::string strCategoryTmp = strCategory.toStdString();
	std::string strVariableTmp = strVariable.toStdString();
	std::string strLabelTmp = strLable.toStdString();
	ua_hit timeHit = ua_create_timing_hit(strCategoryTmp.c_str(), strVariableTmp.c_str(), iValue, strLabelTmp.c_str());
	ua_send_hit(m_Tracker, timeHit);
	ua_destroy_hit(timeHit);
}

void TUATracker::SendSocialNetWorkInfo(QString strNetWork, QString strAction, QString strTarget)
{
	std::string strNetWorkTmp = strNetWork.toStdString();
	std::string strActionTmp = strAction.toStdString();
	std::string strTargetTmp = strTarget.toStdString();
	ua_hit socialNetWorkHit = ua_create_socialnetwork_hit(strNetWorkTmp.c_str(), strActionTmp.c_str(), strTargetTmp.c_str());
	ua_send_hit(m_Tracker, socialNetWorkHit);
	ua_destroy_hit(socialNetWorkHit);
}

void TUATracker::SendExceptionInfo(QString strDescription, int iFatal)
{
	std::string strDescriptionTmp = strDescription.toStdString();
	ua_hit exceptionHit = ua_create_exception_hit(strDescriptionTmp.c_str(), iFatal);
	ua_send_hit(m_Tracker, exceptionHit);
	ua_destroy_hit(exceptionHit);
}

char* TUATracker::QStr2Char(QString strInput)
{
	std::string str = strInput.toStdString();
	char*  ch = new char[str.length() + 1]();
	memcpy_s(ch, str.length() + 1, str.c_str(), str.length());
	return ch;
}

TUATracker* TUATracker::getInstance()
{
	if (m_pInstance == NULL)
	{   //double check  
		m_Mutex.lock();
		//用lock实现线程安全，用资源管理类，实现异常安全  
		//使用资源管理类，在抛出异常的时候，资源管理类对象会被析构，析构总是发生的无论是因为异常抛出还是语句块结束。  
		if (m_pInstance == NULL)
		{
			m_pInstance = new TUATracker();
		}
		m_Mutex.unlock();
	}
	return m_pInstance;
}

QString TUATracker::getClientId()
{
	HKEY h;
	QString strValue;
	//通过判断特定项是否存在，判断系统位数
	int iRec = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Wow6432Node\\Wondershare\\Wondershare Helper Compact", 0, KEY_ALL_ACCESS, &h);
	if (iRec == 0)
	{
		QSettings reg("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Wondershare\\Wondershare Helper Compact", QSettings::NativeFormat);
		strValue = reg.value("ClientSign").toString();
	}
	else
	{
		QSettings reg("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wondershare\\Wondershare Helper Compact", QSettings::NativeFormat);
		strValue = reg.value("ClientSign").toString();
	}
	return strValue;
}

TUATracker::TUATracker()
{
	//获取用户的id
	QString strClientId = getClientId();
	std::string strClientIdTmp = strClientId.toStdString();
	createTracker(strTrackingId, strClientIdTmp.c_str(), strAppName);
}
