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
#include "ObjectMacros.h"

/** (Ivy) 关于类实现的接口的信息 information about an interface a class implements */
struct FImplementedInterface
{
	/** 接口类 the interface class */
	//UClass* Class;
	///** 接口虚函数表的指针偏移量 the pointer offset of the interface's vtable */
	//qint64 PointerOffset;
	///** 这个接口是否通过K2实现 whether or not this interface has been implemented via K2 */
	//bool bImplementedByK2;

	//FImplementedInterface()
	//	: Class(nullptr)
	//	, PointerOffset(0)
	//	, bImplementedByK2(false)
	//{}

	//FImplementedInterface(UClass* InClass, qint64 InOffset, bool InImplementedByK2)
	//	: Class(InClass)
	//	, PointerOffset(InOffset)
	//	, bImplementedByK2(InImplementedByK2)
	//{}

	//friend FArchive& operator<<(FArchive& Ar, FImplementedInterface& A);
};

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

	/** （Ivy）类的标识;有关更多信息，请参见EClassFlags */
	EClassFlags ClassFlags;

	/**
	 * （Ivy）这个类实现的接口列表，以及位于接口虚函数表偏移位置的指针属性。The list of interfaces which this class implements, along with the pointer property that is located at the offset of the interface's vtable.
	 * 如果接口类不是本机的，属性将为null。 If the interface class isn't native, the property will be null.
	 */
	QList<FImplementedInterface> Interfaces;

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UField)
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
	VP_SERIALIZE(UVariant)
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
	VP_SERIALIZE(UFunction)
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
	VP_SERIALIZE(UEnum)
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

	/**
	 * (Ivy) 用于安全检查是否设置了传入标志。 Used to safely check whether the passed in flag is set.
	 *
	 * @param	FlagsToCheck		要检查的类标记 Class flag(s) to check for
	 *
	 * @return	如果设置了传入标志，则为true，否则为false true if the passed in flag is set, false otherwise
	 *			(如果设置了传入的标志，则为true，如果没有传入的标志，则为false，除非FlagsToCheck是CLASS_AllFlags
					including no flag passed in, unless the FlagsToCheck is CLASS_AllFlags)
	 */
	bool HasAnyClassFlags(EClassFlags FlagsToCheck) const;

public:
	QList<UFunctionGuid> m_Functions;
	QList<UVariantGuid> m_Members;
	QList<QString> m_Includes;

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar)const override;
	virtual void Deserialize(QDataStream& Ar) override;
	VP_SERIALIZE(UClass)
};
Q_DECLARE_METATYPE(UClass)

