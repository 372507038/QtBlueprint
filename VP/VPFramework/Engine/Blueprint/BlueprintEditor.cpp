#include "BlueprintEditor.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QMessageBox>

BlueprintEditor::BlueprintEditor()
{
	RegisterMetaType();
}

BlueprintEditor::~BlueprintEditor()
{
}

void BlueprintEditor::Init(const QString &FileName)
{
	m_Archive.setFileName(FileName);

	InitModel();
	InitView();
}

QMainWindow* BlueprintEditor::GetMainWindow()
{
	return m_MainWindow;
}

/// virtual
QString BlueprintEditor::BlueprintName()
{
	QString unique = m_Archive.fileName();
	QString md5 = QCryptographicHash::hash(unique.toLocal8Bit(), QCryptographicHash::Md5).toHex();
	return (md5);
}

/// virtual
QString BlueprintEditor::BlueprintType()
{
	return QString(typeid(UBlueprint).name());
}

/// virtual
UBlueprint* BlueprintEditor::CreateBlueprint(const QString& name)
{
	return UBlueprintFactories::CreateBlueprint(name);
}

/// virtual
IArchiveCreateObject BlueprintEditor::GetIArchiveCreateObject()
{
	return UObjectFactory::CreateObject;
}

void BlueprintEditor::RegisterMetaType()
{
	qRegisterMetaType<FGuid>("FGuid");

	qRegisterMetaType<EBlueprintItemType>("EBlueprintItemType");
	qRegisterMetaType<EBlueprintItemDetailType>("EBlueprintItemDetailType");
	qRegisterMetaType<EBlueprintEditorKey>("EBlueprintEditorKey");
}

void BlueprintEditor::InitModel()
{
	if (!m_Archive.exists())
	{
		//当文件不存在时，创建蓝图文件后启动
		m_Blueprint = CreateBlueprint(BlueprintName());
		//重要:创建后的蓝图文件需要保存本地
		slotSaveArchive();
	}
	else
	{
		//当文件存在时，读取蓝图文件后启动
		slotLoadArchive();
		//获取蓝图对象
		m_Blueprint = dynamic_cast<UBlueprint*>(UObjectManager::GetPool(BlueprintName()).Find(BlueprintType()));
		Q_ASSERT(m_Blueprint != nullptr);

		//文件可能移动了路径，修改蓝图的name
		if (m_Blueprint->GetObjectName() != BlueprintName())
		{
			m_Blueprint->SetObjectName(BlueprintName());
		}
	}
}

void BlueprintEditor::InitView()
{
	m_MainWindow = new QMainWindow();
	this->setParent(m_MainWindow); //随窗口一起退出
	m_MainWindow->installEventFilter(this);

	m_MyBlueprint = new SMyBlueprint();
	m_SCSEditor = new SSCSEditor();
	m_KismetInspector = new SKismetInspector();
	m_Compiler = new SCompiler();
	m_CompilerResults = new SCompilerResults();

	//创建DockWidget
	auto createDockWidget = [](QMainWindow* parent, QWidget* child)
	{
		QDockWidget* dock = new QDockWidget(parent);
		dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
		dock->setAllowedAreas(Qt::AllDockWidgetAreas);
		dock->setWindowTitle(child->metaObject()->className());
		dock->setWidget(child);
		dock->setSizePolicy(child->sizePolicy());
		return dock;
	};

	QDockWidget* dockMyBlueprint     = createDockWidget(m_MainWindow, m_MyBlueprint);
	QDockWidget* dockKismetInspector = createDockWidget(m_MainWindow, m_KismetInspector);
	QDockWidget* dockSCSEditor       = createDockWidget(m_MainWindow, m_SCSEditor);
	QDockWidget* dockComplier        = createDockWidget(m_MainWindow, m_Compiler);
	QDockWidget* dockComplierResults = createDockWidget(m_MainWindow, m_CompilerResults);

	m_MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockMyBlueprint);
	m_MainWindow->splitDockWidget(dockMyBlueprint, dockComplier, Qt::Horizontal);
	m_MainWindow->splitDockWidget(dockComplier, dockKismetInspector, Qt::Horizontal);
	m_MainWindow->splitDockWidget(dockComplier, dockSCSEditor, Qt::Vertical);
	m_MainWindow->splitDockWidget(dockSCSEditor, dockComplierResults, Qt::Vertical);

	dockComplierResults->hide();

	InitSMyBlueprint();
	InitSSCSEditor();
	InitSKismetInspector();
	InitSCompiler();
	InitSCompilerResults();
}

