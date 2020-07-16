/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-05
Description:蓝图的方法、函数、枚举等
**************************************************/
#pragma once

#include "Object.h"
#include "Guid.h"
#include "Script.h"
#include <QMap>
#include <QVariant>

typedef FGuid UFieldGuid;
class UField : public UObject
{
public:
	UField();
	UField(const UObjectInfo& info);
	UField(QString ObjectType, QString ObjectName);
	virtual ~UField();

public:
	EFieldModifiers m_Modifiers = EFieldModifiers::Normal;
	EAccessSpecifier m_AccessModifiers = EAccessSpecifier::Private;

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UField);
	//(zxf)序列化数据
};
Q_DECLARE_METATYPE(UField)


typedef FGuid UVariantGuid;
class UVariant : public UField
{
public:
	UVariant();
	UVariant(const UObjectInfo& info);
	UVariant(QString ObjectType, QString ObjectName, EVariantType VariantType, EVariantBoxing VariantBoxing);
	virtual ~UVariant();

public:
	EVariantType m_VariantType = EVariantType::None;
	EVariantBoxing m_VariantBoxing = EVariantBoxing::None;
	QString m_VariantTypeDetail;	//枚举或Class需要知道类型
	QString m_DefaultValue;			//默认值

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UVariant);
	//(zxf)序列化数据
};
Q_DECLARE_METATYPE(UVariant)


typedef FGuid UFunctionGuid;
class UFunction : public UField
{
public:
	UFunction();
	UFunction(const UObjectInfo& info);
	UFunction(QString ObjectType, QString ObjectName);
	virtual ~UFunction();

public:
	EFunctionAbstraction m_FunctionAbstraction = EFunctionAbstraction::Normal;
	QList<UVariantGuid> m_Inputs;
	QList<UVariantGuid> m_Outputs;

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UFunction);
	//(zxf)序列化数据
};
Q_DECLARE_METATYPE(UFunction)


typedef FGuid UEnumGuid;
class UEnum : public UField
{
public:
	UEnum();
	UEnum(const UObjectInfo& info);
	UEnum(QString ObjectType, QString ObjectName);
	virtual ~UEnum();

public:
	QMap<QString, qint64> m_MapEnums;

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UEnum);
	//(zxf)序列化数据
};
Q_DECLARE_METATYPE(UEnum)


typedef FGuid UClassGuid;
class UClass : public UField
{
public:
	UClass();
	UClass(const UObjectInfo& info);
	UClass(QString ObjectType, QString ObjectName);
	virtual ~UClass();

public:
	QList<UFunctionGuid> m_Functions;
	QList<UVariantGuid> m_Members;
	QList<QString> m_Includes;

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UClass);
	//(zxf)序列化数据
};
Q_DECLARE_METATYPE(UClass)

