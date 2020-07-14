/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:��ͼ
**************************************************/
#pragma once

#include "Runtime/Core/Object.h"
#include "Runtime/Core/Class.h"
#include "Runtime/EdGraph/EdGraph.h"
#include "../Core/SubclassOf.h"

/**
 * ��ͼ���ṩ���ڽڵ��ֱ�۽���������ʲ��������ڴ������͵�Actor�ͽű����¼��� 
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

	/** (Ivy) ָ���������ȫ���ɵ����ָ�� Pointer to the 'most recent' fully generated class */
	//TSubclassOf<class UObject>	GeneratedClass;

public:
	UClassGuid m_Class;
	QList<UEdGraphGuid> m_Graphs;

public:
	//(zxf)���л�����
	virtual void Serialize(QDataStream& Ar) const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UBlueprint);

	/** (Ivy) �������ͼ���ҵ����е�ͼ�� Get all graphs in this blueprint */
	void GetAllGraphs(QList<UEdGraph*>& Graphs) const;

public:
	/** (Ivy) ���������������ͼ��ʵ�ֵĽӿڵ���Ϣ���� Array of info about the interfaces we implement in this blueprint */
	QList<struct FBPInterfaceDescription> ImplementedInterfaces;
};
Q_DECLARE_METATYPE(UBlueprint)


#pragma region (Ivy) ���������-�����ѡ��
/**(Ivy) ��������� Type of compilation. */
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

/*Ivy:20200623 �����ѡ��*/
struct FKismetCompilerOptions
{
public:
	/** (Ivy) Ҫִ�еı�������(�������롢��ͨ����ܵ�) The compile type to perform (full compile, skeleton pass only, etc) */
	EKismetCompileType::Type	CompileType;

	/** (Ivy) �Ƿ񱣴��м乹����Ʒ(��ʱͼ��չ���ĺ�)�Խ��е��� Whether or not to save intermediate build products (temporary graphs and expanded macros) for debugging */
	bool bSaveIntermediateProducts;

	/** (Ivy) �Ƿ������������ɹǼܣ��ڼ��ر���ʱ�����ǲ���Ҫ�������ɹǼ� Whether to regenerate the skeleton first, when compiling on load we don't need to regenerate the skeleton. */
	bool bRegenerateSkelton;

	/** (Ivy) ������������Ƿ�Ϊһ���ظ�����ͼ Whether or not this compile is for a duplicated blueprint */
	bool bIsDuplicationInstigated;

	/** �����ͼ����ʧ�ܣ��Ƿ�����ʵ���ʹ�� Whether or not to reinstance and stub if the blueprint fails to compile */
	bool bReinstanceAndStubOnFailure;

	/** �Ƿ�������Ĭ�϶�����֤ Whether or not to skip class default object validation */
	bool bSkipDefaultObjectValidation;

	/** �Ƿ����blueprint�е�find����Ԫ���� Whether or not to update Find-in-Blueprint search metadata */
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

#pragma region (Ivy) �ṹ�����������������ͼ��ʵ������Щ�ӿڵ���Ϣ
/** �ṹ�����������������ͼ��ʵ������Щ�ӿڵ���Ϣ Struct containing information about what interfaces are implemented in this blueprint */
struct FBPInterfaceDescription
{
	/** ��Ҫ��ӵ�����ͼ�еĽӿ�������� Reference to the interface class we're adding to this blueprint */
	TSubclassOf<class UInterface>  Interface;

	/** ����˽ӿ����躯��������ͼ������ References to the graphs associated with the required functions for this interface */
	QList<UEdGraph*> Graphs;

	//FBPInterfaceDescription()
	//	: Interface(nullptr)
	//{ }
};
#pragma endregion

