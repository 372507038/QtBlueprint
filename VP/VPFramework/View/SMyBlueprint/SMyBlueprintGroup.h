/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:À¶Í¼ÏêÇé´°¿Ú
**************************************************/
#pragma once

#include "Model/Core/Guid.h"
#include "Model/Core/Class.h"
#include "ui_SMyBlueprintGroup.h"
#include "SMyBlueprintItem.h"

class SMyBlueprintGroup : public QWidget
{
	Q_OBJECT

public:
	SMyBlueprintGroup(QWidget *parent = Q_NULLPTR);
	~SMyBlueprintGroup();

	void InitFunc(QList<UFunction*> funcs);
	void InitMember(QList<UVariant*> vars);

	EBlueprintItemType Type;

signals:
	void sigCbStateChanged(int state);
	void sigModifiersClicked();
	void sigAddClicked();

private:
	Ui::SMyBlueprintGroup ui;
};
