/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:À¶Í¼ÏêÇé´°¿Ú
**************************************************/
#pragma once

#include "Runtime/Core/Guid.h"
#include "Runtime/Core/Class.h"
#include "Editor/Common/CommEnum.h"
#include "ui_SMyBlueprintItem.h"
#include <QTimer>
#include <QMenu>
#include <QKeyEvent>
#include <QMouseEvent>


class SMyBlueprintItem : public QWidget
{
	Q_OBJECT

public:
	SMyBlueprintItem(QWidget *parent = Q_NULLPTR);
	~SMyBlueprintItem();

	void InitFunc(UFunction* func);
	void InitMember(UVariant* var);

	void SetRenameMode(bool re);
	void PopupMenu();

	EBlueprintItemType Type;
	FGuid Guid;

signals:
	void sigRename(QString newName);
	void sigDelete();

public slots:
	void slotActionRename();
	void slotActionDelete();

private:
	bool eventFilter(QObject* object, QEvent* event) override;
	void mousePressEvent(QMouseEvent* e) override;

private:
	Ui::SMyBlueprintItem ui;
};
