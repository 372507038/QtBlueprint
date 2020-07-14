/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:ÏêÇé´°¿Ú
**************************************************/
#pragma once

#include "Runtime/Core/Guid.h"
#include "Runtime/Core/Class.h"
#include "Editor/Common/CommEnum.h"
#include "Editor/Common/CommStruct.h"
#include "ui_SKismetInspectorItem.h"
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>


class SKismetInspectorItem : public QWidget
{
	Q_OBJECT

public:
	SKismetInspectorItem(QWidget *parent = Q_NULLPTR);
	~SKismetInspectorItem();

	void InitFunc(UFunction* func, EBlueprintItemDetailType detail, EBlueprintEditorKey key);
	void InitFuncIO(UFunction* func, UVariant *io, EBlueprintItemDetailType detail, EBlueprintEditorKey key);
	void InitMember(UVariant* member, EBlueprintItemDetailType detail, EBlueprintEditorKey key);

	void FuncSetUI(EBlueprintEditorKey key, UFunction* func, UVariant* var = nullptr);
	void MemberSetUI(EBlueprintEditorKey key, UVariant* var);

	void SetName(const QString& name);
	void SetLineEdit(const QString& init);
	void SetComboBox(const QList<QString>& list, QString init);
	void SetCheckBox(bool init);

	EBlueprintItemType Type;
	EBlueprintItemDetailType TypeDetail;
	EBlueprintEditorKey TypeKey;
	FGuid Guid; //Function or Function-IO or Member

signals:
	void sigValueChanged(const FGuid& guid, EBlueprintItemDetailType detail, EBlueprintEditorKey key, const QString& value);

public slots:
	void slotComboBoxChanged(const QString& text);
	void slotCheckBoxChanged(int state);

private:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	Ui::SKismetInspectorItem ui;
	QString m_EditorOldValue;
};
