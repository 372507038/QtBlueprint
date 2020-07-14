#include "SKismetInspector.h"


SKismetInspector::SKismetInspector(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_endSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
}

SKismetInspector::~SKismetInspector()
{
	if (m_endSpacer)
	{
		ui.listLayout->removeItem(m_endSpacer);
		delete m_endSpacer;
	}
}

void SKismetInspector::InitUI(UFunction* func, QList<UVariant*> inputs, QList<UVariant*> outputs)
{
	Type = EBlueprintItemType::Function;

	//Function group
	SKismetInspectorGroup* funcGroup = new SKismetInspectorGroup;
	funcGroup->InitFunc(func, EBlueprintItemDetailType::Function);
	ListAddGroup(funcGroup);
	{
		QList<EBlueprintEditorKey> keys = {
			EBlueprintEditorKey::FunctionName,
			EBlueprintEditorKey::EFunctionAbstraction,
			EBlueprintEditorKey::EFieldModifiers,
			EBlueprintEditorKey::EAccessSpecifier
		};
		for (auto key : keys)
		{
			SKismetInspectorItem* item = new SKismetInspectorItem;
			item->InitFunc(func, EBlueprintItemDetailType::Function, key);
			ListAddItem(funcGroup, item);
		}
	}

	//Inputs group
	SKismetInspectorGroup* inputGroup = new SKismetInspectorGroup;
	inputGroup->InitFunc(func, EBlueprintItemDetailType::Input);
	ListAddGroup(inputGroup);
	for (auto input : inputs)
	{
		SKismetInspectorFuncIO* item = new SKismetInspectorFuncIO;
		item->InitUI(func, input, EBlueprintItemDetailType::Input);
		ListAddIO(inputGroup, item);
	}

	//Outputs group
	SKismetInspectorGroup* outputGroup = new SKismetInspectorGroup;
	outputGroup->InitFunc(func, EBlueprintItemDetailType::Output);
	ListAddGroup(outputGroup);
	for (auto output : outputs)
	{
		SKismetInspectorFuncIO* item = new SKismetInspectorFuncIO;
		item->InitUI(func, output, EBlueprintItemDetailType::Output);
		ListAddIO(outputGroup, item);
	}

	//endSpacer
	ui.listLayout->removeItem(m_endSpacer);
	ui.listLayout->addItem(m_endSpacer);
}

void SKismetInspector::InitUI(UVariant* var)
{
	Type = EBlueprintItemType::Member;

	//Variable group
	SKismetInspectorGroup* varGroup = new SKismetInspectorGroup;
	varGroup->InitMember(var, EBlueprintItemDetailType::Variable);
	ListAddGroup(varGroup);
	{
		QList<EBlueprintEditorKey> keys = {
			EBlueprintEditorKey::VariableName,
			EBlueprintEditorKey::VariableType,
		};
		for (auto key : keys)
		{
			SKismetInspectorItem* item = new SKismetInspectorItem;
			item->InitMember(var, EBlueprintItemDetailType::Variable, key);
			ListAddItem(varGroup, item);
		}
	}

	//DefaultValue group
	SKismetInspectorGroup* defaultGroup = new SKismetInspectorGroup;
	defaultGroup->InitMember(var, EBlueprintItemDetailType::DefaultValue);
	ListAddGroup(defaultGroup);
	{
		QList<EBlueprintEditorKey> keys = {
			EBlueprintEditorKey::DefaultValue,
		};
		for (auto key : keys)
		{
			SKismetInspectorItem* item = new SKismetInspectorItem;
			item->InitMember(var, EBlueprintItemDetailType::DefaultValue, key);
			ListAddItem(defaultGroup, item);
		}
	}

	//endSpacer
	ui.listLayout->removeItem(m_endSpacer);
	ui.listLayout->addItem(m_endSpacer);
}

void SKismetInspector::ClearUI()
{
	//ui.listWidget->clear();
	for (auto ite = m_mapGroupItem.begin(); ite != m_mapGroupItem.end(); ite++)
	{
		for (auto widget : ite.value())
		{
			delete widget;
		}
		delete ite.key();
	}
	m_mapGroupItem.clear();
}

