/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:��ͼ�㼶 ��ͼ��-�ڵ�-����
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

	/**(Ivy)��ȡͼ�и������͵����нڵ� Gets all the nodes in the graph of a given type */
	void GetNodesOfClass(QList<UK2Node*>& OutNodes) const;

public:
	UEdGraphSchemaGuid SchemaGuid; //��Ҫ���ص�ģʽ
	QList<UEdGraphNodeGuid> Nodes; //�ӽڵ�

public:
	//(zxf)���л�����
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UEdGraph);
};
Q_DECLARE_METATYPE(UEdGraph)