void BlueprintEditor::RefreshView()
{
	RefreshSMyBlueprint();
	RefreshSSCSEditor();
	RefreshSKismetInspector();
	RefreshSCompiler();
	RefreshSCompilerResults();
}

void BlueprintEditor::ReloadView()
{
	ReloadSMyBlueprint();
	ReloadSSCSEditor();
	ReloadSKismetInspector();
	ReloadSCompiler();
	ReloadSCompilerResults();
}

void BlueprintEditor::InitSMyBlueprint()
{
	ReloadSMyBlueprint();

	connect(m_MyBlueprint, &SMyBlueprint::sigModifiersClicked, this, &BlueprintEditor::slotMyBlueprintModifiersClicked,
		Qt::ConnectionType(Qt::UniqueConnection | Qt::QueuedConnection));
	connect(m_MyBlueprint, &SMyBlueprint::sigAddClicked, this, &BlueprintEditor::slotMyBlueprintAddClicked,
		Qt::ConnectionType(Qt::UniqueConnection | Qt::QueuedConnection));
	connect(m_MyBlueprint, &SMyBlueprint::sigRename, this, &BlueprintEditor::slotMyBlueprintRename,
		Qt::ConnectionType(Qt::UniqueConnection | Qt::QueuedConnection));
	connect(m_MyBlueprint, &SMyBlueprint::sigDelete, this, &BlueprintEditor::slotMyBlueprintDelete,
		Qt::ConnectionType(Qt::UniqueConnection | Qt::QueuedConnection));
	connect(m_MyBlueprint, &SMyBlueprint::sigItemClicked, this, &BlueprintEditor::slotMyBlueprintItemClicked,
		Qt::ConnectionType(Qt::UniqueConnection | Qt::QueuedConnection));
	connect(m_MyBlueprint, &SMyBlueprint::sigItemDoubleClicked, this, &BlueprintEditor::slotMyBlueprintItemDoubleClicked,
		Qt::ConnectionType(Qt::UniqueConnection | Qt::QueuedConnection));
}

void BlueprintEditor::RefreshSMyBlueprint()
{
	m_MyBlueprint->RefreshUI(GetCurUClass(), GetCurFuncs(), GetCurMembers());
}

void BlueprintEditor::ReloadSMyBlueprint()
{
	m_MyBlueprint->ClearUI();
	m_MyBlueprint->InitUI(GetCurUClass(), GetCurFuncs(), GetCurMembers());
}

void BlueprintEditor::InitSSCSEditor()
{
	//测试代码
	m_SCSEditor->InitUI();
}

void BlueprintEditor::RefreshSSCSEditor()
{
}

void BlueprintEditor::ReloadSSCSEditor()
{
}

void BlueprintEditor::InitSKismetInspector()
{
	ReloadSKismetInspector();

	connect(m_KismetInspector, &SKismetInspector::sigInspectorValueChanged, this, &BlueprintEditor::slotInspectorValueChanged,
		Qt::ConnectionType(Qt::UniqueConnection | Qt::QueuedConnection));
	connect(m_KismetInspector, &SKismetInspector::sigInspectorAddClicked, this, &BlueprintEditor::slotInspectorAddClicked,
		Qt::ConnectionType(Qt::UniqueConnection | Qt::QueuedConnection));
	connect(m_KismetInspector, &SKismetInspector::sigInspectorDelete, this, &BlueprintEditor::slotInspectorDelete,
		Qt::ConnectionType(Qt::UniqueConnection | Qt::QueuedConnection));
	connect(m_KismetInspector, &SKismetInspector::sigInspectorMoveUp, this, &BlueprintEditor::slotInspectorMoveUp,
		Qt::ConnectionType(Qt::UniqueConnection | Qt::QueuedConnection));
	connect(m_KismetInspector, &SKismetInspector::sigInspectorMoveDn, this, &BlueprintEditor::slotInspectorMoveDn,
		Qt::ConnectionType(Qt::UniqueConnection | Qt::QueuedConnection));
}

