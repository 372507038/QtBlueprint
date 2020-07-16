/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:ÏêÇé´°¿Ú
**************************************************/
#pragma once

#include "Model/Core/Guid.h"
#include "Model/Core/Class.h"
#include "View/Common/CommEnum.h"
#include "ui_SKismetInspectorGroup.h"
#include "SKismetInspectorItem.h"

class SKismetInspectorGroup : public QWidget
{
	Q_OBJECT

public:
	SKismetInspectorGroup(QWidget *parent = Q_NULLPTR);
	~SKismetInspectorGroup();

	void InitFunc(UFunction* func, EBlueprintItemDetailType detail);
	void InitMember(UVariant* member, EBlueprintItemDetailType detail);

	EBlueprintItemType Type;
	EBlueprintItemDetailType TypeDetail;
	FGuid Guid;

signals:
	void sigCbStateChanged(int state);
	void sigAddClicked();

private:
	Ui::SKismetInspectorGroup ui;
};
