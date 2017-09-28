#ifndef COMMUNICATORCLIENT_H
#define COMMUNICATORCLIENT_H

#include <QObject>
#include <QFile>
#include <QTimer>
#include <QStringList>
class CommunicatorClient : public QObject
{
	Q_OBJECT

public:
	static CommunicatorClient* GetInstance();
	void SetEditorView(QWidget *pEditorView);

	void GotoRecorder();
	void SetContentChanged(bool bChanged);
	//bool IsContentChanged();
	bool IsNewProj();
	void Save();
	void SaveNew(QString newProjfile);
    void QuitDontSave();
	void Quit();
	void ClearRecorder();
	void LoadProject(QString projFile);
	void LoadImportPorject(QString projFile);
	void SaveThumbnailFile();

	bool IsSaving();
	void EditorShowed();
	QStringList GetRecentOpens();

	void TellRegisterResult(bool bSucc);

	void Test();
Q_SIGNALS:
	void sigShowEditor();
	void sigHideEditor();
	void sigImportFiles(QStringList files);
	void sigMatterStringLoaded(QString str);
    void sigTimelineStringLoaded(QString str);
    void sigProjectSettingsLoaded(QString str);
    void sigProjectFinishLoaded();
	void sigGetProjectName(QString prjName);
	void sigRegisterResult(bool bSucc);
protected:
    bool SendMsg(const QString msg, bool waitFinishSave = true);
	Q_INVOKABLE void _OnReceiveMsg();
	QString SendMsgWaitForResponse(const QString msg);
private:
	CommunicatorClient(QObject *parent = 0);
	QFile m_Filein;

	QString m_strResponse;
	QWidget *m_pEditorView;

	bool m_bSaving;
};


//����Ԥ���������
class FSEditor;
class ProjPreproccessorClient : public QObject
{
	Q_OBJECT
public:
	static ProjPreproccessorClient* GetInstance();

	void SetEditorView(FSEditor *pEditor);

	void SaveAtClose();
	bool SaveAtMenu();
	bool SaveNewAtMenu();
	void Clear();
	void Load(QString projFile);
	void ImportLoad(const QString projFile);//editor����recorder���̣�����recorder���ļ���editor����������ͣ����editor��

	QStringList GetRecentOpens();
	void SetRecentOpens(QStringList lst);
	QString GetOpenProjFile();
	enum QuestionSavingRes
	{
		QuestionSavingRes_Saved = 0,
		QuestionSavingRes_UserRefuse,
		QuestionSavingRes_UserCancel,
		QuestionSavingRes_UserNoSavePath,
	};
	QuestionSavingRes DoQuestionSaving(); //return: 0���Ա��棬������ʾû�б����ԭ�� 1���û������no 2���û������cancel 3���û����yes����û��ѡ�񱣴�·��

	void SetContentChanged(bool bChanged);
	bool IsContentChanged();

	void SetNewProject(bool bNew);
	bool IsNewProject();

    QString GetProjectSavePath();
Q_SIGNALS:
	void sigContentChanged();
	void sigIsNewProjectChanged();
protected:
	ProjPreproccessorClient(QObject *parent = 0);

	
private:
	FSEditor* m_pFSEditor;
	bool m_bContentChanged;
	bool m_bNewProject;

	QStringList m_lstRecentOpens;
};


#endif // COMMUNICATORCLIENT_H
