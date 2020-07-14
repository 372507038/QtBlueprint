/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:��ͼ����
**************************************************/
#pragma once

#include "Runtime/Core/ObjectPool.h"
#include "Runtime/Core/Archive.h"
#include "Runtime/Blueprint/Blueprint.h"
#include "Runtime/Blueprint/BlueprintFactories.h"
#include "Editor/SMyBlueprint/SMyBlueprint.h"
#include "Editor/SKismetInspector/SKismetInspector.h"
#include "Editor/SSCSEditor/SSCSEditor.h"
#include "Editor/SCompiler/SCompiler.h"
#include "Editor/SCompilerResults/SCompilerResults.h"
#include <QMainWindow>
#include <QDockWidget>
#include <QCloseEvent>


class BlueprintEditor : public QObject
{
	Q_OBJECT

public:
	BlueprintEditor();
	virtual ~BlueprintEditor();

	void Init(const QString &FileName);
	QMainWindow* GetMainWindow();

protected:
	/// virtual
	virtual QString BlueprintName();	//��ǰ��ͼ������Ĭ��ʹ��bp�ļ�·����MD5��
	virtual QString BlueprintType();	//��ǰ��ͼ����
	virtual UBlueprint* CreateBlueprint(const QString& name);	//����Blueprint
	virtual IArchiveCreateObject GetIArchiveCreateObject();		//����Object�Ľӿ�
	/// virtual

private:
	void RegisterMetaType();

	/// Model
	void InitModel();
	/// Model

	/// View
	void InitView();
	void RefreshView();
	void ReloadView();
	/// View

	void InitSMyBlueprint();
	void RefreshSMyBlueprint();
	void ReloadSMyBlueprint();

	void InitSSCSEditor();
	void RefreshSSCSEditor();
	void ReloadSSCSEditor();

	void InitSKismetInspector();
	void RefreshSKismetInspector();
	void ReloadSKismetInspector();

	void InitSCompiler();
	void RefreshSCompiler();
	void ReloadSCompiler();

	void InitSCompilerResults();
	void RefreshSCompilerResults();
	void ReloadSCompilerResults();

private:
	UClass* GetCurUClass();
	QList<UEdGraph*> GetCurGraphs();
	QList<UFunction*> GetCurFuncs();
	QList<UVariant*> GetCurMembers();

	void SetChanged(bool bChange); //�޸����ݺ���Ҫ�ֶ�����

	bool CheckFuncNameValid(const QString& funcName); //���func�����Ƿ�Ϸ�
	bool CheckVariantNameValid(const QString& variantName); //���Variant�����Ƿ�Ϸ�

public slots:
	/// Model
	void slotSaveArchive();	//����Pool�е�UObject���ݵ����ش浵�ļ�
	void slotLoadArchive(); //�ӱ��ش浵�ж�ȡUObject��Pool��
	/// Model

	/// View MyBlueprint
	void slotMyBlueprintModifiersClicked(EBlueprintItemType type);
	void slotMyBlueprintAddClicked(EBlueprintItemType type);
	void slotMyBlueprintRename(const FGuid& guid, EBlueprintItemType type, QString newName);
	void slotMyBlueprintDelete(const FGuid& guid, EBlueprintItemType type);
	void slotMyBlueprintItemClicked(const FGuid& guid, EBlueprintItemType type);
	void slotMyBlueprintItemDoubleClicked(const FGuid& guid, EBlueprintItemType type);
	/// View MyBlueprint

	/// View KismetInspector
	void slotInspectorValueChanged(const FGuid& guid, EBlueprintItemDetailType detail, EBlueprintEditorKey key, const QString& value);
	void slotInspectorAddClicked(const FGuid& guid, EBlueprintItemType type, EBlueprintItemDetailType detail);
	void slotInspectorDelete(const FGuid& funcGuid, const FGuid& ioGuid, EBlueprintItemType type, EBlueprintItemDetailType detail);
	void slotInspectorMoveUp(const FGuid& funcGuid, const FGuid& ioGuid, EBlueprintItemType type, EBlueprintItemDetailType detail);
	void slotInspectorMoveDn(const FGuid& funcGuid, const FGuid& ioGuid, EBlueprintItemType type, EBlueprintItemDetailType detail);
	/// View KismetInspector

private:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	/// Model
	FArchive m_Archive;
	UBlueprint* m_Blueprint = nullptr;
	/// Model

	/// View
	QMainWindow* m_MainWindow = nullptr;
	SMyBlueprint* m_MyBlueprint = nullptr;
	SSCSEditor* m_SCSEditor = nullptr;
	SKismetInspector* m_KismetInspector = nullptr;
	SCompiler* m_Compiler = nullptr;
	SCompilerResults* m_CompilerResults = nullptr;
	/// View

private:
	bool m_bNoSave = false; //�޸����ݺ���Ҫ�ֶ�����

	EBlueprintItemType m_MyBlueprintSelType = EBlueprintItemType::None;		//��ǰѡ�е�item
	FGuid m_MyBlueprintCurSelGuid;											//��ǰ���ѡ�е�item
	FGuid m_MyBlueprintCurDblGuid;											//��ǰ˫��ѡ�е�item

};




