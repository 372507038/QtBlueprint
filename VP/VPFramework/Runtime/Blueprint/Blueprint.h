/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:蓝图
**************************************************/
#pragma once

#include "Runtime/Core/Object.h"
#include "Runtime/Core/Class.h"
#include "Runtime/EdGraph/EdGraph.h"
#include "../Core/SubclassOf.h"

/**
 * 蓝图是提供基于节点的直观界面的特殊资产，可用于创建新型的Actor和脚本级事件。 
 * Blueprints are special assets that provide an intuitive, node-based interface that can be used to create new types of Actors
 * and script level events; giving designers and gameplay programmers the tools to quickly create and iterate gameplay from
 * within Unreal Editor without ever needing to write a line of code.
 */
class UBlueprint : public UObject
{
	friend class BlueprintEditor;

public:
	UBlueprint();
	UBlueprint(const UObjectInfo& info);
	UBlueprint(QString ObjectType, QString ObjectName);
	UBlueprint(QString name);
	virtual ~UBlueprint();

	/** (Ivy) 指向“最近”完全生成的类的指针 Pointer to the 'most recent' fully generated class */
	//TSubclassOf<class UObject>	GeneratedClass;

public:
	UClassGuid m_Class;
	QList<UEdGraphGuid> m_Graphs;

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar) const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UBlueprint);

	/** (Ivy) 在这个蓝图中找到所有的图表 Get all graphs in this blueprint */
	void GetAllGraphs(QList<UEdGraph*>& Graphs) const;

public:
	/** (Ivy) 关于我们在这个蓝图中实现的接口的信息数组 Array of info about the interfaces we implement in this blueprint */
	QList<struct FBPInterfaceDescription> ImplementedInterfaces;
};
Q_DECLARE_METATYPE(UBlueprint)


#pragma region (Ivy) 编译的类型-编译的选项
/**(Ivy) 编译的类型 Type of compilation. */
namespace EKismetCompileType
{
	enum Type
	{
		SkeletonOnly,
		Full,
		StubAfterFailure,
		BytecodeOnly,
		Cpp,
	};
};

/*Ivy:20200623 编译的选项*/
struct FKismetCompilerOptions
{
public:
	/** (Ivy) 要执行的编译类型(完整编译、仅通过框架等) The compile type to perform (full compile, skeleton pass only, etc) */
	EKismetCompileType::Type	CompileType;

	/** (Ivy) 是否保存中间构建产品(临时图和展开的宏)以进行调试 Whether or not to save intermediate build products (temporary graphs and expanded macros) for debugging */
	bool bSaveIntermediateProducts;

	/** (Ivy) 是否首先重新生成骨架，在加载编译时，我们不需要重新生成骨架 Whether to regenerate the skeleton first, when compiling on load we don't need to regenerate the skeleton. */
	bool bRegenerateSkelton;

	/** (Ivy) 不管这个编译是否为一个重复的蓝图 Whether or not this compile is for a duplicated blueprint */
	bool bIsDuplicationInstigated;

	/** 如果蓝图编译失败，是否重新实例和存根 Whether or not to reinstance and stub if the blueprint fails to compile */
	bool bReinstanceAndStubOnFailure;

	/** 是否跳过类默认对象验证 Whether or not to skip class default object validation */
	bool bSkipDefaultObjectValidation;

	/** 是否更新blueprint中的find搜索元数据 Whether or not to update Find-in-Blueprint search metadata */
	bool bSkipFiBSearchMetaUpdate;

	//TSharedPtr<FString> OutHeaderSourceCode;
	//TSharedPtr<FString> OutCppSourceCode;
	//FCompilerNativizationOptions NativizationOptions;

	bool DoesRequireCppCodeGeneration() const
	{
		return (CompileType == EKismetCompileType::Cpp);
	}

	bool DoesRequireBytecodeGeneration() const
	{
		return (CompileType == EKismetCompileType::Full)
			|| (CompileType == EKismetCompileType::BytecodeOnly)
			|| (CompileType == EKismetCompileType::Cpp);
	}

	FKismetCompilerOptions()
		: CompileType(EKismetCompileType::Full)
		, bSaveIntermediateProducts(false)
		, bRegenerateSkelton(true)
		, bIsDuplicationInstigated(false)
		, bReinstanceAndStubOnFailure(true)
		, bSkipDefaultObjectValidation(false)
		, bSkipFiBSearchMetaUpdate(false)
	{
	};
};
#pragma endregion

#pragma region (Ivy) 结构，包含关于在这个蓝图中实现了哪些接口的信息
/** 结构，包含关于在这个蓝图中实现了哪些接口的信息 Struct containing information about what interfaces are implemented in this blueprint */
struct FBPInterfaceDescription
{
	/** 对要添加到该蓝图中的接口类的引用 Reference to the interface class we're adding to this blueprint */
	TSubclassOf<class UInterface>  Interface;

	/** 对与此接口所需函数关联的图的引用 References to the graphs associated with the required functions for this interface */
	QList<UEdGraph*> Graphs;

	//FBPInterfaceDescription()
	//	: Interface(nullptr)
	//{ }
};
#pragma endregion

