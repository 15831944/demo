#ifndef FEDITRECTANGLE_H
#define FEDITRECTANGLE_H

#include "inc_FCommonLib/FBaseWidget.h"

/*
edit: �ƶ������š���ת
*/

//class FEditRectangle : public FBaseWidget
//{
//	Q_OBJECT
//
//public:
//	FEditRectangle(QWidget *parent = 0);
//	~FEditRectangle();
//
//	void SetTimeline(QList<FNLETimeline*>);
//	// ���þ�������ɼ���
//	void SetRectangleVisible(bool);
//	void Update();
//	// ��ȡ��ǰ�ľ���
//	QRectF GetCurrentRect();  // ��Ӿ���
//	float GetRotateAngle();
//	void SetRenderRect(const QRectF&);
//
//signals:
//	void sigRectChanged(const QRectF&);   // �϶����ο�����ź�
//
//protected:
//	void paintEvent(QPaintEvent *) override;
//	void resizeEvent(QResizeEvent *) override;
//	void mousePressEvent(QMouseEvent *) override;
//	void mouseReleaseEvent(QMouseEvent *) override;
//	void mouseMoveEvent(QMouseEvent *) override;
//
//private:
//	void Init();
//	int WhichNamedPointEncounters(const QPointF&, qreal r = 5);  // ���ر���갴�µ�������������0-7�������򣬷���-1
//	QCursor GetCursorShape(const QPointF&);                      // ���ݴ�������꣬ȷ�����ָ����ʽ
//	// �����϶�״̬
//	void OnDraging();
//	// ��������״̬
//	void OnScaling(const QPointF&);
//	// ������ת״̬
//	void OnRotating(const QPointF&);
//	void OnRotatingAdjust(qreal);
//	bool IsRotatable(const QPointF&, qreal r = 20);
//	void AdjustRectangle();
//	qreal GetRotateAngle(const QPointF&);        // ������ת�Ƕȣ����ؽǶ�ֵ
//	void PointLeftTopBeScaled(const QPointF&);   // PointLeftTop������
//	void PointRightTopBeScaled(const QPointF&);  // PointRightTop������
//	void PointRightDownBeScaled(const QPointF&); // PointRightDown������
//	void PointLeftDownBeScaled(const QPointF&);  // PointLeftDown������
//	void PointTopBeScaled(const QPointF&);       // PointTop������
//	void PointRightBeScaled(const QPointF&);     // PointTop������
//	void PointDownBeScaled(const QPointF&);      // PointTop������
//	void PointLeftBeScaled(const QPointF&);      // PointTop������
//
//private:
//	FEditRectangleMgr *m_pMgr;
//	bool m_bVisible;           // ���ο��Ƿ�ɼ�
//	bool m_bPressed;           // ����Ƿ���о��ο�����
//	bool m_bDraged;            // ������϶����ο�ǰ�᣺m_bPressedΪtrue��
//	bool m_bRotated;           // ��ת״̬
//	int m_ScaledIndex;         // ��ǰ���ŵ�����
//	qreal m_RotateAngle;       // ���ο���ת�Ƕ�
//	QPointF m_CenterPoint;     // ���ο����ĵ�
//	QPointF m_PressPoint;      // ��갴�µĵ�
//	QPointF m_DragPoint;       // ����϶��ĵ�
//	QPointF m_PointLeftTop;    // ������0
//	QPointF m_PointTop;        // ������1
//	QPointF m_PointRightTop;   // ������2
//	QPointF m_PointRight;      // ������3
//	QPointF m_PointRightDown;  // ������4
//	QPointF m_PointDown;       // ������5
//	QPointF m_PointLeftDown;   // ������6
//	QPointF m_PointLeft;       // ������7
//	QPainterPath m_Rect;
//	QPixmap m_CursorMap;
//	QRectF m_RenderRect;       // ����������Ⱦ����
//};

class FNLETimeline;

class FKeyPoint : public QObject
{
	Q_OBJECT

public:
	enum KeyPoint{
		LeftTop_Pt = 0,
		Top_Pt,
		RightTop_Pt,
		Right_Pt,
		RightDown_Pt,
		Down_Pt,
		LeftDown_Pt,
		Left_Pt,
		Center_Pt
	};

public:
	FKeyPoint(QObject *parent = 0);
	~FKeyPoint();
	void SetPoint(KeyPoint, const QPointF&);
	QPointF GetPoint(KeyPoint);

private:
	QVector<QPointF> m_KeyPoints;
};

class FEditRectangleBase : public QObject
{
	Q_OBJECT

public:
	FEditRectangleBase(FNLETimeline* pTimeline, QRectF playerRegion, QObject* parent = 0);
	~FEditRectangleBase();

	virtual void DoMousePressEvent(QMouseEvent*);
	virtual void DoMouseMoveEvent(QMouseEvent*);
	virtual void DoPaintEvent(QPainter*, QPaintEvent*);
	// Ĭ������£��Ѿ��ε����ĵ�����Ϊ��ת�㡣������޸Ĵ˹���
	virtual void SetRotatePoint();                           
	// ���þ��������Ƿ�ɼ�
	void SetRectVisible(bool bVisible);
	bool IsRectVisible();
	// ���ò���������
	void SetPlayerRegion(const QRectF&);
	// ��ȡPainterPath
	QPainterPath GetPainterPath();

signals:
	void sigUpdate();
	void sigCursorShapeChanged(const QCursor&);

private:
	void InitKeyPoints();
	void AdjustKeyPoints();
	int WhichNamedPointEncounters(const QPointF&, qreal r = 5);  // ���ر���갴�µ�������������0-7�������򣬷���-1
	bool IsRotatable(const QPointF&, qreal r = 20);
	QCursor GetCursorShape(const QPointF&);                      // ���ݴ�������꣬ȷ�����ָ����ʽ
	// �����϶�״̬
	void OnDraging();
	// ��������״̬
	void OnScaling(const QPointF&);
	void CornerPointBeScaled(FKeyPoint::KeyPoint, const QPointF&);
	void EdgePointBeScaled(FKeyPoint::KeyPoint, const QPointF&);
	// ������ת״̬
	void OnRotating(const QPointF&);
	void OnRotatingAdjust(qreal);
	void AdjustRectangle();

protected:
	bool m_bVisible;             // ���ο��Ƿ�ɼ�
	bool m_bPressed;             // ����Ƿ���о��ο�����
	bool m_bDraged;              // ������϶����ο�ǰ�᣺m_bPressedΪtrue��
	bool m_bRotated;             // ��ת״̬
	int m_ScaledIndex;           // ��ǰ���ŵ�����
	qreal m_RotateAngle;         // ���ο���ת�Ƕ�
	QPointF m_PressPt;           // ��갴�µĵ�
	QPointF m_DragPt;            // ����϶��ĵ�
	QPointF m_RotatePt;          // ��ת��
	FNLETimeline *m_pTimeline;
	FKeyPoint m_KeyPoint;
	QRectF m_PlayerRegion;
	QPainterPath m_PainterPath;
	QPixmap m_CursorMap;
};

class FEditPIP : public FEditRectangleBase
{
	Q_OBJECT

public:
	FEditPIP(FNLETimeline* pTimeline, QRectF playerRegion, QObject* parent = 0);
	~FEditPIP();

	//void DoMousePressEvent(QMouseEvent*) override;
};

#endif // FEDITRECTANGLE_H



