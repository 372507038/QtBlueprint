#include "K2BlueprintFactories.h"

#include "Runtime/Core/Object.h"
#include "Runtime/Customize/k2EdGraph/K2Node.h"
#include "Runtime/Customize/k2EdGraph/EdGraphSchema_K2.h"
#include "Runtime/Customize/k2EdGraph/K2Node_EditablePinBase.h"
#include "Runtime/Customize/k2EdGraph/K2Node_FunctionEntry.h"
#include "Runtime/Customize/k2EdGraph/K2Node_FunctionTerminator.h"
#include <QDebug>


K2UBlueprint* K2UBlueprintFactories::CreateBlueprint(const QString& name)
{
	K2UBlueprint* blueprint = new K2UBlueprint(name);
	VPPOOL(blueprint).Add(blueprint);

	//测试创建一个Class，包含一个Func和一个Member
	UClass* newClass = VPNEW_UCLASS(blueprint);
	{
		newClass->SetObjectName("K2TestClass");

		UFunction* newFunc = VPNEW_UFunction(blueprint);
		{
			newFunc->SetObjectName("K2TestFunc");

			UVariant* newInput = VPNEW_UVariant(blueprint);
			{
				newInput->SetObjectName("nTestInput");
				newInput->m_VariantType = EVariantType::Int;
				newInput->m_VariantBoxing = EVariantBoxing::Copy;
			}
			newFunc->m_Inputs.append(newInput->GetObjectGuid());

			UVariant* newOutput = VPNEW_UVariant(blueprint);
			{
				newOutput->SetObjectName("nTestOutput");
				newOutput->m_VariantType = EVariantType::Int;
				newOutput->m_VariantBoxing = EVariantBoxing::Copy;
			}
			newFunc->m_Outputs.append(newOutput->GetObjectGuid());
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


const UObjectInfo K2UObjectFactory::OBJ_K2UBlueprint(typeid(K2UBlueprint).name(), "");
const UObjectInfo K2UObjectFactory::OBJ_UK2Node(typeid(UK2Node).name(), "");
const UObjectInfo K2UObjectFactory::OBJ_UEdGraphSchema_K2(typeid(UEdGraphSchema_K2).name(), "");
const UObjectInfo K2UObjectFactory::OBJ_UK2Node_EditablePinBase(typeid(UK2Node_EditablePinBase).name(), "");
const UObjectInfo K2UObjectFactory::OBJ_UK2Node_FunctionEntry(typeid(UK2Node_FunctionEntry).name(), "");
const UObjectInfo K2UObjectFactory::OBJ_UK2Node_FunctionTerminator(typeid(UK2Node_FunctionTerminator).name(), "");


UObject* K2UObjectFactory::CreateObject(const UObjectInfo& info)
{
	if (info.ObjectType == OBJ_K2UBlueprint.ObjectType)
		return new K2UBlueprint(info);
	if (info.ObjectType == OBJ_UK2Node.ObjectType)
		return new UK2Node(info);
	if (info.ObjectType == OBJ_UEdGraphSchema_K2.ObjectType)
		return new UEdGraphSchema_K2(info);
	if (info.ObjectType == OBJ_UK2Node_EditablePinBase.ObjectType)
		return new UK2Node_EditablePinBase(info);
	if (info.ObjectType == OBJ_UK2Node_FunctionEntry.ObjectType)
		return new UK2Node_FunctionEntry(info);
	if (info.ObjectType == OBJ_UK2Node_FunctionTerminator.ObjectType)
		return new UK2Node_FunctionTerminator(info);

	return UObjectFactory::CreateObject(info);
}

UObject* K2UObjectFactory::CreateObject2(const QString& key, const UObjectInfo& info)
{
	UObject* obj = CreateObject(info);
	if (obj)
		VPPOOL(key).Add(obj);
	return obj;
}

UObject* K2UObjectFactory::CreateObject3(const UObject* blueprint, const UObjectInfo& info)
{
	UObject* obj = CreateObject(info);
	if (obj)
		VPPOOL(blueprint).Add(obj);
	return obj;
}

