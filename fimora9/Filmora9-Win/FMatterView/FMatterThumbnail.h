#ifndef FMATTERTHUMBNAILBASE_H
#define FMATTERTHUMBNAILBASE_H
#include "inc_FCommonLib/FBaseWidget.h"

class FLabel;
class FLineEdit;
class QProgressBar;

/*FMatterThumbnailBase*/
class FMatterThumbnailBase : public FBaseWidget
{
	Q_OBJECT

public:
	FMatterThumbnailBase(QWidget *parent = nullptr);
	~FMatterThumbnailBase();

	void SetTitle(const QString&);
	void SetEditable(bool);
	void Click();
	void Unclick();
	void Rename();

Q_SIGNALS:
	void sigClicked();
	void sigDoubleClicked();
	void sigAdd();
	void sigTitleChanged(const QString&);

protected:
	void paintEvent(QPaintEvent *) override;
	void resizeEvent(QResizeEvent *) override;
	void mousePressEvent(QMouseEvent *) override;
	void mouseReleaseEvent(QMouseEvent *) override;
	void mouseMoveEvent(QMouseEvent *) override;
	void mouseDoubleClickEvent(QMouseEvent *) override;
	void enterEvent(QEvent *) override;
	void leaveEvent(QEvent *) override;

protected:
	QString GetDisplayString(QString);
	void slotEditingFinished();

protected:
	bool m_bHover;                // �����ͣ
	bool m_bClicked;              // �����
	bool m_bAddable;              // ����ӵ�ʱ����
	bool m_bEditable;             // �ɱ༭���޸ı��⣬Ĭ�Ͽɱ༭��
	bool m_bTryEdit;
	bool m_bBeginEdit;
	QDateTime m_TryEditTime;
	QPointF m_AddPt;              // ����ͼ���ĵ㣨����ӵ�ʱ���ߵĵ㣩
	QString m_TitleStr;           // ����
	QRect m_ThumbnailRect;        // ����ͼλ��
	QRect m_BottomlineRect;       // �ײ�ָʾ��λ��
	FLabel *m_pTitleLbl;          // ����Label 
	FLineEdit *m_pTitleLineEdit;  // ����LineEdit
};

/*FThumbnailDownload*/
class FThumbnailDownload : public FMatterThumbnailBase
{
	Q_OBJECT

public:
	FThumbnailDownload(QWidget* parent = nullptr);
	~FThumbnailDownload();

protected:
	void resizeEvent(QResizeEvent *) override;

private:
	QProgressBar *m_pProgressBar;
};

/*FMediaThumbnail*/
class FMediaThumbnail : public FMatterThumbnailBase
{
	Q_OBJECT

public:
	FMediaThumbnail(QWidget* parent = nullptr);
	~FMediaThumbnail();

Q_SIGNALS:
	void sigEditInActionCam();

protected:
	void resizeEvent(QResizeEvent *) override;
	void mouseReleaseEvent(QMouseEvent *) override;
	void mouseMoveEvent(QMouseEvent *) override;
	void enterEvent(QEvent *) override;
	void leaveEvent(QEvent *) override;

private:
	FLabel *m_pActionCamLbl;
	FLabel *m_pVideoLbl;
};
#endif // FMATTERTHUMBNAILBASE_H
