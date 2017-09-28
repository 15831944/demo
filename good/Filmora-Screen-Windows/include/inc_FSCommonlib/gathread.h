#ifndef GATHREAD_H
#define GATHREAD_H

#include "inc_FSCommonlib/fscommonlib_global.h"
#include <QThread>
#include "FSNLETimeline.h"

class GAThread;
class FSNLETimeline;
class TimelineManager;
//ϵͳ��Ϣ�ṹ��
typedef struct
{
	QString strCpuMode;  //cpu�ͺ�
	QString strGpuMode;  //Gpu�ͺ�
	QString strSysRamInfo;//ϵͳ�ڴ��С
	QString strOSBit;     //����ϵͳ��λ��
	QString strSysResolution;//ϵͳ�ֱ���
	QString strSysVersion;  //����ϵͳ�İ汾
	QString strSysLanguage;//ϵͳ����
	QString strProductVersion;//��Ʒ�İ汾��
}*pSysInfo, sysInfo;

//��Ƶ�ļ�����
typedef struct
{
	QString strFileType;      //�ļ�����
	QString strFileFormat;    //�ļ���ʽ
	QString strFileSizeRange; // ��Ƶ�ļ��Ĵ�С
	QString strFileDurationRange;//��Ƶʱ�䳤��
	QString strVedioResolutionRange;//��Ƶ�ֱ���
	QString strVedioCodec;         //��Ƶ������
	QString strVedioFramerate;//��Ƶ֡��
	QString strVedioBitrate; // ��Ƶ�ı�����
}*pVedioInfo, VedioInfo;

//��Ƶ�ļ�����
typedef struct
{
	QString strAudioBitrate;//��Ƶ������
	QString strAudioCodec; //��Ƶ������
	QString strAudioChannel; //��Ƶͨ��
	QString strAudioSampleRate;//��Ƶ��Ʒ��
}*pAudioInfo, AudioInfo;

enum eventType
{
	Sys_Info,       //�ϴ�ϵͳ��Ϣ�¼�
	Start_Up,       //�ϴ�����ҳ������¼�
	Recorder_Device,//�ϴ�¼���豸��Ϣ�¼�
	Recorder_Widget,//�ϴ�¼������Ƶ��Ϣ�¼�
	Your_Clips,     //�ϴ�������clip��Ϣ���¼�
	Import,         //�ϴ����������Ϣ���¼�
	Import_Media,   //�ϴ�����Ķ�ý���ļ�����Ϣ�¼�
	Import_Failed,  //�ϴ�����ʧ����Ϣ�¼�
	Clip_Edit,      //�ϴ��û���Clip�����¼�
	Annotation_Edit,//�ϴ��û���Annotation Edit�����¼�
	Export_Profile, //�ϴ��û���Export Profile �����¼�
	Export_Fail,    //�ϴ��û���Export  Fail �����¼�
	Project_Management, //�ϴ��û���Project  Management�����¼�
	Register,            //�ϴ��û���Register�����¼�
	Buy,                 //�ϴ��û���Buy�����¼�
	Change_Page,        //�û�ҳ���л��¼�
	App_Launch,         //app����ʱ��ͳ��
	VideoEditorLaunchFromStartup,//VideoEditorҳ���л�ʱ��
	ClipsSeekSpeed, //Seekʱ��
	YourClipsLaunchFromStartup,//yourclipsҳ���л�ʱ��
	YourClipsLaunchFromRecorder,//yourclipsҳ���л�ʱ��
	ImportTimer,  //����ʱ������
	ExportTimer, //�����ļ�ʱ������
	RegisterTimer,//ע��ʱ������
	VideoEditorLaunchFromLocalFile, //�ӱ���˫��Editor�����ļ�
	YourClipsLaunchFromLocalFile,  //�ӱ���˫��Recorder�����ļ�
	UserDefineDimension,            //�û��Զ���ά��
	AppStartAndExitCount            //�û��������������˳��������ͳ��
};

//�ϴ������ݽṹ��
typedef struct
{
	eventType eventTypeInfo;//�¼���������Ϣ
	//action ��ֵ,��3�����
	//1������Ǽ�ʱ�����Ǽ�ʱ��������,
	//2: ������л�ҳ��������ҳ�������
	//3�������Event ���Ǿ�����¼�����
	QString strAction;
	QString strLabel;//��ǩ��ֵ������Ǽ�ʱ����ò���ΪNULL
	int iValue;//����Ǽ�ʱ����Ϣ�������������ĺ������������������Ϊ0
}*pGaInfo, gaInfo;

//�����ļ��ָ�����
enum partitionType
{
	EqualType,//�Ⱥŷָ�
	ColonType,//ð�ŷָ�
};

