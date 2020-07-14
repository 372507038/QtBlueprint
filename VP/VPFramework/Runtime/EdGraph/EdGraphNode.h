/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:��ͼ�㼶 ͼ-���ڵ㡿-����
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
	QList<UEdGraphPinGuid> Inputs; //��������
	QList<UEdGraphPinGuid> Outputs;//�������
	FGuid GraphGuid; //��ͼ�����洢

public:
	//(zxf)���л�����
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UEdGraphNode);
};
Q_DECLARE_METATYPE(UEdGraphNode)
