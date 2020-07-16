#include "Class.h"

UField::UField()
	: UObject()
{
}

UField::UField(const UObjectInfo& info)
	: UObject(info)
{
}

UField::~UField()
{
}

UField::UField(QString ObjectType, QString ObjectName)
	: UObject(ObjectType.isEmpty() ? typeid(UField).name() : ObjectType, ObjectName)
{
}

void UField::Serialize(QDataStream & Ar)const
{
	__super::Serialize(Ar);

	Ar << m_Modifiers << m_AccessModifiers;
}

void UField::Deserialize(QDataStream & Ar)
{
	__super::Deserialize(Ar);

	Ar >> m_Modifiers >> m_AccessModifiers;
}


UVariant::UVariant()
	: UField()
{
}

UVariant::UVariant(const UObjectInfo& info)
	: UField(info)
{
}

UVariant::UVariant(QString ObjectType, QString ObjectName, EVariantType VariantType, EVariantBoxing VariantBoxing)
	: UField(ObjectType.isEmpty() ? typeid(UVariant).name() : ObjectType, ObjectName)
	, m_VariantType(VariantType)
	, m_VariantBoxing(VariantBoxing)
{
}

UVariant::~UVariant()
{
}

void UVariant::Serialize(QDataStream & Ar)const
{
	__super::Serialize(Ar);

	Ar << m_VariantType << m_VariantBoxing << m_DefaultValue;
}

void UVariant::Deserialize(QDataStream & Ar)
{
	__super::Deserialize(Ar);

	Ar >> m_VariantType >> m_VariantBoxing >> m_DefaultValue;
}


UFunction::UFunction()
	: UField()
{
}

UFunction::UFunction(const UObjectInfo& info)
	: UField(info)
{
}

UFunction::UFunction(QString ObjectType, QString ObjectName)
	: UField(ObjectType.isEmpty() ? typeid(UFunction).name() : ObjectType, ObjectName)
{
}

UFunction::~UFunction()
{
}

void UFunction::Serialize(QDataStream & Ar)const
{
	__super::Serialize(Ar);

	Ar << m_FunctionAbstraction << m_Inputs << m_Outputs;
}

void UFunction::Deserialize(QDataStream & Ar)
{
	__super::Deserialize(Ar);

	Ar >> m_FunctionAbstraction >> m_Inputs >> m_Outputs;
}


UEnum::UEnum()
	: UField()
{
}

UEnum::UEnum(const UObjectInfo& info)
	: UField(info)
{
}

UEnum::UEnum(QString ObjectType, QString ObjectName)
	: UField(ObjectType.isEmpty() ? typeid(UEnum).name() : ObjectType, ObjectName)
{
}

UEnum::~UEnum()
{
}

void UEnum::Serialize(QDataStream & Ar)const
{
	__super::Serialize(Ar);

	Ar << m_MapEnums;
}

void UEnum::Deserialize(QDataStream & Ar)
{
	__super::Deserialize(Ar);

	Ar >> m_MapEnums;
}


UClass::UClass()
	: UField()
{
}

UClass::UClass(const UObjectInfo& info)
	: UField(info)
{
}

UClass::UClass(QString ObjectType, QString ObjectName)
	: UField(ObjectType.isEmpty() ? typeid(UClass).name() : ObjectType, ObjectName)
{
}

UClass::~UClass()
{
}

void UClass::Serialize(QDataStream & Ar)const
{
	__super::Serialize(Ar);

	Ar << m_Functions << m_Members << m_Includes;
}

void UClass::Deserialize(QDataStream & Ar)
{
	__super::Deserialize(Ar);

	Ar >> m_Functions >> m_Members >> m_Includes;
}
