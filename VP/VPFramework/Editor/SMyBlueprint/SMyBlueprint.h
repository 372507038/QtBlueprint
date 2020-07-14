/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:À¶Í¼ÏêÇé´°¿Ú
**************************************************/
#pragma once

#include <QWidget>
#include "ui_SMyBlueprint.h"
#include "SMyBlueprintGroup.h"

class SMyBlueprint : public QWidget
{
	Q_OBJECT

public:
	SMyBlueprint(QWidget* parent = Q_NULLPTR);
	~SMyBlueprint();

	void InitUI(UClass* curClass, QList<UFunction*> funcs, QList<UVariant*> vars);
	void RefreshUI(UClass* curClass, QList<UFunction*> funcs, QList<UVariant*> vars);
	void ClearUI();

	void AddNewItem(UFunction* func);
	void AddNewItem(UVariant* var);

private:
	void ListAddGroup(SMyBlueprintGroup* itemWidget);
	void ListAddItem(SMyBlueprintGroup* itemGroup, SMyBlueprintItem* itemWidget);
	void ListDeleteItem(SMyBlueprintGroup* itemGroup, SMyBlueprintItem* itemWidget);
	SMyBlueprintGroup* ToGroup(QWidget* widget);
	SMyBlueprintItem* ToItem(QWidget* widget);

signals:
	void sigModifiersClicked(EBlueprintItemType type);
	void sigAddClicked(EBlueprintItemType type);
	void sigRename(const FGuid& guid, EBlueprintItemType type, QString newName);
	void sigDelete(const FGuid& guid, EBlueprintItemType type);
	void sigItemClicked(const FGuid& guid, EBlueprintItemType type);
	void sigItemDoubleClicked(const FGuid& guid, EBlueprintItemType type);

public slots:
	// Group
	void slotCbStateChanged(int state);
	void slotModifiersClicked();
	void slotAddClicked();
	// Item
	void slotRename(QString newName);
	void slotDelete();
	// ListWidgetItem
	void slotItemClicked(QListWidgetItem* listItem);
	void slotItemDoubleClicked(QListWidgetItem* listItem);

private:
	Ui::SMyBlueprint ui;
	QMap<SMyBlueprintGroup*, QList<SMyBlueprintItem*>> m_mapGroupItem;
};
