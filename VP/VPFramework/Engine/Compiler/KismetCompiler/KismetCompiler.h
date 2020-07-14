/*************************************************
Copyright:Ver1.0
Author:Ivy
Date:2020-06-04
Description:相关图的编译全过程
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

	/** 编译蓝图的类布局 Compile a blueprint into a class and a set of functions */
	void CompileClassLayout(EInternalCompilerFlags InternalFlags);

	/** 编译的功能蓝图-必须完成编译后的类布局 */
	void CompileFunctions(EInternalCompilerFlags InternalFlags);

	/** 在CDO生成后调用，允许分配缓存/派生数据 */
	void PostCDOCompiled();

	/** 将一个蓝图编译成一个类和一组函数 */
	void Compile();

	/** 用于分配编译器将使用的新类的函数 */
	void SetNewClass(UBlueprintGeneratedClass* ClassToUse);

protected:
	// FGraphCompilerContext 接口
	virtual void ValidateLink(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const override;
	virtual void ValidatePin(const UEdGraphPin* Pin) const override;
	virtual void ValidateNode(const UEdGraphNode* Node) const override;
	virtual bool CanIgnoreNode(const UEdGraphNode* Node) const override;

	/** 使派生类有机会连接任何自定义逻辑 Gives derived classes a chance to hook up any custom logic */
	virtual void PreCompile() { /*OnPreCompile.Broadcast();*/ } /*Ivy: 委托 todo*/

	/** 确保所有变量都有用于编译/复制的有效名称 Ensures that all variables have valid names for compilation/replication */
	void ValidateVariableNames();

	/** 确保所有组件类重写都是父类的合法重写 Ensures that all component class overrides are legal overrides of the parent class */
	void ValidateComponentClassOverrides();

	/** 为Blueprint NewVars数组中的每个条目创建一个类变量 Creates a class variable for each entry in the Blueprint NewVars array */
	virtual void CreateClassVariablesFromBlueprint();

	/**
	 * 从类中删除属性和函数，以便可以在其位置创建新的属性和函数 Removes the properties and functions from a class, so that new ones can be created in its place
	 *
	 * @param ClassToClean		The UClass to scrub
	 * @param OldCDO			引用旧的类的CDO，因此我们可以将其属性复制到新类的CDO中 Reference to the old CDO of the class, so we can copy the properties from it to the new class's CDO
	 */
	virtual void CleanAndSanitizeClass(UBlueprintGeneratedClass* ClassToClean, UObject*& OldCDO);

	/**
	 * 处理将实现的接口信息添加到类 Handles adding the implemented interface information to the class
	 */
	virtual void AddInterfacesFromBlueprint(UClass* Class);

	/**
	 * 创建要编译的函数列表 Creates a list of functions to compile
	 */
	virtual void CreateFunctionList();

public:
	typedef FGraphCompilerContext Super;

	UBlueprint* Blueprint;
	UBlueprintGeneratedClass* NewClass;
	UBlueprintGeneratedClass* OldClass;

	/* 跨CompileClassLayout/CompileFunctions调用持久化的数据: Data that persists across CompileClassLayout/CompileFunctions calls:*/
	UBlueprintGeneratedClass* TargetClass;

	qint64 bIsFullCompile : 1;

protected:
	/** 这个结构体包含各种编译选项，比如要执行哪个编译，是否保存中间结果，等等 
	This struct holds the various compilation options, such as which passes to perform, whether to save intermediate results, etc
	*/
	FKismetCompilerOptions CompileOptions;
};

