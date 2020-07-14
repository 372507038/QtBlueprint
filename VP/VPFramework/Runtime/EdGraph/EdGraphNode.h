/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:蓝图层级 图-【节点】-引脚
**************************************************/
#pragma once

#include "Runtime/Core/Object.h"
#include "Runtime/Core/Class.h"
#include "EdGraphPin.h"


typedef FGuid UEdGraphNodeGuid;
class UEdGraphNode : public UObject
{
public:
	UEdGraphNode();
	UEdGraphNode(const UObjectInfo& info);
	UEdGraphNode(QString ObjectType, QString ObjectName);
	virtual ~UEdGraphNode();

public:
	QList<UEdGraphPinGuid> Inputs; //输入引脚
	QList<UEdGraphPinGuid> Outputs;//输出引脚
	FGuid GraphGuid; //父图，仅存储

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UEdGraphNode);
};
Q_DECLARE_METATYPE(UEdGraphNode)
