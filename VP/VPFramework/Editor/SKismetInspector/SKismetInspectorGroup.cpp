#include "SKismetInspectorGroup.h"

SKismetInspectorGroup::SKismetInspectorGroup(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.cbType, &QCheckBox::stateChanged, this, &SKismetInspectorGroup::sigCbStateChanged);
	connect(ui.btnAdd, &QAbstractButton::clicked, this, &SKismetInspectorGroup::sigAddClicked);
}

SKismetInspectorGroup::~SKismetInspectorGroup()
{
}

void SKismetInspectorGroup::InitFunc(UFunction* func, EBlueprintItemDetailType detail)
{
	Type = EBlueprintItemType::Function;
	TypeDetail = detail;
	Guid = func->GetObjectGuid();

	ui.cbType->setText(ToString(TypeDetail));
	if(detail == EBlueprintItemDetailType::Function)
		ui.btnAdd->hide();
}

void SKismetInspectorGroup::InitMember(UVariant* member, EBlueprintItemDetailType detail)
{
	Type = EBlueprintItemType::Member;
	TypeDetail = detail;
	Guid = member->GetObjectGuid();

	ui.cbType->setText(ToString(TypeDetail));
	ui.btnAdd->hide();
}
