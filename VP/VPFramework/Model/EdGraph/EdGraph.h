/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:��ͼ�㼶 ��ͼ��-�ڵ�-����
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
	UEdGraphSchemaGuid SchemaGuid; //��Ҫ���ص�ģʽ
	QList<UEdGraphNodeGuid> Nodes; //�ӽڵ�

public:
	//(zxf)���л�����
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UEdGraph);;
	//(zxf)���л�����
};
Q_DECLARE_METATYPE(UEdGraph)
