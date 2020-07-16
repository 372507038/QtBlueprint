#include "SMyBlueprint.h"

SMyBlueprint::SMyBlueprint(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.listWidget, &QListWidget::itemClicked, this, &SMyBlueprint::slotItemClicked, Qt::UniqueConnection);
	connect(ui.listWidget, &QListWidget::itemDoubleClicked, this, &SMyBlueprint::slotItemDoubleClicked, Qt::UniqueConnection);
}

SMyBlueprint::~SMyBlueprint()
{
}

void SMyBlueprint::InitUI(UClass* curClass, QList<UFunction*> funcs, QList<UVariant*> vars)
{
	//funcs group
	SMyBlueprintGroup* funcGroup = new SMyBlueprintGroup;
	funcGroup->InitFunc(funcs);
	ListAddGroup(funcGroup);
	for (auto func : funcs)
	{
		SMyBlueprintItem* item = new SMyBlueprintItem;
		item->InitFunc(func);
		ListAddItem(funcGroup, item);
	}

	//vars group
	SMyBlueprintGroup* memberGroup = new SMyBlueprintGroup;
	memberGroup->InitMember(vars);
	ListAddGroup(memberGroup);
	for (auto var : vars)
	{
		SMyBlueprintItem* item = new SMyBlueprintItem;
		item->InitMember(var);
		ListAddItem(memberGroup, item);
	}
}

void SMyBlueprint::RefreshUI(UClass* curClass, QList<UFunction*> funcs, QList<UVariant*> vars)
{
	for (auto ite = m_mapGroupItem.begin(); ite != m_mapGroupItem.end(); ite++)
	{
		SMyBlueprintGroup* group = ToGroup(ite.key());
		auto items = ite.value();

		switch (group->Type)
		{
		case EBlueprintItemType::Function:
			Q_ASSERT(items.count() == funcs.count());
			group->InitFunc(funcs);
			break;
		case EBlueprintItemType::Member:
			Q_ASSERT(items.count() == vars.count());
			group->InitMember(vars);
			break;
		}

		for (int idx = 0; idx < items.count(); idx++)
		{
			switch (group->Type)
			{
			case EBlueprintItemType::Function:
				items[idx]->InitFunc(funcs[idx]);
				break;
			case EBlueprintItemType::Member:
				items[idx]->InitMember(vars[idx]);
				break;
			}
		}
	}
}

void SMyBlueprint::ClearUI()
{
	m_mapGroupItem.clear();
	ui.listWidget->clear();
}

void SMyBlueprint::AddNewItem(UFunction* func)
{
	for (auto ite = m_mapGroupItem.begin(); ite != m_mapGroupItem.end(); ite++)
	{
		SMyBlueprintGroup* group = ToGroup(ite.key());
		if (group->Type == EBlueprintItemType::Function)
		{
			SMyBlueprintItem* item = new SMyBlueprintItem;
			item->InitFunc(func);
			ListAddItem(group, item);
			break;
		}
	}
}

void SMyBlueprint::AddNewItem(UVariant* var)
{
	for (auto ite = m_mapGroupItem.begin(); ite != m_mapGroupItem.end(); ite++)
	{
		SMyBlueprintGroup* group = ToGroup(ite.key());
		if (group->Type == EBlueprintItemType::Member)
		{
			SMyBlueprintItem* item = new SMyBlueprintItem;
			item->InitMember(var);
			ListAddItem(group, item);
			break;
		}
	}
}

void SMyBlueprint::ListAddGroup(SMyBlueprintGroup* itemWidget)
{
	QListWidgetItem* listItem = new QListWidgetItem(ui.listWidget);
	listItem->setSizeHint(itemWidget->sizeHint());
	ui.listWidget->addItem(listItem);
	ui.listWidget->setItemWidget(listItem, itemWidget);

	connect(itemWidget, &SMyBlueprintGroup::sigCbStateChanged, this, &SMyBlueprint::slotCbStateChanged, Qt::UniqueConnection);
	connect(itemWidget, &SMyBlueprintGroup::sigModifiersClicked, this, &SMyBlueprint::slotModifiersClicked, Qt::UniqueConnection);
	connect(itemWidget, &SMyBlueprintGroup::sigAddClicked, this, &SMyBlueprint::slotAddClicked, Qt::UniqueConnection);

	itemWidget->setProperty("VPType", "Group");
	m_mapGroupItem[itemWidget]; //Ìí¼Ó½ømap
}

