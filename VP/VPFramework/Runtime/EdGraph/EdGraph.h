/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:蓝图层级 【图】-节点-引脚
**************************************************/
#pragma once

#include "Runtime/Core/Object.h"
#include "Runtime/Core/Guid.h"
#include "Runtime/Core/Class.h"
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

	/**(Ivy)获取图中给定类型的所有节点 Gets all the nodes in the graph of a given type */
	void GetNodesOfClass(QList<UK2Node*>& OutNodes) const;

public:
	UEdGraphSchemaGuid SchemaGuid; //需要遵守的模式
	QList<UEdGraphNodeGuid> Nodes; //子节点

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UEdGraph);
};
Q_DECLARE_METATYPE(UEdGraph)
