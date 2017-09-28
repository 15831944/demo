#ifndef TIMELINECONTROL_H
#define TIMELINECONTROL_H

#include <QtCore/QObject>
#include <memory>

#include "cMouseStreamCtrl.h"

#include "inc_FSTimelineView/fstimelineview.h"
#include "inc_FSCommonlib/FSNLETimeline.h"

#include "TimelineClip.h"
#include "UndoCommand.h"

class TimelineTrack;
class FSNLETimeline;
class UndoCommand;
class PlayerEditorManager;
class TitleBarManager;
struct ClipColor;
class MarkPointMgr;
class ClipMarkerMgr;
/*
	ʱ���߿�����
*/
class TimelineManager : public QObject
{
	Q_OBJECT
public:
	static TimelineManager* GetInstance();
	void Reset();
	void Load(INLETimelineBase *rootTimeline);
	// ����Ƭ��
	Clip* AddClip(int trackIndex, int frames, FSNLETimeline *timeline,bool bEmitSelectChange = true);

	// �ƶ�Ƭ��
	void MoveClip(int trackIndex, int frames, Clip* clip);

	// ɾ��ѡ��Ƭ��
	void RemoveClips();
	bool CanRemove();

	// trimƬ�� leftSide:trimƬ�ε����true, frames:��ǰtrim����ʱ�����ϵ�֡
	void AdjustClip(bool leftSide, int frames);

	//��ȡ����trim�ķ�Χ��leftSide:trimƬ�ε����true, ����ֵx��ʾ�����϶�����󳤶ȣ���ֵ��y��ʾ�����϶�����󳤶ȣ���ֵ
	QPoint GetTrimRange(bool bLeftSide);

	//trimƬ��,startPos��length�µĿ�ʼλ�úͳ���
	void Trim(Clip* clip, int startPos, int length);


	// split��ǰѡ���Ƭ��
	void Split();
	bool CanSplit();

	// ������ǰѡ��Ƭ��
	void Copy();
	bool CanCopy();

	// ճ����ǰѡ��Ƭ��
	void Paste();
	bool CanPaste();

	// ���е�ǰѡ��Ƭ��
	void Cut();
	bool CanCut();
	
	// ��ȡѡ������Ƭ��
	Clips GetSelected();
	// ��ȡλ��frames��ѡ���Ƭ��
	Clips GetSelected(int frames);
	// ��ȡ���trackIndexλ��framesѡ���Ƭ��
	Clip* GetSelected(int trackIndex, int frames);

	//��ȡΪѡ�е�clip
	Clips GetUnselected();

	void SingleSelect(int nTrackIndex,int nFrame);

	void BeginRectangleSelect();
	void RectangleSelect(int nTrackFrom, int nTrackTo, int nFrameFrom, int nFrameTo);
	void EndRectangleSelect();

	void SetShiftSelectBaseClip(Clip *clip);
	void ShiftSelect(int nTrackIndex, int nFrame);
	void CtrlSelect(int nTrackIndex, int nFrame); 
	void SelectTrack(int nTrackIndex);
	//�ṩ���������༭��ʹ��
	void MultiSelect(QList<FSNLETimeline*> timelines);
	// �������ѡ��
	void UnselectAll();
	// ѡ������Ƭ��
	void SelectedAll();
	//ѡ�����пɱ༭Ƭ��
	void SelectAllEditableClips();


	// ��ȡ���й��
	TimelineTracks GetTracks();
	TimelineTrack* GetTrack(int index);
	int GetTrackCount();

	Clips GetClips();
	Clips GetEditableClips();
	Clips GetClipsWithout(Clip *pClip);

	// ������
	void InsertTrack(int trackIndex);
	// �Ƴ����
	void RemoveTrack(int index);
	// �Ƴ����пչ��
	void RemoveAllEmptyTrack();
	// �Ƴ������Ŀչ��
	void RemoveTailEmptyTrack();
	// �Ƿ��пչ��
	bool HasEmptyTrack();

	// ��ȡʱ������ʱ��
	int GetDuration();
	// ���õ�ǰ֡
	void SetCurrentFrames(int frames);
	int GetCurrentFrames();

	// Undo/Redo����
	bool CanUndo();
	bool CanRedo();
	void Undo();
	void Redo();
	void BeginComposite();
	void EndComposite();
	void SetUndoLimit(int limit);

	// Mute����ѡ��Ƭ��, ֻMute��������Ƭ��
	void Mute(bool enabled);
	void CanMute(Clip *clip, bool &canMute, bool &hadMute);

	// Detach����ѡ��Ƭ��, ֻdetach��������Ƭ��
	void Detach();
	bool CanDetack(Clip *clip);

