#include "KismetCompiler.h"

#include "Runtime/Customize/k2EdGraph/K2Node.h"
#include "../Kismet2/BlueprintEditorUtils.h"

FKismetCompilerContext::FKismetCompilerContext(UBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions)
	: FGraphCompilerContext(InMessageLog)
{
}

FKismetCompilerContext::~FKismetCompilerContext()
{
}

/** 将一个蓝图编译成一个类和一组函数 Compile a blueprint into a class and a set of functions */
void FKismetCompilerContext::CompileClassLayout(EInternalCompilerFlags InternalFlags)
{
	PreCompile();

	// Interfaces only need function signatures, so we only need to perform the first phase of compilation for them
	//bIsFullCompile = CompileOptions.DoesRequireBytecodeGeneration() && (Blueprint->BlueprintType != BPTYPE_Interface);

	//UClass* TargetUClass = Blueprint->GeneratedClass;

	/* 早期的验证 Early validation*/
	if (CompileOptions.CompileType == EKismetCompileType::Full)
	{
		QList<UEdGraph*> AllGraphs;
		Blueprint->GetAllGraphs(AllGraphs);
		for (UEdGraph* Graph : AllGraphs)
		{
			if (Graph)
			{
				QList<UK2Node*> AllNodes;
				Graph->GetNodesOfClass(AllNodes);
				for (UK2Node* Node : AllNodes)
				{
					if (Node)
					{
						Node->EarlyValidation(MessageLog);
					}
				}
			}
		}
	}

#pragma region /*先屏蔽:默认没有父类重载*/
	// 确保成员变量名是有效的，并且与父类没有冲突 Ensure that member variable names are valid and that there are no collisions with a parent class
	// 这种验证需要CDO对象 This validation requires CDO object.
	//ValidateVariableNames();

	//ValidateComponentClassOverrides();
#pragma endregion

	//CleanAndSanitizeClass(TargetClass, OldCDO);

	{
		/**  下面的调用可能会表明蓝图是脏的，但我们知道这些操作刚刚清理了BP,所以依赖关系仍然可以被认为是“最新的”
			the following calls may mark the blueprint as dirty, but we know that these operations just cleaned up the BP 
		    so dependencies can still be considered 'up to date'
		*/
		//TGuardValue<bool> LockDependenciesUpToDate(Blueprint->bCachedDependenciesUpToDate, Blueprint->bCachedDependenciesUpToDate);

		// 确保这个蓝图是最新的关于它的父功能 Make sure that this blueprint is up-to-date with regards to its parent functions
		FBlueprintEditorUtils::ConformCallsToParentFunctions(Blueprint);

		// 遵循此处实现的事件，以确保在重新父化后生成自定义事件 Conform implemented events here, to ensure we generate custom events if necessary after reparenting
		FBlueprintEditorUtils::ConformImplementedEvents(Blueprint);

		// 遵循此处实现的接口，以确保我们生成接口作为存根所需的所有功能 Conform implemented interfaces here, to ensure we generate all functions required by the interface as stubs
		FBlueprintEditorUtils::ConformImplementedInterfaces(Blueprint);
	}

	// 首先运行类定义的变量，注册它们 Run thru the class defined variables first, get them registered
	CreateClassVariablesFromBlueprint();

	// 将蓝图实现的任何接口添加到类中 Add any interfaces that the blueprint implements to the class
	// 必须在CreateFunctionList()中验证pin链接之前发生，以便我们可以验证self/interface pin (has to happen before we validate pin links in CreateFunctionList(), so that we can verify self/interface pins)
	//AddInterfacesFromBlueprint(NewClass);

	// Construct a context for each function, doing validation and building the function interface
	CreateFunctionList();
}

void FKismetCompilerContext::CompileFunctions(EInternalCompilerFlags InternalFlags)
{
	//TODO
}

void FKismetCompilerContext::PostCDOCompiled()
{
	//TODO
}

void FKismetCompilerContext::Compile()
{
	CompileClassLayout(EInternalCompilerFlags::None);
	CompileFunctions(EInternalCompilerFlags::None);
}

void FKismetCompilerContext::SetNewClass(UBlueprintGeneratedClass * ClassToUse)
{
	//TODO
}

void FKismetCompilerContext::ValidateLink(const UEdGraphPin * PinA, const UEdGraphPin * PinB) const
{
	//TODO
}

void FKismetCompilerContext::ValidatePin(const UEdGraphPin * Pin) const
{
	//TODO
}

void FKismetCompilerContext::ValidateNode(const UEdGraphNode * Node) const
{
	//TODO
}

bool FKismetCompilerContext::CanIgnoreNode(const UEdGraphNode * Node) const
{
	return false;
}

void FKismetCompilerContext::ValidateVariableNames()
{
	//TODO
}

void FKismetCompilerContext::ValidateComponentClassOverrides()
{
	//TODO
}

void FKismetCompilerContext::CreateClassVariablesFromBlueprint()
{
	//TODO
}

void FKismetCompilerContext::CleanAndSanitizeClass(UBlueprintGeneratedClass * ClassToClean, UObject *& OldCDO)
{
	//TODO
}

void FKismetCompilerContext::AddInterfacesFromBlueprint(UClass * Class)
{
	// 确保我们确实有一些接口要实现 Make sure we actually have some interfaces to implement
	if (Blueprint->ImplementedInterfaces.size() == 0)
	{
		return;
	}

	// 遍历所有实现的接口，并将它们添加到类中 Iterate over all implemented interfaces, and add them to the class
	for (qint64 i = 0; i < Blueprint->ImplementedInterfaces.size(); i++)
	{
		//UClass* Interface = Blueprint->ImplementedInterfaces[i].Interface;
		//if (Interface)
		//{
		//	// 确保它是一个有效的接口 Make sure it's a valid interface
		//	if (Interface->HasAnyClassFlags(CLASS_Interface))
		//	{
		//		//传播可继承的类标志 propogate the inheritable ClassFlags
		//		Class->ClassFlags |= (Interface->ClassFlags) & CLASS_ScriptInherit;

		//		new (Class->Interfaces) FImplementedInterface(Interface, 0, true);
		//	}
		//}
	}
}

void FKismetCompilerContext::CreateFunctionList()
{
	//TODO
}