void SKismetInspector::ListAddGroup(SKismetInspectorGroup* itemWidget)
{
	ui.listLayout->addWidget(itemWidget);

	connect(itemWidget, &SKismetInspectorGroup::sigCbStateChanged, this, &SKismetInspector::slotCbStateChanged, Qt::UniqueConnection);
	connect(itemWidget, &SKismetInspectorGroup::sigAddClicked, this, &SKismetInspector::slotAddClicked, Qt::UniqueConnection);

	itemWidget->setProperty("VPType", "Group");
	m_mapGroupItem[itemWidget]; //Ìí¼Ó½ømap
}

void SKismetInspector::ListAddItem(SKismetInspectorGroup* itemGroup, SKismetInspectorItem* itemWidget)
{
	ui.listLayout->addWidget(itemWidget);

	connect(itemWidget, &SKismetInspectorItem::sigValueChanged, this, &SKismetInspector::sigInspectorValueChanged, Qt::UniqueConnection);

	itemWidget->setProperty("VPType", "Item");
	m_mapGroupItem[itemGroup].append(itemWidget);
}

void SKismetInspector::ListAddIO(SKismetInspectorGroup* itemGroup, SKismetInspectorFuncIO* itemWidget)
{
	ui.listLayout->addWidget(itemWidget);

	connect(itemWidget->Item(), &SKismetInspectorItem::sigValueChanged, this, &SKismetInspector::sigInspectorValueChanged, Qt::UniqueConnection);
	connect(itemWidget, &SKismetInspectorFuncIO::sigValueChanged, this, &SKismetInspector::sigInspectorValueChanged, Qt::UniqueConnection);
	connect(itemWidget, &SKismetInspectorFuncIO::sigDelete, this, &SKismetInspector::slotDeleteClicked, Qt::UniqueConnection);
	connect(itemWidget, &SKismetInspectorFuncIO::sigMoveUp, this, &SKismetInspector::slotMoveUpClicked, Qt::UniqueConnection);
	connect(itemWidget, &SKismetInspectorFuncIO::sigMoveDn, this, &SKismetInspector::slotMoveDnClicked, Qt::UniqueConnection);

	itemWidget->setProperty("VPType", "IO");
	m_mapGroupItem[itemGroup].append(itemWidget);
}

SKismetInspectorGroup* SKismetInspector::ToGroup(QWidget* widget)
{
	if (widget->property("VPType").toString() == "Group")
		return static_cast<SKismetInspectorGroup*>(widget);
	return nullptr;
}

SKismetInspectorItem* SKismetInspector::ToItem(QWidget* widget)
{
	if (widget->property("VPType").toString() == "Item")
		return static_cast<SKismetInspectorItem*>(widget);
	return nullptr;
}

SKismetInspectorFuncIO* SKismetInspector::ToIO(QWidget* widget)
{
	if (widget->property("VPType").toString() == "IO")
		return static_cast<SKismetInspectorFuncIO*>(widget);
	return nullptr;
}

void SKismetInspector::slotCbStateChanged(int state_)
{
	SKismetInspectorGroup* groupItem = qobject_cast<SKismetInspectorGroup*>(sender());
	const auto& listItems = m_mapGroupItem[groupItem];
	Qt::CheckState state = (Qt::CheckState)state_;
	bool bHide = (state == Qt::CheckState::Unchecked);

	for (auto wid : listItems)
	{
		wid->setHidden(bHide);
	}
}

void SKismetInspector::slotAddClicked()
{
	SKismetInspectorGroup* groupItem = qobject_cast<SKismetInspectorGroup*>(sender());
	emit sigInspectorAddClicked(groupItem->Guid, groupItem->Type, groupItem->TypeDetail);
}

void SKismetInspector::slotDeleteClicked()
{
	SKismetInspectorFuncIO* ioItem = qobject_cast<SKismetInspectorFuncIO*>(sender());
	emit sigInspectorDelete(ioItem->Guid, ioItem->Item()->Guid, ioItem->Item()->Type, ioItem->Item()->TypeDetail);
}

void SKismetInspector::slotMoveUpClicked()
{
	SKismetInspectorFuncIO* ioItem = qobject_cast<SKismetInspectorFuncIO*>(sender());
	emit sigInspectorMoveUp(ioItem->Guid, ioItem->Item()->Guid, ioItem->Item()->Type, ioItem->Item()->TypeDetail);
}

void SKismetInspector::slotMoveDnClicked()
{
	SKismetInspectorFuncIO* ioItem = qobject_cast<SKismetInspectorFuncIO*>(sender());
	emit sigInspectorMoveDn(ioItem->Guid, ioItem->Item()->Guid, ioItem->Item()->Type, ioItem->Item()->TypeDetail);
}
