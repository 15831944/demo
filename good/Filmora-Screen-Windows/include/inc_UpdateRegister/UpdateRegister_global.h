#ifndef UPDATEREGISTER_GLOBAL_H
#define UPDATEREGISTER_GLOBAL_H

#ifdef WIN32

#ifdef UPDATEREGISTER_LIB
#define UPDATEREGISTER_EXPORT __declspec(dllexport)
#else
#define UPDATEREGISTER_EXPORT __declspec(dllimport)
#endif

#else
#define UPDATEREGISTER_EXPORT  
#endif


class UPDATEREGISTER_EXPORT UpdateRegisterInit
{
public:
	//���������ļ�������Ŀ¼��ֻ��ָ��Ŀ¼����ָ�������ļ���
	static void SetConfigFileDir(QString dir);
	static QString GetConfigFileDir();
	static QString gGetStyleSheet(QString path);
};


#endif // UPDATEREGISTER_GLOBAL_H
