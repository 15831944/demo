#ifndef FTRACK_H
#define FTRACK_H

#include "inc_FProject/FNLETimeline.h"

class FSequence;

class FPROJECT_EXPORT FTrack : public FRef
{
public:
    FTrack(FSequence *sequence);
    ~FTrack();

    FSequence* GetSequence();

    // ��ȡ����Ƭ��
    FNLETimelines GetTimelines();
    // ��ȡλ��frames��Ƭ��
    FNLETimelinePtr GetTimeline(int frames);

    FNLEDragTimelines GetDragTimelines();
    void SetDragTimelines(FNLEDragTimelines timelines);

    // ��ȡ��ǰ���Index
    int GetIndex();

    // ��ȡ���ʱ��(֡)
    int GetDuration();

    void AddTimeline(int frames, FNLETimelinePtr timeline);

    void RemoveTimeline(FNLETimelinePtr timeline);

    void MoveTimeline(int frames, FNLETimelinePtr timeline);



    //��ȡ�ų�rejectClips֮���clips
    //Clips GetRejectClips(Clips rejectClips);

    //��ȡ��������FromFrame��nEndFrame֮���clip
    //Clips GetInsideClips(int nFromFrame, int nEndFrame);

    //��ȡ��������FromFrame��nEndFrame֮���֮���clip
   // QPair<Clips, Clips> GetInsideOutsizeClips(int nFromFrame, int nEndFrame);

    //��ȡnFrame�ұߵ�clips������nFrame
    //Clips GetRightClips(int nFrame);
    //��ȡnFrame��ߵ�clips������nFrame
    //Clips GetLeftClips(int nFrame);

    // ��ȡѡ��Ƭ��
    FNLETimelines GetSelected();
    FNLETimelinePtr GetSelected(int frame);
    //��ȡδѡ��Ƭ��
    FNLETimelines GetUnselected();

public:
    bool CanSplit(int frames);
    FNLETimelinePtr Split(FNLETimelinePtr clip, int frames);
    void Split(FNLETimelinePtr clip, FNLETimelinePtr clip2);
    void UnSplit(FNLETimelinePtr clip, FNLETimelinePtr clip2);
private:
    FNLETimelines m_timelines;
    FNLEDragTimelines m_dragTimelines;
    FSequence *m_sequence;
};

typedef NLEComPtr<FTrack> FTrackPtr;
typedef QList<FTrackPtr> FTracks;

#endif // FNLETIMELINE_H
