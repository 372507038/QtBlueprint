#include "SKismetInspectorFuncIO.h"


SKismetInspectorFuncIO::SKismetInspectorFuncIO(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.editName->installEventFilter(this);
	connect(ui.cbValueType, &QComboBox::currentTextChanged, this, &SKismetInspectorFuncIO::slotComboBoxChanged, Qt::UniqueConnection);
	connect(ui.btnDelete, &QAbstractButton::clicked, this, &SKismetInspectorFuncIO::sigDelete, Qt::UniqueConnection);
	connect(ui.btnUp, &QAbstractButton::clicked, this, &SKismetInspectorFuncIO::sigMoveUp, Qt::UniqueConnection);
	connect(ui.btnDown, &QAbstractButton::clicked, this, &SKismetInspectorFuncIO::sigMoveDn, Qt::UniqueConnection);
}

SKismetInspectorFuncIO::~SKismetInspectorFuncIO()
{
}

void SKismetInspectorFuncIO::InitUI(UFunction* func, UVariant* io, EBlueprintItemDetailType detail)
{
	Guid = func->GetObjectGuid();

	ui.editName->setText(io->GetObjectName());
	QStringList typeList = {
		Script::ToString(EVariantType::Bool),
		Script::ToString(EVariantType::Int),
		Script::ToString(EVariantType::Double),
		Script::ToString(EVariantType::String),
		Script::ToString(EVariantType::Class),
		Script::ToString(EVariantType::Enum),
	};
	ui.cbValueType->addItems(typeList);
	ui.cbValueType->setCurrentText(Script::ToString(io->m_VariantType));

	Item()->InitFuncIO(func, io, detail, EBlueprintEditorKey::DefaultValue);
	Item()->SetName("Default Value");

	if (io->m_VariantType == EVariantType::Bool)
	{
		Item()->SetCheckBox(io->m_DefaultValue != "0");
	}
	else if (io->m_VariantType == EVariantType::Class || io->m_VariantType == EVariantType::Enum)
	{
		//ÔÝ²»Ö§³Ö
		Item()->SetComboBox(QStringList({ io->m_VariantTypeDetail }), io->m_VariantTypeDetail);
	}
	else
	{
		Item()->SetLineEdit(io->m_DefaultValue);
	}
}

SKismetInspectorItem* SKismetInspectorFuncIO::Item()
{
	return ui.widget;
}

void SKismetInspectorFuncIO::slotComboBoxChanged(const QString& text)
{
	emit sigValueChanged(Item()->Guid, Item()->TypeDetail, EBlueprintEditorKey::VariableType, text);
}

bool SKismetInspectorFuncIO::eventFilter(QObject* object, QEvent* event)
{
	if (object == ui.editName)
	{
		if (event->type() == QEvent::KeyRelease)
		{
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
			{
				QString newValue = ui.editName->text();
				if (newValue != m_EditorOldValue)
					emit sigValueChanged(Item()->Guid, Item()->TypeDetail, EBlueprintEditorKey::VariableName, newValue);
				ui.editName->setText(m_EditorOldValue);
			}
			else if (keyEvent->key() == Qt::Key_Escape)
			{
				ui.editName->setText(m_EditorOldValue);
			}
		}
		else if (event->type() == QEvent::FocusOut)
		{
			QString newValue = ui.editName->text();
			if (newValue != m_EditorOldValue)
				emit sigValueChanged(Item()->Guid, Item()->TypeDetail, EBlueprintEditorKey::VariableName, newValue);
			ui.editName->setText(m_EditorOldValue);
		}
		else if (event->type() == QEvent::FocusIn)
		{
			m_EditorOldValue = ui.editName->text();
		}
	}
	return QWidget::eventFilter(object, event);
}
