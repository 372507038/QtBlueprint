#include "BlueprintFactories.h"

#include "Runtime/Core/Object.h"
#include "Runtime/Core/Class.h"
#include "Runtime/EdGraph/EdGraph.h"
#include "Runtime/EdGraph/EdGraphNode.h"
#include "Runtime/EdGraph/EdGraphPin.h"
#include "Runtime/EdGraph/EdGraphSchema.h"
#include "Runtime/Core/ObjectPool.h"
#include <QDebug>


UBlueprint * UBlueprintFactories::CreateBlueprint(const QString & name)
{
	UBlueprint *blueprint = new UBlueprint(name);
	VPPOOL(blueprint).Add(blueprint);

	//测试创建一个Class，包含一个Func和一个Member
	UClass* newClass = VPNEW_UCLASS(blueprint);
	{
		newClass->SetObjectName("MyTestClass");

		UFunction* newFunc = VPNEW_UFunction(blueprint);
		{
			newFunc->SetObjectName("MyTestFunc");
		}
		newClass->m_Functions.append(newFunc->GetObjectGuid());

		UVariant* newMember = VPNEW_UVariant(blueprint);
		{
			newMember->SetObjectName("m_StringTest");
			newMember->m_VariantType = EVariantType::String;
			newMember->m_VariantBoxing = EVariantBoxing::Copy;
		}
		newClass->m_Members.append(newMember->GetObjectGuid());
	}
	blueprint->m_Class = newClass->GetObjectGuid();

	return blueprint;
}


const UObjectInfo UObjectFactory::OBJ_UBlueprint(typeid(UBlueprint).name(), "");
const UObjectInfo UObjectFactory::OBJ_UObject(typeid(UObject).name(), "");
const UObjectInfo UObjectFactory::OBJ_UField(typeid(UField).name(), "");
const UObjectInfo UObjectFactory::OBJ_UVariant(typeid(UVariant).name(), "");
const UObjectInfo UObjectFactory::OBJ_UFunction(typeid(UFunction).name(), "");
const UObjectInfo UObjectFactory::OBJ_UEnum(typeid(UEnum).name(), "");
const UObjectInfo UObjectFactory::OBJ_UClass(typeid(UClass).name(), "");
const UObjectInfo UObjectFactory::OBJ_UEdGraph(typeid(UEdGraph).name(), "");
const UObjectInfo UObjectFactory::OBJ_UEdGraphNode(typeid(UEdGraphNode).name(), "");
const UObjectInfo UObjectFactory::OBJ_UEdGraphPin(typeid(UEdGraphPin).name(), "");
const UObjectInfo UObjectFactory::OBJ_UEdGraphSchema(typeid(UEdGraphSchema).name(), "");


UObject * UObjectFactory::CreateObject(const UObjectInfo & info)
{
	if (info.ObjectType == OBJ_UBlueprint.ObjectType)
		return new UBlueprint(info);
	if (info.ObjectType == OBJ_UObject.ObjectType)
		return new UObject(info);
	if (info.ObjectType == OBJ_UField.ObjectType)
		return new UField(info);
	if (info.ObjectType == OBJ_UVariant.ObjectType)
		return new UVariant(info);
	if (info.ObjectType == OBJ_UFunction.ObjectType)
		return new UFunction(info);
	if (info.ObjectType == OBJ_UEnum.ObjectType)
		return new UEnum(info);
	if (info.ObjectType == OBJ_UClass.ObjectType)
		return new UClass(info);
	if (info.ObjectType == OBJ_UEdGraph.ObjectType)
		return new UEdGraph(info);
	if (info.ObjectType == OBJ_UEdGraphNode.ObjectType)
		return new UEdGraphNode(info);
	if (info.ObjectType == OBJ_UEdGraphPin.ObjectType)
		return new UEdGraphPin(info);
	if (info.ObjectType == OBJ_UEdGraphSchema.ObjectType)
		return new UEdGraphSchema(info);

	return nullptr;
}

UObject* UObjectFactory::CreateObject2(const QString& key, const UObjectInfo& info)
{
	UObject* obj = CreateObject(info);
	if (obj)
		VPPOOL(key).Add(obj);
	return obj;
}

UObject* UObjectFactory::CreateObject3(const UObject* blueprint, const UObjectInfo& info)
{
	UObject* obj = CreateObject(info);
	if (obj)
		VPPOOL(blueprint).Add(obj);
	return obj;
}