void BlueprintEditor::RefreshSKismetInspector()
{
	ReloadSKismetInspector();
}

void BlueprintEditor::ReloadSKismetInspector()
{
	m_KismetInspector->ClearUI();

	if (m_MyBlueprintSelType != EBlueprintItemType::None && !m_MyBlueprintCurSelGuid.IsValid())
		return;

	switch (m_MyBlueprintSelType)
	{
	case EBlueprintItemType::Function:
	{
		UFunction* func = VPPOOL_FIND(m_Blueprint, m_MyBlueprintCurSelGuid, class UFunction);
		QList<UVariant*> inputs, outputs;
		for (auto guidInput : func->m_Inputs)
		{
			UVariant* var = VPPOOL_FIND(m_Blueprint, guidInput, class UVariant);
			inputs.append(var);
		}
		for (auto guidOutput : func->m_Outputs)
		{
			UVariant* var = VPPOOL_FIND(m_Blueprint, guidOutput, class UVariant);
			outputs.append(var);
		}
		m_KismetInspector->InitUI(func, inputs, outputs);
	}
	break;
	case EBlueprintItemType::Member:
	{
		UVariant* var = VPPOOL_FIND(m_Blueprint, m_MyBlueprintCurSelGuid, class UVariant);
		m_KismetInspector->InitUI(var);
	}
	break;
	}
}

void BlueprintEditor::InitSCompiler()
{
}

void BlueprintEditor::RefreshSCompiler()
{
}

void BlueprintEditor::ReloadSCompiler()
{
}

void BlueprintEditor::InitSCompilerResults()
{
}

void BlueprintEditor::RefreshSCompilerResults()
{
}

void BlueprintEditor::ReloadSCompilerResults()
{
}

UClass* BlueprintEditor::GetCurUClass()
{
	UClass* curClass = VPPOOL_FIND(m_Blueprint, m_Blueprint->m_Class, class UClass);
	return curClass;
}

QList<UEdGraph*> BlueprintEditor::GetCurGraphs()
{
	QList<UEdGraph*> graphs;
	for (const auto& guidGraph : m_Blueprint->m_Graphs)
	{
		UEdGraph* graph = VPPOOL_FIND(m_Blueprint, guidGraph, class UEdGraph);
		graphs.append(graph);
	}
	return graphs;
}

QList<UFunction*> BlueprintEditor::GetCurFuncs()
{
	QList<UFunction*> funcs;
	for (const auto& guidFunc : GetCurUClass()->m_Functions)
	{
		UFunction* func = VPPOOL_FIND(m_Blueprint, guidFunc, class UFunction);
		funcs.append(func);
	}
	return funcs;
}

QList<UVariant*> BlueprintEditor::GetCurMembers()
{
	QList<UVariant*> vars;
	for (const auto& guidVar : GetCurUClass()->m_Members)
	{
		UVariant* var = VPPOOL_FIND(m_Blueprint, guidVar, class UVariant);
		vars.append(var);
	}
	return vars;
}

void BlueprintEditor::SetChanged(bool bChange)
{
	if (m_MainWindow)
	{
		if (bChange)
		{
			if (!m_bNoSave)
			{
				QString title = m_MainWindow->windowTitle();
				m_MainWindow->setWindowTitle(title + " *");
			}
		}
		else
		{
			QString title = m_MainWindow->windowTitle();
			if (title.endsWith(" *"))
			{
				m_MainWindow->setWindowTitle(title.left(title.count() - 2));
			}
		}
	}
	m_bNoSave = bChange;
}