class FSCOMMONLIB_EXPORT GAThread : public QThread
{
	Q_OBJECT

public:
	~GAThread();
public:
	void setCurrentEventType(eventType curType){ m_CurrentEventType = curType; };
	void TransformSysInfo();
	void TransformStartUpInfo();
	void TransformRecorderDeviceInfo();
	void TransFromSpeedInfo();
	//�ϴ��Զ���ά����Ϣ
	void TransfromDimensionInfo();
	//ͨ����ȡ������Ƶʱ�����õ���Ƶ���ڵ�ʱ�䷶Χ
	QString getRecordDurarionRange(int iCounts);
	//��ȡϵͳ������Ϣ
	pSysInfo getSysInfo();
	//���ַ�תխ�ַ�
	BOOL WStringToString(const std::wstring &wstr, std::string &str);
	//��ȡע������ض����ֵ
	std::string  ReadRegValue(wchar_t* wcRegPath, wchar_t* wcRegKey);
	//����ǰ���߳�
	void suspendThread();
	//�ָ��߳�ִ��
	void  resumThread();
	//�ڶ����в���һ���¼���Ϣ��
	void insertEventItem(gaInfo& eventInfo);
	//�����¼���Ϣ��, ������ʽ
	void insertEventItem(eventType eventTypeInfo, QString strAction, QString strLabel= "", int iValue = 0);
	//����Ϊ����ģʽ������ȫ�ֻ�ȡ�̶߳���
	static GAThread* getInstance();
	//��ö���͵ı�����ת�����ַ���
	QString convertEventTypeToString(eventType tyepInfo);
	//������Ƶ�ļ�������
	VedioInfo insertVedioFileInfo(FSNLETimeline *timeline);
	//������Ƶ�ļ���������Ϣ
	AudioInfo insertAudioInfo(FSNLETimeline *timeline);
	//
	QString sGetFourCCString(int fourcc);
	//��ȡͼ��ֱ������ڵķ�Χ
	QString getPicResolutionRange(NLESize picSize);
	//����ClipCount��Ϣ
	void insetClipCountInfo(NLETimeline* timeline);
	//����ClipsCount��Ϣ
	void insetClipCountInfo(TimelineManager*);
	//��ȡ�����ļ��Ĵ�С��Χ
	QString getExportFileRange(qint64 fileSize);
	//��ȡ����ʱ��ķ�Χ ע�⴫���ʱ�䵥λ����
	QString getExportFileDurationRange(qint64 durationRange);
	//��ȡ�����ļ��ķֱ��ʵķ�Χ
	QString getFileResolutionRange(int  iArea);
	//���뵱ǰ��seek������Ϣ
	void insertSeekInfo(int iCurCost){ iTotalSeekCost += iCurCost; iTotalSeekCount++; };
	QString getAverageTime(){ return  QString::number((float)(iTotalSeekCost * 1000) / (float)qMax(1, iTotalSeekCount)); };
	void startTime(){ m_Time.restart(); };
	int getElapse(){return m_Time.elapsed();};
	void setLoadProjectType(bool bType){ m_bIsLoadFromRecorder = bType; };
	bool getLoadProjectType(){ return m_bIsLoadFromRecorder; };
	void increaseSeekCount(){ iTotalSeekCount++; };
	int getSeekCount(){ return iTotalSeekCount; };
	void  setStartRegisterTime(QDateTime time){ m_StartRegTime = time; };
	QDateTime getStartRegisterTime(){ return m_StartRegTime; };
	long long getAppStartTime(){ return m_lAppStartTime; };
	void setAppStartTime(long long time){ m_lAppStartTime = time; };
	QDateTime getAppInstallTime();
	void  setIsStartFromStartup(bool bIsFromStartUp){ bIsStartFromStartUp = bIsFromStartUp; };
	bool getIsStartFromStartUp(){ return bIsStartFromStartUp; };
	//�����߳�
	void start();

protected:
	//�߳�ִ����
	void run();
	std::string getGpuMode();
	std::wstring getSysLanguage();
	std::string getSysRamSize();
	std::string getSysResolution();
	std::string getProductVersion();
	//��ȡ����ϵͳ�İ汾�ţ�����win10��
	std::string getOsVersion();
	//�������ļ���ͨ��keyֵ��ȡ����Ӧ������ֵ
	std::string getConifgByKey(QString strConfigFilePath, QString strKey, partitionType divType = EqualType);
	QString getFileType(TimelineType type);
	//��ȡ�ļ���С��Χ
	QString getFileSizeRange(QString strFilePath);
	//��ȡ��Ƶ�ļ���ʱ�䷶Χ
	QString getFileDurationRange(FSNLETimeline * timeline);
	//��ȡ�ļ��ķֱ��ʷ�Χ
	QString getFileResolutionRange(QSizeF size);
private:
	GAThread(QObject *parent);
	void TranfromPageInfo();
	void TransfromStartAndExitCount();
	bool IsOn();
private:
	eventType m_CurrentEventType; //��ǰ�������¼�����
	QQueue <gaInfo> m_EventList;   //�¼�����
	QMutex m_SyncMutext;//���ڶԶ�����ͬ�����ʵĻ������
	QMutex m_TheadSuspendMutext;//�����߳���ͣ�Ļ������
	gaInfo m_CurrentInfo;//��ǰ�ڵ����Ϣ
	static QMutex m_Mutex;
	static GAThread* m_sGaThread;
	static QWaitCondition m_sWaitCondition;
	int iTotalSeekCost;//��ǰ���е�seek�������ܺ�ʱ
	int iTotalSeekCount;//��ǰseek�������ܵĴ���
	QTime m_Time;//���ڼ�ʱ
	bool m_bIsLoadFromRecorder;//�����ļ��Ƿ��Ǵ�Recorder����
	QDateTime m_StartRegTime;//����ע���ʱ��
	long long m_lAppStartTime;//app ������ʱ��
	QDateTime m_AppInstallTime;//app�İ�װʱ��
	QSettings* m_Setting;
	bool m_bOn;
	bool bIsStartFromStartUp;
};
#endif // GATHREAD_H
