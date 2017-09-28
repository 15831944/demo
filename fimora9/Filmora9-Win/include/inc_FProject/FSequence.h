#ifndef FSEQUENCE_H
#define FSEQUENCE_H

#include "inc_FProject/FNLETimeline.h"
#include "inc_FProject/FTrack.h"

class FUndoCommand;

class FPROJECT_EXPORT FSequence : public FNLETimeline
{
    Q_OBJECT
public:

    // ��ȡʱ������ʱ��
    int GetDuration();
    // ���õ�ǰ֡
    void SetCurrentFrames(int frames);

    int GetCurrentFrames();

    // ����Ƭ��
    void AddTimeline(int trackIndex, int frames, FNLETimelinePtr timeline);
    // �ƶ�Ƭ��
    void MoveTimeline(int trackIndex, int frames, FNLETimelinePtr timeline);

    FTracks GetTracks();
    // ������
    void InsertTrack(int trackIndex);
    // �Ƴ����
    void RemoveTrack(int index);

    // ɾ��ѡ��Ƭ��
    void RemoveClips();
    bool CanRemove();

    // ��ȡѡ������Ƭ��
    FNLETimelines GetSelected();
    // ��ȡλ��frames��ѡ���Ƭ��
    FNLETimelines GetSelected(int frames);
    // ��ȡ���trackIndexλ��framesѡ���Ƭ��
    FNLETimelinePtr GetSelected(int trackIndex, int frames);
    // ��ǰ������ѡ���Ƭ��
    FNLETimelinePtr GetCurrentSelected();
    void SetCurrentSelected(FNLETimelinePtr timeline);

    // ѡ��Ƭ��trackIndex:�ڼ����, frames:�ڼ�֡, enabled:trueΪѡ��falseΪ��ѡ��,multiSelected:�Ƿ��Ƕ�ѡ
    void SingleSelect(int trackIndex, int frame);
    void CtrlSelect(int trackIndex, int frame);
    void ShiftSelect(int trackIndex, int frame);
    void RectangleSelect(int trackFrom, int trackTo, int frameFrom, int frameTo);
    void SetSelected(int trackIndex, int frames, bool enabled, bool multiSelected = false);

    // �������ѡ��
    void UnselectAll();
    // ѡ������Ƭ��
    void SelectedAll();


    void Split();
    bool CanSplit();


    //// ɾ��ѡ��Ƭ��
    //void RemoveClips();
    //bool CanRemove();

    //// trimƬ�� leftSide:trimƬ�ε����true, frames:��ǰtrim����ʱ�����ϵ�֡
    //void AdjustClip(bool leftSide, int frames);

    FSequence* Clone() override;

Q_SIGNALS:
    // ��������ź�
    void sigTrackUpdate();
    // ����ؽ��ź�
    void sigTrackRebuild();
    // Ƭ��ѡ��ı��ź�
    void sigSelectionChanged();

    void sigPause();

    //void sigDoCommand();

    //void sigPasted(FSNLETimeline *timeline);

public:
    void _InsertTrack(int trackIndex, FTrackPtr track);
    void _RemoveTrack(FTrackPtr track);
    void _ResetTimelineLevel();

protected:
    FSequence(NLEComPtr<INLETimelineBase> timeline, QObject *parent = 0);
    ~FSequence();

protected:
    void PushCommand(FUndoCommand *commond);
    void BeginComposite();
    void EndComposite();

    void PushUpdateCommond();
    void PushRebuildTrackCommond();

protected:
    FTracks m_tracks;
    FNLETimelinePtr m_curSelectedTimeline;

    int m_currentFrames;

    friend class FNLETimelineFactory;

};

typedef NLEComPtr<FSequence> FSequencePtr;

#endif // FNLETIMELINE_H
