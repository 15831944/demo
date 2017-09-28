/*
*Author:		zhy
*Date:			2016.06.13
*Description:	ʱ��߿ؼ�
*/

#pragma once


#include "inc_CommonLib/commonlib_global.h"

#include <QtWidgets/QWidget>
#include <QtCore/QList>

#include <tuple>

struct RulerPointerShape
{
	QPolygonF	shape;		//pointer����״
	int			height;		//pointer�߶�
	int			width;		//pointer�߶�
	QColor		color;
	bool		aligntop;	//pointer���ڳ��ӵ��Ϸ������·�
	int			linewidth;	//�߿��
	bool		showpostext; //�Ƿ���ʾ��ǰʱ���
	QColor		postextcolor;
};

class TimelineViewRuler;
class COMMONLIB_EXPORT TimelineRuler : public QWidget
{
	Q_OBJECT
public:
	TimelineRuler(QWidget *parent = nullptr);

	// ���õ�ǰ֡
	void SetCurrentFrames(int frames);
	// ��ȡ��ǰ֡
	int CurrentFrames();

	// ����ʱ���ƫ��֡
	void SetOffsetFrames(int frames);
	int OffsetFrames();

	// ����ʱ���ƫ�����أ������ڹ�����
	void SetOffsetPosition(int position);
	//int OffsetPosition();

	// �����ܳ�
	void SetTotalFrames(int frames);
	int TotaleFrames();

	// ��ǰʱ��߳�����ʾ����֡��
	int AvailableTotaleFrames();

	// ����ʱ���zoomֵ
    void SetZoom(float zoom);
    float Zoom();

	void StartZoomAndScrollRuler();
	int GetZoomAndScrollRulerOffsetPosition();

    float FindZoom(int frames, int position);

	// ����ʱ������zoom
    void SetMaxZoom(float zoom);
    float MaxZoom();

	// ����֡��
	void SetFPS(float fps);
	float FPS();

	// ʱ���Ԥ���
	int Height();


	void setObjectName(QString name);

	// λ�õ�ת��֡
	float Position2FramesF(int pos);
	// ��ת����λ��
	float Frames2PositionF(int frames);
	// ֡��ת�����ȣ����أ�
	float Frames2DurationF(int frames);
	// ���ȣ����أ�ת����֡��
	float Duration2FramesF(int duration);

	// ���ݳ��Ⱥ���֡�����ض�Ӧ��zoom,
	int ZoomFromWidthAndTotaleFramesF(int rulerWidth, int totalFrames);
	// �ؽ�ʱ��߱�����
	// �����ֱ�zoom���ȡ� zoom��Ӧ�����س��ȡ��̶���
    void RebuildRulerConvertor(QList<std::tuple<float, int, int>> zoomPixelUnit);

	// �Ƿ���Ĭ�ϵ�CursorShape
	void SetCursorEnable(bool enable);
	// �Ƿ�����קʱ�������/��Сzoomֵ
	void SetDragable(bool enable);

	void SetMouseReleaseEmitFramesChangedEnabled(bool enable);
	void SetMousePressEmitFramesChangedEnabled(bool enable);

	// �����λ��ת��Ϊ֡ʱ���Ƿ������������
	void SetFramesRound(bool round);
	bool GetFramesRound();

	void SetSingalClickStartEndFrameChangeEnabled(bool enable);

	//����Pointer����״
	void SetPointerShape(RulerPointerShape shape);

	//���ÿ̶Ⱥ�ʱ�����ɫ
	void SetDrawColor(QColor clr);

Q_SIGNALS:
	void sigSingleClickStartFramesChanged();
	void sigSingleClickEndFrameChanged();
	void StartFramesChanged();
	void EndFramesChanged();
	void FramesChanged(int frames);
	void StartZoomChanged();
	void EndZoomChanged();
	void ZoomChanged(int zoom);
	void OffsetFramesChanged(int frames);
	void sigRightClicked(QPoint pt);
private:
	TimelineViewRuler *m_p;
};


