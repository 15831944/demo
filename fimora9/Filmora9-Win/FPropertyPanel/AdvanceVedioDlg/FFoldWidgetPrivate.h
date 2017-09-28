#ifndef FFOLDWIDGETPRIVATE_H
#define FFOLDWIDGETPRIVATE_H

#include <QList>
#include "inc_FCommonLib\FBaseWidget.h"
#include "..\include\inc_FPropertyPanel\fpropertypanel_global.h"

class FFoldWidgetItem;
class QVBoxLayout;

class  FFoldWidgetPrivate : public FBaseWidget
{
	Q_OBJECT

public:
	FFoldWidgetPrivate(QWidget *parent, bool bShowMode = false);
	~FFoldWidgetPrivate();
	void AddItem(FFoldWidgetItem* item);
	void SetShowMode(bool bShowMode){ m_bExclusiveShow = bShowMode;};	
	void AddItems(const QList<FFoldWidgetItem*> items);
	void InsertItem(int iRow, FFoldWidgetItem* item);
	void InsertItems(int iRow, const QList<FFoldWidgetItem*> items);
	FFoldWidgetItem* TakeItem(int iRow);
	FFoldWidgetItem* Item(int iRow) const;

Q_SIGNALS:
	void sigUpdateSize(int iNewHeight);
private:
	void collapseItem();

protected:
	void resizeEvent(QResizeEvent *e)override;


private:
	void InitUI();
	void InitData();
	void InitConnections();
	void PreCheckItemList(FFoldWidgetItem* item);
	void SetCurItemsState(bool bIsShow){ m_bIsItemShow = bIsShow; };

private:
	bool m_bExclusiveShow; //ÿ�������Ƿ񻥳���ʾ
	bool m_bIsItemShow;      //��ǰ�Ƿ�������չ����
	QList<FFoldWidgetItem*> m_AllShrinkWidget;
	QVBoxLayout* m_VboxLayout; //��ֱ����
};

#endif // FFOLDWIDGETPRIVATE_H
