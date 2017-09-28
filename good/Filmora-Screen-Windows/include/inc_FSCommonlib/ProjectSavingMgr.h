#ifndef PROJECTSAVINGMGR_H
#define PROJECTSAVINGMGR_H

#include "inc_FSCommonlib/fscommonlib_global.h"


#include <QObject>

// Recorder��Editor��ͨ�� �� �Զ�����ͨ������ŵ�����
// ����ȫ������ȷ���Զ������ڼ䣬����ͨ����Ҫ�ȴ�
class FSCOMMONLIB_EXPORT ProjectSavingMgr : public QObject
{
    Q_OBJECT

public:
    static ProjectSavingMgr* GetInstance();
    void Release();

    bool IsSaving();
    void SetSaving(bool saving);

    void WaitFinishSave(int msecs = 0);

public:
    ProjectSavingMgr(QObject *parent);
    ~ProjectSavingMgr();

private:
    QSharedMemory *memory;
    QString m_mutexName;
};

#endif // PROJECTSAVINGMGR_H
