/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:ÏêÇé´°¿Ú
**************************************************/
#pragma once

#include "SKismetInspectorGroup.h"
#include "SKismetInspectorItem.h"
#include "SKismetInspectorFuncIO.h"
#include "ui_SKismetInspector.h"
#include <QSpacerItem>


class SKismetInspector : public QWidget
{
	Q_OBJECT

public:
	SKismetInspector(QWidget* parent = Q_NULLPTR);
	~SKismetInspector();

	void InitUI(UFunction* func, QList<UVariant*> inputs, QList<UVariant*> outputs);
	void InitUI(UVariant* var);
	void ClearUI();

	EBlueprintItemType Type;

private:
	void ListAddGroup(SKismetInspectorGroup* itemWidget);
	void ListAddItem(SKismetInspectorGroup* itemGroup, SKismetInspectorItem* itemWidget);
	void ListAddIO(SKismetInspectorGroup* itemGroup, SKismetInspectorFuncIO* itemWidget);
	SKismetInspectorGroup* ToGroup(QWidget* widget);
	SKismetInspectorItem* ToItem(QWidget* widget);
	SKismetInspectorFuncIO* ToIO(QWidget* widget);

signals:
	void sigInspectorValueChanged(const FGuid& guid, EBlueprintItemDetailType detail, EBlueprintEditorKey key, const QString& value);
	void sigInspectorAddClicked(const FGuid& guid, EBlueprintItemType type, EBlueprintItemDetailType detail);
	void sigInspectorDelete(const FGuid& funcGuid, const FGuid& ioGuid, EBlueprintItemType type, EBlueprintItemDetailType detail);
	void sigInspectorMoveUp(const FGuid& funcGuid, const FGuid& ioGuid, EBlueprintItemType type, EBlueprintItemDetailType detail);
	void sigInspectorMoveDn(const FGuid& funcGuid, const FGuid& ioGuid, EBlueprintItemType type, EBlueprintItemDetailType detail);

public slots:
	// Group
	void slotCbStateChanged(int state);
	void slotAddClicked();
	void slotDeleteClicked();
	void slotMoveUpClicked();
	void slotMoveDnClicked();

private:
	Ui::SKismetInspector ui;
	QMap<SKismetInspectorGroup*, QList<QWidget*>> m_mapGroupItem;
	QSpacerItem* m_endSpacer = nullptr;
};

