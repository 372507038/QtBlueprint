/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:蓝图层级 【图】-节点-引脚
**************************************************/
#pragma once

#include "Model/Core/Object.h"
#include "Model/Core/Guid.h"
#include "Model/Core/Class.h"
#include "EdGraphNode.h"
#include "EdGraphSchema.h"
#include "../Customize/k2EdGraph/K2Node.h"


typedef FGuid UEdGraphGuid;
class UEdGraph : public UObject
{
public:
	UEdGraph();
	UEdGraph(const UObjectInfo& info);
	UEdGraph(QString ObjectType, QString ObjectName);
	virtual ~UEdGraph();

public:
	UEdGraphSchemaGuid SchemaGuid; //需要遵守的模式
	QList<UEdGraphNodeGuid> Nodes; //子节点

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UEdGraph);;
	//(zxf)序列化数据
};
Q_DECLARE_METATYPE(UEdGraph)
