#ifndef DESKTOPRECTANGLEMGR_H
#define DESKTOPRECTANGLEMGR_H

#include "inc_FSCommonlib/fscommonlib_global.h"
#include <QtCore/QObject>
#include <QtCore/QRect>

// ����¼��ʱ�����͸�����λ�ã�һ������Ϊ¼����������Ϊ��������
// �˴�����Ϊ�߼��϶��������,���������඼�ḱ��
class FSCOMMONLIB_EXPORT DesktopRectangleMgr : public QObject
{
    Q_OBJECT
public:
    static DesktopRectangleMgr* GetInstance();

    //  ����
    QRect PrimaryScreen();
    // ����,����index��С�ĸ���
    QRect SecondScreen();
    // ����������index����
    void SwitchPrimary2Screen(int index);
    bool IsPrimaryScreen();

    // ����index
    int PrimaryScreenIndex();
    int SecondScreenIndex();

    QRect ScreenGeometry(int index);
    QRect ScreenAvailableGeometry(QPoint point);
    QRect ScreenAvailableGeometry(int index);
    int ScreenCount();

    //  ��һ������
    QRect PrePrimaryScreen();
    // ��һ�θ���,����index��С�ĸ���
    QRect PreSecondScreen();

signals:
    void sigPrimaryScreenChanged();

protected:
    DesktopRectangleMgr(QObject *parent);

    void CalSecondScreenIndex();

private:
    QRect m_offsetRect;
    int m_primaryIndex;
    int m_secondIndex;
    int m_prePrimaryIndex;
    int m_preSecondIndex;
    int m_screenType;
};

#endif // DESKTOPRECTANGLEMGR_H