bool BlueprintEditor::CheckFuncNameValid(const QString& name)
{
	if (name.isEmpty())
		return false;
	if (!name[0].isLetter()) //首字母
		return false;
	for (int idx = 1; idx < name.count(); idx++) //字母、数字、下划线
	{
		QChar c = name[idx];
		if (c.isLetterOrNumber())
			continue;
		if (c == '-' || c == '_')
			continue;
		return false;
	}
	return true;
}

bool BlueprintEditor::CheckVariantNameValid(const QString& name)
{
	if (name.isEmpty())
		return false;
	if (!name[0].isLetter()) //首字母
		return false;
	for (int idx = 1; idx < name.count(); idx++) //字母、数字、下划线
	{
		QChar c = name[idx];
		if (c.isLetterOrNumber())
			continue;
		if (c == '-' || c == '_')
			continue;
		return false;
	}
	return true;
}

void BlueprintEditor::slotSaveArchive()
{
	m_Archive.SaveObjects(VPPOOL(BlueprintName()).Get());
	SetChanged(false);
}

void BlueprintEditor::slotLoadArchive()
{
	QList<UObject*> Objects;
	m_Archive.LoadObjects(Objects, GetIArchiveCreateObject());
	VPPOOL(BlueprintName()).Add(Objects);
}

void BlueprintEditor::slotMyBlueprintModifiersClicked(EBlueprintItemType type)
{
	//todo
}

void BlueprintEditor::slotMyBlueprintAddClicked(EBlueprintItemType type)
{
	switch (type)
	{
	case EBlueprintItemType::Function:
	{
		UFunction* newFunc = VPNEW_UFunction(m_Blueprint);
		newFunc->SetObjectName("newFunction");
		newFunc->m_AccessModifiers = EAccessSpecifier::Private;
		newFunc->m_Modifiers = EFieldModifiers::Normal;
		GetCurUClass()->m_Functions.append(newFunc->GetObjectGuid());
	}break;

	case EBlueprintItemType::Member:
	{
		UVariant* newVar = VPNEW_UVariant(m_Blueprint);
		newVar->SetObjectName("newVariant");
		newVar->m_AccessModifiers = EAccessSpecifier::Private;
		newVar->m_Modifiers = EFieldModifiers::Normal;
		newVar->m_VariantBoxing = EVariantBoxing::Copy;
		newVar->m_VariantType = EVariantType::String;
		GetCurUClass()->m_Members.append(newVar->GetObjectGuid());
	}break;
	}

	ReloadView();
	SetChanged(true);
}

void BlueprintEditor::slotMyBlueprintRename(const FGuid& guid, EBlueprintItemType type, QString newName)
{
	if (!CheckFuncNameValid(newName))
		return;

	switch (type)
	{
	case EBlueprintItemType::Function:
	{
		UFunction* func = VPPOOL_FIND(m_Blueprint, guid, class UFunction);
		func->SetObjectName(newName);
		RefreshView();
		SetChanged(true);
	} 
	break;
	case EBlueprintItemType::Member:
	{
		UVariant* var = VPPOOL_FIND(m_Blueprint, guid, class UVariant);
		var->SetObjectName(newName);
		RefreshView();
		SetChanged(true);
	} 
	break;
	}
}

void BlueprintEditor::slotMyBlueprintDelete(const FGuid& guid, EBlueprintItemType type)
{
	if (m_MyBlueprintCurSelGuid == guid)
	{
		m_MyBlueprintSelType = EBlueprintItemType::None;
		m_MyBlueprintCurSelGuid = m_MyBlueprintCurDblGuid = FGuid();
	}

	switch (type)
	{
	case EBlueprintItemType::Function:
	{
		GetCurUClass()->m_Functions.removeOne(guid);
		VPPOOL(m_Blueprint).Delete(guid);
		ReloadView();
		SetChanged(true);
	}
	break;
	case EBlueprintItemType::Member:
	{
		GetCurUClass()->m_Members.removeOne(guid);
		VPPOOL(m_Blueprint).Delete(guid);
		ReloadView();
		SetChanged(true);
	}
	break;
	}
}

