/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:��ͼ�㼶 ͼ-�ڵ�-�����š�
**************************************************/
#pragma once

#include "Runtime/Core/Object.h"
#include "Runtime/Core/Guid.h"


typedef FGuid UEdGraphPinGuid;
class UEdGraphPin : public UObject
{
public:
	UEdGraphPin();
	UEdGraphPin(const UObjectInfo& info);
	UEdGraphPin(QString ObjectType, QString ObjectName);
	virtual ~UEdGraphPin();

public:
	UEdGraphPinGuid ConnPinGuid; //���ӵ�Pin��ID����������������
	FGuid NodeGuid; //���ڵ㣬���洢

public:
	//(zxf)���л�����
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UEdGraphPin);
};
Q_DECLARE_METATYPE(UEdGraphPin)