	// �����������Filter filter:���filter, type:���״̬����, level:��filter������
	void AddMouseFilter(Clip *clip, FSNLETimeline *filter, MouseEvent type = MouseEvent::MouseEvent_None, int level = 0);
	bool CanAddMouseFilter(Clip *clip);

	//�����������
	void AddMouseSound(Clip *clip,QString soundPath);

	
	// ��ȡʱ���߸�NLETimeline
	FSNLETimeline* GetRootTimeline();

	QList<TimelineTrack*> GetHidenTracks();
	QList<TimelineTrack*> GetFreezenTracks();

	// ��ȡ�������༭��������
	PlayerEditorManager* GetPlayerEditManager();
	TitleBarManager* GetTitleBarManager();

	void SetDisplayName(QString ancestralGuid, QString displayName);

	
	void HideTrack(int trackIndex);
	void ShowTrack(int trackIndex);
	void FreezeTrack(int trackIndex);
	void UnfreezeTrack(int trackIndex);
	void SaveHidenFreezeTrack2RootTimeline();
	void RestoreHidenFreezeTrackFromRootTimeine(FSNLETimeline *srcRootTimeline);


	bool CanFreezeFrame(Clip *clip);
	void FreezeFrame(Clip* clip,int len = 2 *25); //len : ��֡�ĳ���

	QPoint GetDragRange(Clip *clip,bool bLeftDrag);
	void ChangeSpeed(Clip *clip,int newStart,int newLen);

	void SetSpeedScale(FSNLETimeline* timeline, float scale);


	void SelectColorGroup(Clip *clip);
	QColor GetClipDefaultColor(Clip *clip);
	QColor GetClipColor(QString name);
	QList<ClipColor> GetClipColorList();

	Clip* GetClipWithTimline(FSNLETimeline* timeline);
	MarkPointMgr *GetMarkPointMgr();
	ClipMarkerMgr *GetClipMarkerMgr();

Q_SIGNALS:
	// ��������ź�
	void signalTrackUpdate();
	// ����ؽ��ź�
	void signalTrackRebuild();
	// Ƭ��ѡ��ı��ź�
	void signalSelectionChanged();

	void sigPause();
	void sigDoCommand();

	void sigPasted(FSNLETimeline *timeline);


public:
	TimelineManager(QObject *parent);
	~TimelineManager();

	void _AdjustClip(ClipPtr clip, int startPos, int len);
	void _InsertTrack(int trackIndex, TimelineTrackPtr track);
	void _RemoveTrack(TimelineTrackPtr track);
	void _Mute(ClipPtr clip, bool mute);
	void _Detach(ClipPtr videoClip, ClipPtr audioClip);
	void _UnDetach(ClipPtr videoClip, ClipPtr audioClip);
	void _RemoveMouseFilter(ClipPtr clip, ClipPtr filter);
	void _AddMouseFilter(ClipPtr clip, ClipPtr filter, MouseEvent type = MouseEvent::MouseEvent_None, int level = 0);
	void _AddMouseSound(ClipPtr clip, QString soundPath);
	void _RemoveMouseSound(ClipPtr clip);
	void _ResetAllClipLevel();

	void _HideTrack(int trackIndex);
	void _ShowTrack(int trackIndex);
	void _FreezeTrack(int trackIndex);
	void _UnfreezeTrack(int trackIndex);
	float _ChangeSpeed(ClipPtr clip, int newStart, int newLen);
	void _ChangeSpeedStandar(ClipPtr clip, int start, float scale);
	int _SetSpeedScale(ClipPtr clip, float scale);
	void _UnsetSpeedScale(ClipPtr clip, float scale, int trimlen);
private:
	ClipPtr CreateClipFromTimeline(FSNLETimeline *timeline);
	ClipPtr GetClipPtrFromClip(Clip *clip);
	ClipPtr GetClipPtrWithTimeline(FSNLETimeline *timeline);
	void PushCommand(UndoCommand *pCommond);
	void PushCommand(QUndoCommand *pCommond);
	void RemoveClip(Clip *clip);
	Clips GetClips(int frames);
	Clips GetEditableClips(int frames);
	void InitClipBkColor();

	void ManumalEmitSelectedChanged();
private:
	FSNLETimeline *m_pRootTimeline;
	TimelineTracksPtr m_tracks;
	
	ClipsPtr m_pCopyedClips;
	QUndoStack *m_UndoStack;

	int m_curFrames;
	bool m_canPaste;

	PlayerEditorManager *m_playerEditManager;
	TitleBarManager *m_pTitleBarManager;