void BlueprintEditor::slotMyBlueprintItemClicked(const FGuid& guid, EBlueprintItemType type)
{
	if (m_MyBlueprintCurSelGuid == guid)
		return;

	m_MyBlueprintSelType = type;
	m_MyBlueprintCurSelGuid = guid;

	RefreshSKismetInspector();
}

void BlueprintEditor::slotMyBlueprintItemDoubleClicked(const FGuid& guid, EBlueprintItemType type)
{
	if (m_MyBlueprintCurDblGuid == guid)
		return;

	m_MyBlueprintSelType = type;
	m_MyBlueprintCurDblGuid = guid;

	RefreshSSCSEditor();
}

void BlueprintEditor::slotInspectorValueChanged(const FGuid& guid, EBlueprintItemDetailType detail, EBlueprintEditorKey key, const QString& value)
{
	switch (detail)
	{
	case EBlueprintItemDetailType::Function:
	{
		UFunction* func = VPPOOL_FIND(m_Blueprint, guid, class UFunction);
		EFunctionAbstraction eAbstraction;
		EFieldModifiers eModifiers;
		EAccessSpecifier eAccess;
		switch (key)
		{
		case EBlueprintEditorKey::FunctionName:
			if (CheckFuncNameValid(value))
			{
				func->SetObjectName(value);
			}
			break;

		case EBlueprintEditorKey::EFunctionAbstraction:
			eAbstraction = Script::ToEnum(value, eAbstraction);
			func->m_FunctionAbstraction = eAbstraction;
			break;

		case EBlueprintEditorKey::EFieldModifiers:
			eModifiers = Script::ToEnum(value, eModifiers);
			func->m_Modifiers = eModifiers;
			break;

		case EBlueprintEditorKey::EAccessSpecifier:
			eAccess = Script::ToEnum(value, eAccess);
			func->m_AccessModifiers = eAccess;
			break;
		}
	}break;

	case EBlueprintItemDetailType::Input:
	case EBlueprintItemDetailType::Output:
	case EBlueprintItemDetailType::Variable:
	case EBlueprintItemDetailType::DefaultValue:
	{
		UVariant* var = VPPOOL_FIND(m_Blueprint, guid, class UVariant);
		EVariantType eVarType;
		switch (key)
		{
		case EBlueprintEditorKey::VariableName:
			if (CheckVariantNameValid(value))
				var->SetObjectName(value);
			break;

		case EBlueprintEditorKey::VariableType:
			eVarType = Script::ToEnum(value, eVarType);
			var->m_VariantType = eVarType;
			break;

		case EBlueprintEditorKey::DefaultValue:
			var->m_DefaultValue = value;
			break;
		}
	}break;
	}

	RefreshView();
	SetChanged(true);
}

void BlueprintEditor::slotInspectorAddClicked(const FGuid& guid, EBlueprintItemType type, EBlueprintItemDetailType detail)
{
	if(type == EBlueprintItemType::Function)
	{
		Q_ASSERT(detail == EBlueprintItemDetailType::Input || detail == EBlueprintItemDetailType::Output);
		UFunction* func = VPPOOL_FIND(m_Blueprint, guid, class UFunction);
		UVariant* newVar = VPNEW_UVariant(m_Blueprint);
		newVar->m_AccessModifiers = EAccessSpecifier::Private;
		newVar->m_Modifiers = EFieldModifiers::Normal;
		newVar->m_VariantBoxing = EVariantBoxing::Copy;
		newVar->m_VariantType = EVariantType::String;

		if (detail == EBlueprintItemDetailType::Input)
		{
			newVar->SetObjectName("newInput");
			func->m_Inputs.append(newVar->GetObjectGuid());
		}
		else if (detail == EBlueprintItemDetailType::Output)
		{
			newVar->SetObjectName("newOutput");
			func->m_Outputs.append(newVar->GetObjectGuid());
		}
	}

	ReloadSKismetInspector();
	SetChanged(true);
}

