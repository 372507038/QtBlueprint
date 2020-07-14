#include "SKismetInspectorItem.h"


SKismetInspectorItem::SKismetInspectorItem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

SKismetInspectorItem::~SKismetInspectorItem()
{
}

void SKismetInspectorItem::InitFunc(UFunction* func, EBlueprintItemDetailType detail, EBlueprintEditorKey key)
{
	Type = EBlueprintItemType::Function;
	TypeDetail = detail;
	TypeKey = key;
	Guid = func->GetObjectGuid();

	FuncSetUI(key, func);
}

void SKismetInspectorItem::InitFuncIO(UFunction* func, UVariant* io, EBlueprintItemDetailType detail, EBlueprintEditorKey key)
{
	Type = EBlueprintItemType::Function;
	TypeDetail = detail;
	TypeKey = key;
	Guid = io->GetObjectGuid();

	if(key != EBlueprintEditorKey::None)
		FuncSetUI(key, func, io);
}

void SKismetInspectorItem::InitMember(UVariant* member, EBlueprintItemDetailType detail, EBlueprintEditorKey key)
{
	Type = EBlueprintItemType::Member;
	TypeDetail = detail;
	TypeKey = key;
	Guid = member->GetObjectGuid();

	if (key != EBlueprintEditorKey::None)
		MemberSetUI(key, member);
}

void SKismetInspectorItem::FuncSetUI(EBlueprintEditorKey key, UFunction* func, UVariant* var)
{
	SetName(ToString(key));

	switch (key)
	{
	case EBlueprintEditorKey::FunctionName:
		this->SetLineEdit(func->GetObjectName());
		break;

	case EBlueprintEditorKey::EFunctionAbstraction:
		this->SetComboBox(QList<QString>({
			Script::ToString(EFunctionAbstraction::Normal),
			Script::ToString(EFunctionAbstraction::Virtual),
			Script::ToString(EFunctionAbstraction::PureVirtual) 
			}), 
			Script::ToString(func->m_FunctionAbstraction));
		break;

	case EBlueprintEditorKey::EFieldModifiers:
		this->SetComboBox(QList<QString>({
			Script::ToString(EFieldModifiers::Normal),
			Script::ToString(EFieldModifiers::Static),
			Script::ToString(EFieldModifiers::Const),
			Script::ToString(EFieldModifiers::Inline) 
			}),
			Script::ToString(func->m_Modifiers));
		break;

	case EBlueprintEditorKey::EAccessSpecifier:
		this->SetComboBox(QList<QString>({
			Script::ToString(EAccessSpecifier::Public),
			Script::ToString(EAccessSpecifier::Private),
			Script::ToString(EAccessSpecifier::Protected) 
			}),
			Script::ToString(func->m_AccessModifiers));
		break;
	}
}

void SKismetInspectorItem::MemberSetUI(EBlueprintEditorKey key, UVariant* var)
{
	SetName(ToString(key));

	switch (key)
	{
	case EBlueprintEditorKey::VariableName:
		this->SetLineEdit(var->GetObjectName());
		break;

	case EBlueprintEditorKey::VariableType:
		this->SetComboBox(QStringList({
			Script::ToString(EVariantType::Bool),
			Script::ToString(EVariantType::Int),
			Script::ToString(EVariantType::Double),
			Script::ToString(EVariantType::String),
			Script::ToString(EVariantType::Class),
			Script::ToString(EVariantType::Enum), 
			}),
			Script::ToString(var->m_VariantType));
		break;

	case EBlueprintEditorKey::DefaultValue:
		if (var->m_VariantType == EVariantType::Bool)
		{
			this->SetCheckBox(var->m_DefaultValue != "false");
		}
		else if (var->m_VariantType == EVariantType::Class || var->m_VariantType == EVariantType::Enum)
		{
			//ÔÝ²»Ö§³Ö
			this->SetComboBox(QStringList({ var->m_VariantTypeDetail }), var->m_VariantTypeDetail);
		}
		else
		{
			this->SetLineEdit(var->m_DefaultValue);
		}
		break;
	}
}

void SKismetInspectorItem::SetName(const QString& name)
{
	ui.labelName->setText(name);
}

void SKismetInspectorItem::SetLineEdit(const QString& init)
{
	ui.comboBox->hide();
	ui.checkBox->hide();

	ui.lineEdit->setText(init);
	ui.lineEdit->installEventFilter(this);
}

void SKismetInspectorItem::SetComboBox(const QList<QString>& list, QString init)
{
	ui.lineEdit->hide();
	ui.checkBox->hide();

	ui.comboBox->addItems(list);
	ui.comboBox->setCurrentText(init);
	connect(ui.comboBox, &QComboBox::currentTextChanged, this, &SKismetInspectorItem::slotComboBoxChanged, Qt::UniqueConnection);
}

void SKismetInspectorItem::SetCheckBox(bool init)
{
	ui.lineEdit->hide();
	ui.comboBox->hide();

	ui.checkBox->setCheckable(true);
	ui.checkBox->setChecked(init);
	connect(ui.checkBox, &QCheckBox::stateChanged, this, &SKismetInspectorItem::slotCheckBoxChanged, Qt::UniqueConnection);
}

void SKismetInspectorItem::slotComboBoxChanged(const QString& text)
{
	emit sigValueChanged(Guid, TypeDetail, TypeKey, text);
}

void SKismetInspectorItem::slotCheckBoxChanged(int state)
{
	QString sCheck = (state == Qt::CheckState::Unchecked ? "false" : "true");
	emit sigValueChanged(Guid, TypeDetail, TypeKey, sCheck);
}

bool SKismetInspectorItem::eventFilter(QObject* object, QEvent* event)
{
	if (object == ui.lineEdit)
	{
		if (event->type() == QEvent::KeyRelease)
		{
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
			{
				QString newValue = ui.lineEdit->text();
				if (newValue != m_EditorOldValue)
					emit sigValueChanged(Guid, TypeDetail, TypeKey, newValue);
				ui.lineEdit->setText(m_EditorOldValue);
			}
			else if (keyEvent->key() == Qt::Key_Escape)
			{
				ui.lineEdit->setText(m_EditorOldValue);
			}
		}
		else if (event->type() == QEvent::FocusOut)
		{
			QString newValue = ui.lineEdit->text();
			if (newValue != m_EditorOldValue)
				emit sigValueChanged(Guid, TypeDetail, TypeKey, newValue);
			ui.lineEdit->setText(m_EditorOldValue);
		}
		else if (event->type() == QEvent::FocusIn)
		{
			m_EditorOldValue = ui.lineEdit->text();
		}
	}
	return QWidget::eventFilter(object, event);
}
