/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:图需要遵守的模式
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

