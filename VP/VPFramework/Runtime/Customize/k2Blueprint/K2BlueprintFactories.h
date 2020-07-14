/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:��ͼ����K2
**************************************************/
#pragma once

#include "Runtime/Blueprint/BlueprintFactories.h"
#include "Runtime/Core/Object.h"
#include "Runtime/Customize/k2Blueprint/K2Blueprint.h"


class K2UBlueprintFactories
{
public:
	/** ������ʼ����ͼ���� UBlueprint����ʼ��Ĭ��Node */
	static K2UBlueprint* CreateBlueprint(const QString& name);
};


class K2UObjectFactory
{
public:
	static const UObjectInfo OBJ_K2UBlueprint;
	static const UObjectInfo OBJ_UK2Node;
	static const UObjectInfo OBJ_UEdGraphSchema_K2;
	static const UObjectInfo OBJ_UK2Node_EditablePinBase;
	static const UObjectInfo OBJ_UK2Node_FunctionEntry;
	static const UObjectInfo OBJ_UK2Node_FunctionTerminator;

public:
	/** ���ݶ�����Ϣ������ UObject����Ҫ�ֶ���ʼ�� */
	static UObject* CreateObject(const UObjectInfo& info);
	static UObject* CreateObject2(const QString& key, const UObjectInfo& info);
	static UObject* CreateObject3(const UObject* blueprint, const UObjectInfo& info);
};


