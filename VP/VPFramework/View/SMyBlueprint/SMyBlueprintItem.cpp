#include "SMyBlueprintItem.h"


SMyBlueprintItem::SMyBlueprintItem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	SetRenameMode(false);
	ui.editBody->installEventFilter(this);
}

SMyBlueprintItem::~SMyBlueprintItem()
{
}

void SMyBlueprintItem::InitFunc(UFunction* func)
{
	Type = EBlueprintItemType::Function;
	Guid = func->GetObjectGuid();

	ui.labelHead->setText(Script::ToString(func->m_AccessModifiers));
	ui.labelBody->setText(func->GetObjectName());

	QIcon icon("");
	ui.btnIcon->setIcon(icon);
}

void SMyBlueprintItem::InitMember(UVariant* var)
{
	Type = EBlueprintItemType::Member;
	Guid = var->GetObjectGuid();

	QString shead = QString("%1 %2%3")
		.arg(Script::ToString(var->m_AccessModifiers))
		.arg(Script::ToString(var->m_VariantType))
		.arg(Script::ToString(var->m_VariantBoxing));
	ui.labelHead->setText(shead);
	ui.labelBody->setText(var->GetObjectName());

	QIcon icon("");
	ui.btnIcon->setIcon(icon);
}

void SMyBlueprintItem::SetRenameMode(bool re)
{
	ui.labelHead->setVisible(!re);
	ui.labelBody->setVisible(!re);
	ui.editBody->setVisible(re);

	if (re)
	{
		ui.editBody->setFocus();
		ui.editBody->setText(ui.labelBody->text());
	}
}

void SMyBlueprintItem::PopupMenu()
{
	QMenu* menu = new QMenu(this);
	menu->setAttribute(Qt::WA_DeleteOnClose);
	{
		QAction* actRename = new QAction("Rename");
		connect(actRename, &QAction::triggered, this, &SMyBlueprintItem::slotActionRename, Qt::UniqueConnection);
		menu->addAction(actRename);
	}
	{
		QAction* actDelete = new QAction("Delete");
		connect(actDelete, &QAction::triggered, this, &SMyBlueprintItem::slotActionDelete, Qt::UniqueConnection);
		menu->addAction(actDelete);
	}
	menu->exec(QCursor::pos());
}

void SMyBlueprintItem::slotActionRename()
{
	SetRenameMode(true);
}

void SMyBlueprintItem::slotActionDelete()
{
	emit sigDelete();
}

bool SMyBlueprintItem::eventFilter(QObject* object, QEvent* event)
{
	if (object == ui.editBody)
	{
		if (event->type() == QEvent::KeyRelease)
		{
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
			{
				QString newName = ui.editBody->text();
				SetRenameMode(false);
				emit sigRename(newName);
				return true;
			}
			else if (keyEvent->key() == Qt::Key_Escape)
			{
				SetRenameMode(false);
			}
		}
		else if (event->type() == QEvent::FocusOut)
		{
			QString newName = ui.editBody->text();
			SetRenameMode(false);
			emit sigRename(newName);
			return true;
		}
	}
	return QWidget::eventFilter(object, event);
}

void SMyBlueprintItem::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::RightButton)
	{
		QTimer::singleShot(1, this, [this]() 
		{
			PopupMenu();
		});
	}
	QWidget::mousePressEvent(e);
}
