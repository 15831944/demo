#ifndef TIMELINECLIP_H
#define TIMELINECLIP_H

#include <memory>

class FSNLETimeline;
class TimelineTrack;

/*
	ʱ����Ƭ��
*/
class Clip
{
public:
	// Ƭ���ڹ����λ��
	int GetStartAtTrack();

	int GetEndAtTrack();
	
	//Ƭ�γ���
	int GetLenAtTrack();

	// Ƭ�ε�trimin
	int GetStartAtSrc();
	// Ƭ��ԭʼʱ��
	int GetSrcLen();

	// ����Ƭ��λ��(�˴�ֻ�������, ��Ƭ�α��������ӵ�NLETimelineʱʹ�ô˱�������λ��)
	void SetStartAtTrack(int pos);

	// Ƭ���Ƿ�ѡ��
	bool GetSelected();

	// ��ȡƬ������
	int GetType() const;
	// ��ȡƬ��Name
	QString GetName() const;

	// ��ȡƬ�����ڹ��Index
	int GetIndex();

	// ��һ��Ƭ��
	Clip* NextClip();
	// ��һ��Ƭ��
	Clip* PreClip();

	FSNLETimeline* GetNLETimeline();


protected:
	virtual void CloneAble(Clip* pAnther);

public:
	Clip(FSNLETimeline *timeline);
	~Clip();

	virtual Clip* Clone();

	void SetTimelineTrack(TimelineTrack *track);
	TimelineTrack* GetTimelineTrack();
	// ��ȡclip���ڹ��,clip���ڹ����,����Copy��Cut������clip��
	void SetCopyIndex(int index);
	int GetCopyIndex();
	void SetSelected(bool selected);

private:
	FSNLETimeline *m_timeline;
	bool m_selected;
	int m_index;
	int m_startAtTrack;

	TimelineTrack *m_track;

};

typedef QList<Clip*> Clips;
typedef std::shared_ptr<Clip> ClipPtr;
typedef QList<ClipPtr> ClipsPtr;


class TimelineManager;

/*
	ʱ���߹��
*/
class TimelineTrack
{
public:
	// ��ȡ����Ƭ��
	Clips GetClips();
	//��ȡ�ų�rejectClips֮���clips
	Clips GetRejectClips(Clips rejectClips);

	//��ȡ��������FromFrame��nEndFrame֮���clip
	Clips GetInsideClips(int nFromFrame, int nEndFrame);

	//��ȡ��������FromFrame��nEndFrame֮���֮���clip
	QPair<Clips,Clips> GetInsideOutsizeClips(int nFromFrame, int nEndFrame);

	//��ȡnFrame�ұߵ�clips������nFrame
	Clips GetRightClips(int nFrame);
	//��ȡnFrame��ߵ�clips������nFrame
	Clips GetLeftClips(int nFrame);

	// ��ȡѡ��Ƭ��
	Clips GetSelected();
	//��ȡδѡ��Ƭ��
	Clips GetUnselected();

	// ��ȡ��ǰ���Index
	int GetIndex();

	// ��ȡ���ʱ��(֡)
	int GetDuration();

	// ��ȡλ��frames��Ƭ��
	Clip* GetClip(int frames);

	void Hide();
	void Show();
	void Freeze();
	void Unfreeze();
	bool IsHiden();
	bool IsFreeze();
	bool IsEditable();

	bool IsEmpty();
	TimelineManager* GetManager();

private:
	void SetManager(TimelineManager *manager);
	bool HaveClip(ClipPtr clip);
	bool CanSplit(int frames);

public:
	TimelineTrack();

	void AddClip(int frames, ClipPtr clip);
	void RemoveClip(ClipPtr clip);
	void MoveClip(int frames, ClipPtr clip);

	ClipsPtr GetSelectedPtr();
	ClipPtr GetSelectedPtr(int frames);
	ClipPtr GetClipPtr(int frames);
	ClipsPtr GetClipsPtr();
	void RemoveClips();

	ClipPtr Split(ClipPtr clip, int frames);
	void Split(ClipPtr clip, ClipPtr clip2);
	void UnSplit(ClipPtr clip, ClipPtr clip2);

	void AdjustClip(int leftSide, int pos);


	int GetBeforeRemoveIndex();
	void SetBeforeRemoveIndex(int index);
	bool HintCollision(int frames, int duration);
	int GetClipIndex(Clip *clip);

private:
	ClipsPtr m_clips;
	TimelineManager *m_manager;
	int m_beforeRemoveIndex;
	friend class TimelineManager;

	bool m_bHide;
	bool m_bFreeze;
};
typedef QList<TimelineTrack*> TimelineTracks;
typedef std::shared_ptr<TimelineTrack> TimelineTrackPtr;
typedef QList<TimelineTrackPtr> TimelineTracksPtr;


#endif // TIMELINECLIP_H
