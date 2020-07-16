/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:�ͼ
**************************************************/
#pragma once

#include "Model/Blueprint/Blueprint.h"


class K2UBlueprint : public UBlueprint
{
public:
	K2UBlueprint();
	K2UBlueprint(const UObjectInfo& info);
	K2UBlueprint(QString ObjectType, QString ObjectName);
	K2UBlueprint(QString name);
	virtual ~K2UBlueprint();
};
