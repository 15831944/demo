#ifndef FNLETIMELINE_H
#define FNLETIMELINE_H
#include "INLETimelineBase.h"

#include "inc_FProject/fproject_global.h"

#include "inc_CommonLib/NLETimeline.h"

#include "inc_FProject/FRef.h"

class FTrack;



class FPROJECT_EXPORT FNLETimeline : public NLETimeline, public FRef
{
    //Q_OBJECT
public:
    enum Type
    {
        Unknown = 0,
        Video,
        Audio,
        VideoAudio,
    };
public:

    Type GetType();

    void SetType(Type type);

    // Ƭ���ڹ����λ��
    virtual int GetStartAtTrack();

    virtual int GetEndAtTrack();

    //Ƭ�γ���
    virtual int GetLenAtTrack();

    // Ƭ�ε�trimin
    int GetStartAtSrc();

    // Ƭ��ԭʼʱ��
    int GetSrcLen();

    // ����Ƭ��λ��(�˴�ֻ�������, ��Ƭ�α��������ӵ�NLETimelineʱʹ�ô˱�������λ��)
    void SetStartAtTrack(int pos);

    // Ƭ���Ƿ�ѡ��
    bool GetSelected();

    void SetSelected(bool selected);


    // ��ȡƬ�����ڹ��Index
    int GetIndex();

    // ��һ��Ƭ��
    NLEComPtr<FNLETimeline> NextTimeline();

    // ��һ��Ƭ��
    NLEComPtr<FNLETimeline> PreTimeline();

    // �����Clone���ز�������ָ�룬��FNLETimeline��Ҫso���¶���clone����
    virtual NLEComPtr<FNLETimeline> clone();

public:
    void SetTrack(FTrack* track);
    FTrack* GetTrack();

protected:
    FNLETimeline(NLEComPtr<INLETimelineBase> timeline, QObject *parent = nullptr);
    // ʹ��clone()���п�¡
    FNLETimeline* Clone() override;
private:
    Type m_type;
    bool m_selected;
    int m_index;
    FTrack *m_track;
private:
    friend class FNLETimelineFactory;
};

typedef NLEComPtr<FNLETimeline> FNLETimelinePtr;
typedef QList<NLEComPtr<FNLETimeline>> FNLETimelines;




class FPROJECT_EXPORT FNLEDragTimeline
{
public:
    FNLEDragTimeline(FNLETimelinePtr timeline);
    // Ƭ���ڹ����λ��
    int GetStartAtTrack();

    //Ƭ�γ���
    int GetLenAtTrack();

    void SetStartAtTrack(int frames);

    int GetIndex();
    void SetIndex(int index);

    FNLETimelinePtr GetTimeline();

private:
    int m_startAtTrack;
    int m_lenAtTrack;
    int m_trackIndex;

    FNLETimelinePtr m_timeline;
};

typedef QList<FNLEDragTimeline> FNLEDragTimelines;




#endif // FNLETIMELINE_H