	Clip *m_pShiftSelectBaseClip;
	Clips m_lstRectangleSelectsTmpClips;

	QMap<TimelineType, QColor> m_defaultBkColor;
	QList<ClipColor> m_allBkColors;

	MarkPointMgr* m_pMarkPointMgr;
	ClipMarkerMgr *m_pClipMarkerMgr;
private:
	friend class PlayerEditorManager;
	friend class MarkPointMgr;
	friend class ClipMarkerMgr;
};

struct ClipColor
{
	QString name;
	QString tranme;
	QColor clr;
	QPixmap icon;
	ClipColor(QColor c, QString n, QString tr,QString iconPath) :name(n), tranme(tr), clr(c),icon(iconPath){}
};


//////////////////////////////////////////////////////////////////////////

/*
	�������༭��������
*/
class PlayerEditorManager : public IPlayerEditorManager
{
	Q_OBJECT
public:
	PlayerEditorManager(TimelineManager *manager, QObject *parent);
	
	void AddTimeline(FSNLETimeline *timeline) override;
	void AddTimelines(QList<FSNLETimeline*> timelines) override;
	void RemoveSelected() override;
	void AddMouseFilter(FSNLETimeline *tl, FSNLETimeline *filter) override;
	void AddMouseSound(FSNLETimeline *tl, QString soundPath) override;

	QList<FSNLETimeline*> GetTimelines() override;
	QList<FSNLETimeline*> GetSelected() override;
	QList<FSNLETimeline*> GetOtherSelected() override;
	void SetSelected(QList<FSNLETimeline*> timelines) override;
	void UnselectAll() override;
	bool HasTimelines() override;
	void SetDisplayName(QString ancestralGuid, QString displayName) override;
	void SetShiftSelectBaseTimeline(FSNLETimeline* timeline) override;

	void Undo() override;
	void Redo() override;
    void PushCommand(UndoCommand *pCommond) override;
	void BeginComposite() override;
	void EndComposite() override;



private:
	TimelineManager *m_manager;
	Clips m_selectedClips;
};


//////////////////////////////////////////////////////////////////////////

/*
�ṩ���˵���ʹ��
*/
class TitleBarManager : public ITitleBarManager
{
	Q_OBJECT
public:
	TitleBarManager(TimelineManager *manager, QObject *parent);

	bool CanUndo() override;
	void Undo() override;

	bool CanRedo() override;
	void Redo() override;

	bool CanCut() override;
	void Cut() override;

	bool CanCopy() override;
	void Copy() override;

	bool CanPaste() override;
	void Paste() override;

	bool CanDelete() override;
	void Delete() override;

private:
	TimelineManager *m_pTimelineMgr;
};


//////////////////////////////////////////////////////////////////////////
class MarkPointMgr : public QObject
{
	Q_OBJECT
public:
	MarkPointMgr(TimelineManager *manager, QObject *parent);
	void InitMarkPoints(QList<MarkPointPtr> mps);
	QList<MarkPointPtr> GetMarkPoints();
	void Add(int frame);
	void Remove(MarkPoint* mp);
	void RemoveAll();
	void Move(MarkPoint *mp, int newframe);
	void SetColor(MarkPoint* mp, QColor clr);
	void SetSelected(MarkPoint *mp, bool bSelected);
	void UnselectAll();

	MarkPoint* GetSelected();

	void Clear();
Q_SIGNALS:
	void sigUpdate();

private:
	MarkPointPtr Pt2Ptr(MarkPoint *mp);

	MarkPointPtr _Add(int frame);
	void _Add(MarkPointPtr mp);
	void _Remove(MarkPointPtr mp);
	void _Move(MarkPointPtr mp, int pos);
private:
	TimelineManager *m_manager;
	QList<MarkPointPtr> m_markPoints;

	friend class AddTLMarkCommond;
	friend class RemoveTLMarkCommond;
	friend class MoveTLMarkCommond;
};

class ClipMarkerMgr : public QObject
{
	Q_OBJECT
public:
	ClipMarkerMgr(TimelineManager *manager, QObject *parent);
	void Add(FSNLETimeline*tl, int frame);
	void Remove(FSNLETimeline*tl,int frame);
	void RemoveAll(FSNLETimeline*tl);
	void SetSelected(FSNLETimeline*tl, int frame,bool bSelected);
	void UnselectAll(FSNLETimeline*tl);
	void UnselectAll();

	bool CanAddMarker(FSNLETimeline* tl,int frame);
private:
	TimelineManager *m_manager;
	
	friend class AddClipMarkerCommond;
	friend class RemoveClipMarkerCommond;
};

#endif // TIMELINECONTROL_H
