#ifndef FEDITPLAYERMGR_H
#define FEDITPLAYERMGR_H

//#include "FPanelMgr.h"
class FNLETimeline;
class FEditRectangleBase;

class FEditPlayerMgr : public QObject
{
	Q_OBJECT

public:
	FEditPlayerMgr(QRectF playerRegion, QObject *parent = 0);
	~FEditPlayerMgr();

	// ����timeline
	void SetTimelines(QList<FNLETimeline*>);
	// ���ò���������
	void SetPlayerRegion(const QRectF&);
	// ��������¼�
	void DoMousePressEvent(QMouseEvent*);
	void DoMouseMoveEvent(QMouseEvent*);
	void DoPaintEvent(QPainter*, QPaintEvent* e = nullptr);
	void DrawRectangles(QPainter*, const QPointF&);

signals:
	void sigUpdate();  // �ػ��ź�
	void sigCursorShapeChanged(const QCursor&);

private:
	void Init();

private:
	QList<FNLETimeline*> m_Timelines;
	QList<FEditRectangleBase*> m_Rects;
	QRectF m_PlayerRegion;
};

#endif // FEDITPLAYERMGR_H
