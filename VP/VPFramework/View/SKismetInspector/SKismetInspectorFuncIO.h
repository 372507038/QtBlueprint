/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:ÏêÇé´°¿Ú
**************************************************/
#pragma once

#include "SKismetInspectorItem.h"
#include "ui_SKismetInspectorFuncIO.h"


class SKismetInspectorFuncIO : public QWidget
{
	Q_OBJECT

public:
	SKismetInspectorFuncIO(QWidget *parent = Q_NULLPTR);
	~SKismetInspectorFuncIO();

	void InitUI(UFunction* func, UVariant* io, EBlueprintItemDetailType detail);

	SKismetInspectorItem* Item();

	FGuid Guid; //Function

signals:
	void sigValueChanged(const FGuid& guid, EBlueprintItemDetailType detail, EBlueprintEditorKey key, const QString& value);
	void sigDelete();
	void sigMoveUp();
	void sigMoveDn();

public slots:
	void slotComboBoxChanged(const QString& text);

private:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	Ui::SKismetInspectorFuncIO ui;
	QString m_EditorOldValue;
};
