/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:蓝图控制
**************************************************/
#pragma once

#include "Model/Core/ObjectPool.h"
#include "Model/Core/Archive.h"
#include "Model/Blueprint/Blueprint.h"
#include "Model/Blueprint/BlueprintFactories.h"
#include "View/SMyBlueprint/SMyBlueprint.h"
#include "View/SKismetInspector/SKismetInspector.h"
#include "View/SSCSEditor/SSCSEditor.h"
#include "View/SCompiler/SCompiler.h"
#include "View/SCompilerResults/SCompilerResults.h"
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
	virtual QString BlueprintName();	//当前蓝图命名（默认使用bp文件路径的MD5）
	virtual QString BlueprintType();	//当前蓝图类名
	virtual UBlueprint* CreateBlueprint(const QString& name);	//创建Blueprint
	virtual IArchiveCreateObject GetIArchiveCreateObject();		//创建Object的接口
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

	UClass* GetCurUClass();
	QList<UEdGraph*> GetCurGraphs();
	QList<UFunction*> GetCurFuncs();
	QList<UVariant*> GetCurMembers();

	void SetChanged(bool bChange); //修改内容后需要手动保存

	bool CheckFuncNameValid(const QString& funcName); //检查func名字是否合法
	bool CheckVariantNameValid(const QString& variantName); //检查Variant名字是否合法

public slots:
	/// Model
	void slotSaveArchive();	//保存Pool中的UObject数据到本地存档文件
	void slotLoadArchive(); //从本地存档中读取UObject到Pool中
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

	bool m_bNoSave = false; //修改内容后需要手动保存

	EBlueprintItemType m_SelType = EBlueprintItemType::None;	//当前选中的item
	FGuid m_CurSelGuid;											//当前点击选中的item
	FGuid m_CurDblGuid;											//当前双击选中的item
};




