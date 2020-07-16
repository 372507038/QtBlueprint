/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:蓝图层级 图-节点-【引脚】
**************************************************/
#pragma once

#include "Model/Core/Object.h"
#include "Model/Core/Guid.h"


typedef FGuid UEdGraphPinGuid;
class UEdGraphPin : public UObject
{
public:
	UEdGraphPin();
	UEdGraphPin(const UObjectInfo& info);
	UEdGraphPin(QString ObjectType, QString ObjectName);
	virtual ~UEdGraphPin();

public:
	UEdGraphPinGuid ConnPinGuid; //连接的Pin的ID，可以是输入或输出 todo list
	FGuid NodeGuid; //父节点，仅存储

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UEdGraphPin);
	//(zxf)序列化数据
};
Q_DECLARE_METATYPE(UEdGraphPin)
