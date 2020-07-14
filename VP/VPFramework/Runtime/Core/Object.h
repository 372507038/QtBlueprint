/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-05
Description:���ж���Ļ���
**************************************************/
#pragma once

#include "ObjectPool.h"
#include "Guid.h"
#include <QObject>
#include <QDataStream>


/** ���л����ݣ��ṩ������ */
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


/** �ýṹ����ΪUObject�����ж�ʹ�� */
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
 * ����UE4����Ļ��ࡣ �������������UClass���塣 
 * ���ṩ�����ڴ�����ʹ�ö����֧�ֹ��ܣ��Լ�Ӧ���������и��ǵ����⹦�ܡ�
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

	/** ע�⿽������ʱ�ᵼ��Guid�ظ� */
	//UObject(const UObject&) = delete;
	//UObject& operator = (const UObject&) = delete;

	UObjectInfo GetInfo() const;
	void SetInfo(const UObjectInfo &info);

public:
	/** ����Guid���洢��pool��ʱ��Ч */
	const FGuid& GetObjectGuid() const;
	void SetObjectGuid(const FGuid &);

	/** ������������Ϊ�� */
	const QString& GetObjectName() const;
	void SetObjectName(const QString &);

	/** ��ͬ�� typeid(UObject).name() */
	const QString& GetObjectType() const;
	void SetObjectType(const QString &);

private:
	FGuid m_ObjectGuid; //�����ΨһID
	QString m_ObjectType; //���������
	QString m_ObjectName; //����ı�ʶ

public:
	//(zxf)���л�����
	virtual void Serialize(QDataStream& Ar) const;
	virtual void Deserialize(QDataStream& Ar);
	VP_SERIALIZE(UObject)
};
Q_DECLARE_METATYPE(UObject)