void BlueprintEditor::slotInspectorDelete(const FGuid& funcGuid, const FGuid& ioGuid, EBlueprintItemType type, EBlueprintItemDetailType detail)
{
	if (type == EBlueprintItemType::Function)
	{
		UFunction* func = VPPOOL_FIND(m_Blueprint, funcGuid, class UFunction);

		if (detail == EBlueprintItemDetailType::Input)
		{
			Q_ASSERT(func->m_Inputs.contains(ioGuid));
			func->m_Inputs.removeOne(ioGuid);
			VPPOOL(m_Blueprint).Delete(ioGuid);
		}
		else if (detail == EBlueprintItemDetailType::Output)
		{
			Q_ASSERT(func->m_Outputs.contains(ioGuid));
			func->m_Outputs.removeOne(ioGuid);
			VPPOOL(m_Blueprint).Delete(ioGuid);
		}
	}

	ReloadSKismetInspector();
	SetChanged(true);
}

void BlueprintEditor::slotInspectorMoveUp(const FGuid& funcGuid, const FGuid& ioGuid, EBlueprintItemType type, EBlueprintItemDetailType detail)
{
	if (type == EBlueprintItemType::Function)
	{
		UFunction* func = VPPOOL_FIND(m_Blueprint, funcGuid, class UFunction);

		if (detail == EBlueprintItemDetailType::Input)
		{
			Q_ASSERT(func->m_Inputs.contains(ioGuid));
			int idx = func->m_Inputs.indexOf(ioGuid);
			if (idx > 0)
				func->m_Inputs.move(idx, idx - 1);
		}
		else if (detail == EBlueprintItemDetailType::Output)
		{
			Q_ASSERT(func->m_Outputs.contains(ioGuid));
			int idx = func->m_Outputs.indexOf(ioGuid);
			if (idx > 0)
				func->m_Outputs.move(idx, idx - 1);
		}
	}

	ReloadSKismetInspector();
	SetChanged(true);
}

void BlueprintEditor::slotInspectorMoveDn(const FGuid& funcGuid, const FGuid& ioGuid, EBlueprintItemType type, EBlueprintItemDetailType detail)
{
	if (type == EBlueprintItemType::Function)
	{
		UFunction* func = VPPOOL_FIND(m_Blueprint, funcGuid, class UFunction);

		if (detail == EBlueprintItemDetailType::Input)
		{
			Q_ASSERT(func->m_Inputs.contains(ioGuid));
			int idx = func->m_Inputs.indexOf(ioGuid);
			if (idx < func->m_Inputs.count() - 1)
				func->m_Inputs.move(idx, idx + 1);
		}
		else if (detail == EBlueprintItemDetailType::Output)
		{
			Q_ASSERT(func->m_Outputs.contains(ioGuid));
			int idx = func->m_Outputs.indexOf(ioGuid);
			if (idx < func->m_Outputs.count() - 1)
				func->m_Outputs.move(idx, idx + 1);
		}
	}

	ReloadSKismetInspector();
	SetChanged(true);
}

bool BlueprintEditor::eventFilter(QObject* object, QEvent* event)
{
	if (object == m_MainWindow)
	{
		if (event->type() == QEvent::Close && m_bNoSave)
		{
			QMessageBox msgBox;
			msgBox.setText("The document has been modified.");
			msgBox.setInformativeText("Do you want to save your changes?");
			msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
			msgBox.setDefaultButton(QMessageBox::Save);
			int ret = msgBox.exec();
			switch (ret) 
			{
			case QMessageBox::Save:
				slotSaveArchive();
				break;
			case QMessageBox::Cancel:
				event->ignore();
				return true;
			}
		}
	}
	return QObject::eventFilter(object, event);
}

