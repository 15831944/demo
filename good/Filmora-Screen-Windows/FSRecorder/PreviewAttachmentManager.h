#ifndef PREVIWATTACHMENTMANAGER_H
#define PREVIWATTACHMENTMANAGER_H

#include <QtCore/QObject>
#include <QtWidgets/QWidget>

class RecorderViewsMgr;
class DashlineWidget;
class RecordPanel;
class PreviewBase;
class PreviwAttachmentManager : public QObject
{
    Q_OBJECT

public:
    static PreviwAttachmentManager* GetInstance();


    void PrimaryScreenSwitchMoveAttachPreviews();

private:
    void StartAttachPreview(PreviewBase *preview, DashlineWidget *dashed, QPoint point);
    void MoveAttachPreview(PreviewBase *preview, DashlineWidget *dashed, QPoint point);
    void EndAttachPreview(PreviewBase *preview, DashlineWidget *dashed);

    void ShowAttachPreview(PreviewBase *preview);

    bool GetPreviewAttach(PreviewBase *preview);
    void SetPreviewAttach(QWidget *preview, bool attach);

protected:
    PreviwAttachmentManager(QObject *parent);

    bool eventFilter(QObject *watcher, QEvent *event);

    bool GetAttack(PreviewBase *preview);
    // ����һ��preivew
    void AttachPreview(PreviewBase *preview);
    // ѭ������/ѭ��ȡ������, 
    //ignorePanelVisible:true����m_pRecordPanel�Ƿ�visible�����������߼�
    void InitPanel(PreviewBase *panel);
    QPoint AdjustPanelInAvailableDesktopRectangle(PreviewBase *preview, QPoint point);
    void AttachPreviews(bool ignoreRecordPanelVisible = false);

    void slotPreviewLock();

    void StartDashedMove(QPoint point);
    void DashedMove(QPoint point);
    void EndDashedMove(QPoint point);


private:
    RecorderViewsMgr *m_recorderViewsMgr;

    RecordPanel *m_pRecordPanel;
    PreviewBase *m_pCameraPreview;
    PreviewBase *m_pGamePreview;
    PreviewBase *m_pAudioPreview;

    //DashlineWidget *m_pCameraDashline;
    //DashlineWidget *m_pGameDashline;
    //DashlineWidget *m_pAudioDashline;

    DashlineWidget *m_pAttachHintDashline;


    QList<std::pair<PreviewBase*, DashlineWidget*>> m_previews;
    bool m_bCamerAttach;
    bool m_bGameAttach;
    bool m_bAudioAttach;

    
    QPoint m_attachPosition;
};


class DashlineWidget :public QWidget
{
    Q_OBJECT
public:
    DashlineWidget(QWidget *parent);

    void SetColor(QColor color);

    void MovePosition(QRect r);
    void MovePosition(QPoint point);
    void HideDashline();
    void ShowDashLine();

protected:
    void paintEvent(QPaintEvent *event);

    QColor m_color;
};


#endif // PREVIWATTACHMENTMANAGER_H
