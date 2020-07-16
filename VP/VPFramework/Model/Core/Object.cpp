#include "Object.h"
#include "ObjectPool.h"

UObject::UObject()
	: UObject(typeid(UObject).name(), "")
{
}

UObject::UObject(const UObjectInfo& info)
	: UObject(info.ObjectType, info.ObjectName)
{
}

UObject::UObject(QString ObjectType, QString ObjectName)
	: m_ObjectGuid(FGuid::NewGuid())
	, m_ObjectType(ObjectType.isEmpty() ? typeid(UObject).name() : ObjectType)
	, m_ObjectName(ObjectName)
{
}

UObject::~UObject()
{
}

void UObject::Serialize(QDataStream & Ar)const
{
	//__super::Serialize(Ar);

	Ar << m_ObjectGuid << m_ObjectType << m_ObjectName;
}

void UObject::Deserialize(QDataStream & Ar)
{
	//__super::Deserialize(Ar);

	Ar >> m_ObjectGuid >> m_ObjectType >> m_ObjectName;
}

const QString& UObject::GetObjectName() const
{
	return m_ObjectName;
}

void UObject::SetObjectName(const QString& s)
{
	m_ObjectName = s;
}

const QString & UObject::GetObjectType() const
{
	return m_ObjectType;
}

void UObject::SetObjectType(const QString &s)
{
	m_ObjectType = s;
}

UObjectInfo UObject::GetInfo() const
{
	return UObjectInfo(GetObjectType(), GetObjectName());
}

void UObject::SetInfo(const UObjectInfo & info)
{
	SetObjectType(info.ObjectType);
	SetObjectName(info.ObjectName);
}

const FGuid& UObject::GetObjectGuid() const
{
	return m_ObjectGuid;
}

void UObject::SetObjectGuid(const FGuid & id)
{
	m_ObjectGuid = id;
}

