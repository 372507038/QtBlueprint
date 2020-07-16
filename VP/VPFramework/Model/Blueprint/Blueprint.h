/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:蓝图
**************************************************/
#pragma once

#include "Model/Core/Object.h"
#include "Model/Core/Class.h"
#include "Model/EdGraph/EdGraph.h"

class UBlueprint : public UObject
{
	friend class BlueprintEditor;

public:
	UBlueprint();
	UBlueprint(const UObjectInfo& info);
	UBlueprint(QString ObjectType, QString ObjectName);
	UBlueprint(QString name);
	virtual ~UBlueprint();

public:
	UClassGuid m_Class;
	QList<UEdGraphGuid> m_Graphs;

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar) const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UBlueprint);
	//(zxf)序列化数据
};
Q_DECLARE_METATYPE(UBlueprint)
