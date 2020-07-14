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

/** ��һ����ͼ�����һ�����һ�麯�� Compile a blueprint into a class and a set of functions */
void FKismetCompilerContext::CompileClassLayout(EInternalCompilerFlags InternalFlags)
{
	PreCompile();

	// Interfaces only need function signatures, so we only need to perform the first phase of compilation for them
	//bIsFullCompile = CompileOptions.DoesRequireBytecodeGeneration() && (Blueprint->BlueprintType != BPTYPE_Interface);

	//UClass* TargetUClass = Blueprint->GeneratedClass;

	/* ���ڵ���֤ Early validation*/
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

#pragma region /*������:Ĭ��û�и�������*/
	// ȷ����Ա����������Ч�ģ������븸��û�г�ͻ Ensure that member variable names are valid and that there are no collisions with a parent class
	// ������֤��ҪCDO���� This validation requires CDO object.
	//ValidateVariableNames();

	//ValidateComponentClassOverrides();
#pragma endregion

	//CleanAndSanitizeClass(TargetClass, OldCDO);

	{
		/**  ����ĵ��ÿ��ܻ������ͼ����ģ�������֪����Щ�����ո�������BP,����������ϵ��Ȼ���Ա���Ϊ�ǡ����µġ�
			the following calls may mark the blueprint as dirty, but we know that these operations just cleaned up the BP 
		    so dependencies can still be considered 'up to date'
		*/
		//TGuardValue<bool> LockDependenciesUpToDate(Blueprint->bCachedDependenciesUpToDate, Blueprint->bCachedDependenciesUpToDate);

		// ȷ�������ͼ�����µĹ������ĸ����� Make sure that this blueprint is up-to-date with regards to its parent functions
		FBlueprintEditorUtils::ConformCallsToParentFunctions(Blueprint);

		// ��ѭ�˴�ʵ�ֵ��¼�����ȷ�������¸����������Զ����¼� Conform implemented events here, to ensure we generate custom events if necessary after reparenting
		FBlueprintEditorUtils::ConformImplementedEvents(Blueprint);

		// ��ѭ�˴�ʵ�ֵĽӿڣ���ȷ���������ɽӿ���Ϊ�����������й��� Conform implemented interfaces here, to ensure we generate all functions required by the interface as stubs
		FBlueprintEditorUtils::ConformImplementedInterfaces(Blueprint);
	}

	// ���������ඨ��ı�����ע������ Run thru the class defined variables first, get them registered
	CreateClassVariablesFromBlueprint();

	// ����ͼʵ�ֵ��κνӿ���ӵ����� Add any interfaces that the blueprint implements to the class
	// ������CreateFunctionList()����֤pin����֮ǰ�������Ա����ǿ�����֤self/interface pin (has to happen before we validate pin links in CreateFunctionList(), so that we can verify self/interface pins)
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
	// ȷ������ȷʵ��һЩ�ӿ�Ҫʵ�� Make sure we actually have some interfaces to implement
	if (Blueprint->ImplementedInterfaces.size() == 0)
	{
		return;
	}

	// ��������ʵ�ֵĽӿڣ�����������ӵ����� Iterate over all implemented interfaces, and add them to the class
	for (qint64 i = 0; i < Blueprint->ImplementedInterfaces.size(); i++)
	{
		//UClass* Interface = Blueprint->ImplementedInterfaces[i].Interface;
		//if (Interface)
		//{
		//	// ȷ������һ����Ч�Ľӿ� Make sure it's a valid interface
		//	if (Interface->HasAnyClassFlags(CLASS_Interface))
		//	{
		//		//�����ɼ̳е����־ propogate the inheritable ClassFlags
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
