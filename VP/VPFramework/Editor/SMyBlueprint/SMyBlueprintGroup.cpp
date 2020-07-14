#include "SMyBlueprintGroup.h"

SMyBlueprintGroup::SMyBlueprintGroup(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.cbType, &QCheckBox::stateChanged, this, &SMyBlueprintGroup::sigCbStateChanged);
	connect(ui.btnModifiers, &QAbstractButton::clicked, this, &SMyBlueprintGroup::sigModifiersClicked);
	connect(ui.btnAdd, &QAbstractButton::clicked, this, &SMyBlueprintGroup::sigAddClicked);
}

SMyBlueprintGroup::~SMyBlueprintGroup()
{
}

void SMyBlueprintGroup::InitFunc(QList<UFunction*> funcs)
{
	Type = EBlueprintItemType::Function;

	QString snotes = /*"(0 Override)"*/ ""; //todo
	QString smodifiers = "Override"; //todo

	ui.cbType->setText(ToString(Type));
	ui.labelNotes->setText(snotes);
	ui.btnModifiers->setText(smodifiers);
	ui.btnAdd->setText("+ " + ToString(Type));

	if (smodifiers.isEmpty())
		ui.btnModifiers->hide();
}

void SMyBlueprintGroup::InitMember(QList<UVariant*> vars)
{
	Type = EBlueprintItemType::Member;

	QString snotes = "";
	QString smodifiers = "";

	ui.cbType->setText(ToString(Type));
	ui.labelNotes->setText(snotes);
	ui.btnModifiers->setText(smodifiers);
	ui.btnAdd->setText("+ " + ToString(Type));

	if (smodifiers.isEmpty())
		ui.btnModifiers->hide();
}
