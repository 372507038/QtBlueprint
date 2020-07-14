/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-05
Description:所有对象的基类
**************************************************/
#pragma once

#include "ObjectPool.h"
#include "Guid.h"
#include <QObject>
#include <QDataStream>


/** 序列化数据，提供流操作 */
#define VP_SERIALIZE(TYPE) VP_SERIALIZE_IMPL(TYPE)
#define VP_SERIALIZE_IMPL(TYPE)											\
	friend QDataStream &operator<<(QDataStream &out, const TYPE &myObj)	\
	{																	\
		myObj.Serialize(out);											\
		return out;														\
	}																	\
	friend QDataStream &operator>>(QDataStream &in, TYPE &myObj)		\
	{																	\
		myObj.Deserialize(in);											\
		return in;														\
	}


/** 该结构将作为UObject类型判断使用 */
struct UObjectInfo
{
	QString ObjectType;
	QString ObjectName;

	UObjectInfo()
		: UObjectInfo("", "")
	{}
	UObjectInfo(QString ObjectType_, QString ObjectName_)
		: ObjectType(ObjectType_)
		, ObjectName(ObjectName_)
	{}

	friend QDataStream &operator<<(QDataStream &out, const UObjectInfo &myObj)
	{
		out << myObj.ObjectType << myObj.ObjectName;
		return out;
	}
	friend QDataStream &operator>>(QDataStream &in, UObjectInfo &myObj)
	{
		in >> myObj.ObjectType >> myObj.ObjectName;
		return in;
	}
};


/**
 * 所有UE4对象的基类。 对象的类型由其UClass定义。 
 * 这提供了用于创建和使用对象的支持功能，以及应该在子类中覆盖的虚拟功能。
 * 
 * The base class of all UE4 objects. The type of an object is defined by its UClass.
 * This provides support functions for creating and using objects, and virtual functions that should be overridden in child classes.
 *
 * @see https://docs.unrealengine.com/en-us/Programming/UnrealArchitecture/Objects
 */
class UObject
{
public:
	UObject();
	UObject(const UObjectInfo& info);
	UObject(QString ObjectType, QString ObjectName);
	virtual ~UObject();

	/** 注意拷贝对象时会导致Guid重复 */
	//UObject(const UObject&) = delete;
	//UObject& operator = (const UObject&) = delete;

	UObjectInfo GetInfo() const;
	void SetInfo(const UObjectInfo &info);

public:
	/** 对象Guid，存储在pool中时有效 */
	const FGuid& GetObjectGuid() const;
	void SetObjectGuid(const FGuid &);

	/** 对象名，可以为空 */
	const QString& GetObjectName() const;
	void SetObjectName(const QString &);

	/** 等同于 typeid(UObject).name() */
	const QString& GetObjectType() const;
	void SetObjectType(const QString &);

private:
	FGuid m_ObjectGuid; //对象的唯一ID
	QString m_ObjectType; //对象的类型
	QString m_ObjectName; //对象的标识

public:
	//(zxf)序列化数据
	virtual void Serialize(QDataStream& Ar) const;
	virtual void Deserialize(QDataStream& Ar);
	VP_SERIALIZE(UObject)
};
Q_DECLARE_METATYPE(UObject)

