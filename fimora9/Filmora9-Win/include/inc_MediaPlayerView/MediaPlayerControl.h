#pragma once

#ifndef MEDIAPLAYERCONTROL_H_H
#define MEDIAPLAYERCONTROL_H_H

/*
*Author:		zhy
*Date:			2016.04.29
*Description:	���������������������š���ͣ��ǰ/��һ֡��
*/

#include "INLEPlayer.h"

#ifdef WIN32

#ifdef MEDIAPLAYVIEW_EXPORT
#define MEDIAPLAYVIEW_EXT __declspec(dllexport)
#else
#define MEDIAPLAYVIEW_EXT __declspec(dllimport)
#endif

#else
#define MEDIAPLAYVIEW_EXT  
#endif



#include <functional>


#ifndef NLEInterface
#ifdef WIN32
#define NLEInterface interface
#else
#define NLEInterface struct
#endif
#endif

//#ifndef HVIEW
//typedef HWND HVIEW;
//#endif

NLEInterface IMediaStream;
NLEInterface INLERender;
class NLETimeline;

#include <QtCore/QObject>

class INLEFrame;

// ���ſ�����
class MEDIAPLAYVIEW_EXT IMediaPlayerControl : public QObject
{
	Q_OBJECT
public:
	static IMediaPlayerControl* CreateInstance();
	virtual void SetHwnd(HVIEW hview, const RECT &rect) = 0;
	virtual bool Open(int bSource, NLETimeline *timeline) = 0;
	virtual void SetRatio(float ratio) = 0;
	virtual float GetRatio() = 0;
	virtual bool Close() = 0;
	virtual bool Play() = 0;
	virtual bool IsPlaying() = 0;
	virtual bool Stop() = 0;
	virtual bool Pause() = 0;
    virtual void SetVolume(int volume) = 0;
    virtual int GetVolume() = 0;
	virtual bool IsPause() = 0;
	virtual bool Seek(int frames, int accurate) = 0;
	virtual bool IsSeeking() = 0;
	virtual bool Forward() = 0;
	virtual bool Backward() = 0;
	virtual int Duration() = 0;
	virtual int CurrentFrames() = 0;
	virtual bool HaveSource() = 0;
	virtual float FPS() = 0;
	virtual void DurationChanged() = 0;
	virtual INLEFrame* CaptureCurrentImage() = 0;
	virtual void Update() = 0;
	virtual NLETimeline* GetTimeline() = 0;

	// ����ǰ�ص����ƣ�����true���ţ�false������
	virtual void RegisterPlayStartCallback(std::function<bool()>) = 0;
	virtual void Release() = 0;

	virtual QImage GetCurrentImage() = 0;

	virtual NLEComPtr<IPlayerViewMgr> GetMediaPlayerMgr()= 0;


Q_SIGNALS:
	// ������֡�ص��źţ���λ֡
	void PlayingCallback(int frames);
	// ��ʼ����
	void PlayStartCallback();
	// ������ͣ
	void PlayPauseCallback();
	// ֹͣ
	void PlayStopCallback();
	// ����ֹͣ�ź�
	void PlayFinishCallback();
	// �������
	void PlayLoadFinishCallback();
	// Seek���
	void SeekFinishCallback(int frames);

	// ������֡�ص��źţ���λ֡��
	void PlayingCallbackMarkdown(int frames);

	// �����ź�
	void AudioVolumesCallback(int lvolume, int rvolume);

	// ʱ��߻���
	void RulerSeekCallback(int frames);

};


#endif
