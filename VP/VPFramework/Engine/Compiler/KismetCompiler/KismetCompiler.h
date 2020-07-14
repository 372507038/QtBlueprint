/*************************************************
Copyright:Ver1.0
Author:Ivy
Date:2020-06-04
Description:���ͼ�ı���ȫ����
**************************************************/

#pragma once

/** KismetCompiler.h -> KismetCompiler.cpp*/

#include "EdGraphCompilerUtilities.h"
#include "Runtime/Blueprint/BlueprintGeneratedClass.h"
#include "Runtime/Blueprint/Blueprint.h"
#include "Runtime/EdGraph/EdGraphNode.h"
#include "Runtime/EdGraph/EdGraphPin.h"

enum class EInternalCompilerFlags:char
{
	None = 0x0,

	PostponeLocalsGenerationUntilPhaseTwo = 0x1,
	PostponeDefaultObjectAssignmentUntilReinstancing = 0x2,
	SkipRefreshExternalBlueprintDependencyNodes = 0x4,
};

class FKismetCompilerContext : public FGraphCompilerContext
{
public:
	FKismetCompilerContext(UBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions);
	virtual ~FKismetCompilerContext();

	/** ������ͼ���಼�� Compile a blueprint into a class and a set of functions */
	void CompileClassLayout(EInternalCompilerFlags InternalFlags);

	/** ����Ĺ�����ͼ-������ɱ������಼�� */
	void CompileFunctions(EInternalCompilerFlags InternalFlags);

	/** ��CDO���ɺ���ã�������仺��/�������� */
	void PostCDOCompiled();

	/** ��һ����ͼ�����һ�����һ�麯�� */
	void Compile();

	/** ���ڷ����������ʹ�õ�����ĺ��� */
	void SetNewClass(UBlueprintGeneratedClass* ClassToUse);

protected:
	// FGraphCompilerContext �ӿ�
	virtual void ValidateLink(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const override;
	virtual void ValidatePin(const UEdGraphPin* Pin) const override;
	virtual void ValidateNode(const UEdGraphNode* Node) const override;
	virtual bool CanIgnoreNode(const UEdGraphNode* Node) const override;

	/** ʹ�������л��������κ��Զ����߼� Gives derived classes a chance to hook up any custom logic */
	virtual void PreCompile() { /*OnPreCompile.Broadcast();*/ } /*Ivy: ί�� todo*/

	/** ȷ�����б����������ڱ���/���Ƶ���Ч���� Ensures that all variables have valid names for compilation/replication */
	void ValidateVariableNames();

	/** ȷ�������������д���Ǹ���ĺϷ���д Ensures that all component class overrides are legal overrides of the parent class */
	void ValidateComponentClassOverrides();

	/** ΪBlueprint NewVars�����е�ÿ����Ŀ����һ������� Creates a class variable for each entry in the Blueprint NewVars array */
	virtual void CreateClassVariablesFromBlueprint();

	/**
	 * ������ɾ�����Ժͺ������Ա��������λ�ô����µ����Ժͺ��� Removes the properties and functions from a class, so that new ones can be created in its place
	 *
	 * @param ClassToClean		The UClass to scrub
	 * @param OldCDO			���þɵ����CDO��������ǿ��Խ������Ը��Ƶ������CDO�� Reference to the old CDO of the class, so we can copy the properties from it to the new class's CDO
	 */
	virtual void CleanAndSanitizeClass(UBlueprintGeneratedClass* ClassToClean, UObject*& OldCDO);

	/**
	 * ����ʵ�ֵĽӿ���Ϣ��ӵ��� Handles adding the implemented interface information to the class
	 */
	virtual void AddInterfacesFromBlueprint(UClass* Class);

	/**
	 * ����Ҫ����ĺ����б� Creates a list of functions to compile
	 */
	virtual void CreateFunctionList();

public:
	typedef FGraphCompilerContext Super;

	UBlueprint* Blueprint;
	UBlueprintGeneratedClass* NewClass;
	UBlueprintGeneratedClass* OldClass;

	/* ��CompileClassLayout/CompileFunctions���ó־û�������: Data that persists across CompileClassLayout/CompileFunctions calls:*/
	UBlueprintGeneratedClass* TargetClass;

	qint64 bIsFullCompile : 1;

protected:
	/** ����ṹ��������ֱ���ѡ�����Ҫִ���ĸ����룬�Ƿ񱣴��м������ȵ� 
	This struct holds the various compilation options, such as which passes to perform, whether to save intermediate results, etc
	*/
	FKismetCompilerOptions CompileOptions;
};

