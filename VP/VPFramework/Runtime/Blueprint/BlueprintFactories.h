/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:��ͼ����
**************************************************/
#pragma once

#include "Runtime/Blueprint/Blueprint.h"
#include "Runtime/Core/Object.h"


class UBlueprintFactories
{
public:
	/** ������ʼ����ͼ���� UBlueprint����ʼ��Ĭ��Node��ע�ᵽPool�� */
	static UBlueprint* CreateBlueprint(const QString& name);
};


#define VPNEW_UCLASS(Blueprint)		static_cast<UClass*>(UObjectFactory::CreateObject3(Blueprint, UObjectFactory::OBJ_UClass))
#define VPNEW_UFunction(Blueprint)	static_cast<UFunction*>(UObjectFactory::CreateObject3(Blueprint, UObjectFactory::OBJ_UFunction))
#define VPNEW_UVariant(Blueprint)	static_cast<UVariant*>(UObjectFactory::CreateObject3(Blueprint, UObjectFactory::OBJ_UVariant))

class UObjectFactory
{
public:
	static const UObjectInfo OBJ_UBlueprint;
	static const UObjectInfo OBJ_UObject;
	static const UObjectInfo OBJ_UField;
	static const UObjectInfo OBJ_UVariant;
	static const UObjectInfo OBJ_UFunction;
	static const UObjectInfo OBJ_UEnum;
	static const UObjectInfo OBJ_UClass;
	static const UObjectInfo OBJ_UEdGraph;
	static const UObjectInfo OBJ_UEdGraphNode;
	static const UObjectInfo OBJ_UEdGraphPin;
	static const UObjectInfo OBJ_UEdGraphSchema;

public:
	/** ���ݶ�����Ϣ������ UObject����Ҫ�ֶ���ʼ����ָ����ͼ�����keyʱע�ᵽPool�� */
	static UObject* CreateObject(const UObjectInfo& info);
	static UObject* CreateObject2(const QString& key, const UObjectInfo& info);
	static UObject* CreateObject3(const UObject* blueprint, const UObjectInfo& info);
};