void SMyBlueprint::ListAddItem(SMyBlueprintGroup* itemGroup, SMyBlueprintItem* itemWidget)
{
	QListWidgetItem* listItem = new QListWidgetItem(ui.listWidget);
	listItem->setSizeHint(itemWidget->sizeHint());
	ui.listWidget->addItem(listItem);
	ui.listWidget->setItemWidget(listItem, itemWidget);

	connect(itemWidget, &SMyBlueprintItem::sigRename, this, &SMyBlueprint::slotRename, Qt::UniqueConnection);
	connect(itemWidget, &SMyBlueprintItem::sigDelete, this, &SMyBlueprint::slotDelete, Qt::UniqueConnection);

	itemWidget->setProperty("VPType", "Item");
	m_mapGroupItem[itemGroup].append(itemWidget);
}

void SMyBlueprint::ListDeleteItem(SMyBlueprintGroup* itemGroup, SMyBlueprintItem* itemWidget)
{
	for (int i = 0; i < ui.listWidget->count(); i++)
	{
		QListWidgetItem* listItem = ui.listWidget->item(i);
		if (ui.listWidget->itemWidget(listItem) == itemWidget)
		{
			delete ui.listWidget->takeItem(i);
			break;
		}
	}

	m_mapGroupItem[itemGroup].removeOne(itemWidget);
}

SMyBlueprintGroup* SMyBlueprint::ToGroup(QWidget* widget)
{
	if (widget->property("VPType").toString() == "Group")
		return static_cast<SMyBlueprintGroup*>(widget);

	//for (auto ite = m_mapGroupItem.begin(); ite != m_mapGroupItem.end(); ite++)
	//{
	//	if (ite.key() == widget)
	//	{
	//		return static_cast<SMyBlueprintGroup*>(widget);
	//	}
	//}

	return nullptr;
}

SMyBlueprintItem* SMyBlueprint::ToItem(QWidget* widget)
{
	if (widget->property("VPType").toString() == "Item")
		return static_cast<SMyBlueprintItem*>(widget);

	//for (auto ite = m_mapGroupItem.begin(); ite != m_mapGroupItem.end(); ite++)
	//{
	//	for (auto item : ite.value())
	//	{
	//		if (item == widget)
	//		{
	//			return static_cast<SMyBlueprintItem*>(widget);
	//		}
	//	}
	//}

	return nullptr;
}

void SMyBlueprint::slotCbStateChanged(int state_)
{
	SMyBlueprintGroup* groupItem = qobject_cast<SMyBlueprintGroup*>(sender());
	const auto& listItems = m_mapGroupItem[groupItem];
	Qt::CheckState state = (Qt::CheckState)state_;
	bool bHide = (state == Qt::CheckState::Unchecked);

	for (int i = 0; i < ui.listWidget->count(); i++)
	{
		QListWidgetItem* listItem = ui.listWidget->item(i);
		QWidget* itemWidget = ui.listWidget->itemWidget(listItem);
		for (auto item : listItems)
		{
			if (item != itemWidget)
				continue;
			listItem->setHidden(bHide);
			break;
		}
	}
}

void SMyBlueprint::slotModifiersClicked()
{
	SMyBlueprintGroup* groupItem = qobject_cast<SMyBlueprintGroup*>(sender());
	emit sigModifiersClicked(groupItem->Type);
}

void SMyBlueprint::slotAddClicked()
{
	SMyBlueprintGroup* groupItem = qobject_cast<SMyBlueprintGroup*>(sender());
	emit sigAddClicked(groupItem->Type);
}

void SMyBlueprint::slotRename(QString newName)
{
	SMyBlueprintItem* item = qobject_cast<SMyBlueprintItem*>(sender());
	emit sigRename(item->Guid, item->Type, newName);
}

void SMyBlueprint::slotDelete()
{
	SMyBlueprintItem* item = qobject_cast<SMyBlueprintItem*>(sender());
	emit sigDelete(item->Guid, item->Type);
}

void SMyBlueprint::slotItemClicked(QListWidgetItem* listItem)
{
	SMyBlueprintItem* item = ToItem(ui.listWidget->itemWidget(listItem));
	if (item)
		emit sigItemClicked(item->Guid, item->Type);
	else
		emit sigItemClicked(FGuid(), EBlueprintItemType::None);
}

void SMyBlueprint::slotItemDoubleClicked(QListWidgetItem* listItem)
{
	SMyBlueprintItem* item = ToItem(ui.listWidget->itemWidget(listItem));
	if (item)
		emit sigItemDoubleClicked(item->Guid, item->Type);
	else
		emit sigItemDoubleClicked(FGuid(), EBlueprintItemType::None);
}
