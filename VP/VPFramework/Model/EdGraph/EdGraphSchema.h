/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:ͼ��Ҫ���ص�ģʽ
**************************************************/
#pragma once

#include "Model/Core/Object.h"


typedef FGuid UEdGraphSchemaGuid;
class UEdGraphSchema : public UObject
{
public:
	UEdGraphSchema();
	UEdGraphSchema(const UObjectInfo& info);
	UEdGraphSchema(QString ObjectType, QString ObjectName);
	virtual ~UEdGraphSchema();

};

