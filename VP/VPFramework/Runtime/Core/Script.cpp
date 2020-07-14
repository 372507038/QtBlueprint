#include "Script.h"

QString Script::ToString(EFieldModifiers e)
{
	QString str;
	switch (e)
	{
	case EFieldModifiers::Normal:
		str = "Normal";
		break;
	case EFieldModifiers::Static:
		str = "Static";
		break;
	case EFieldModifiers::Const:
		str = "Const";
		break;
	case EFieldModifiers::Inline:
		str = "Inline";
		break;
	default:
		str = "{EnumNoFound}";
		break;
	}
	return str;
}

EFieldModifiers Script::ToEnum(const QString& str, EFieldModifiers& e)
{
	if (str == ToString(EFieldModifiers::Normal)) return EFieldModifiers::Normal;
	if (str == ToString(EFieldModifiers::Static)) return EFieldModifiers::Static;
	if (str == ToString(EFieldModifiers::Const)) return EFieldModifiers::Const;
	if (str == ToString(EFieldModifiers::Inline)) return EFieldModifiers::Inline;
	return EFieldModifiers::Normal;
}

QString Script::ToString(EAccessSpecifier e)
{
	QString str;
	switch (e)
	{
	case EAccessSpecifier::Public:
		str = "Public";
		break;
	case EAccessSpecifier::Protected:
		str = "Protected";
		break;
	case EAccessSpecifier::Private:
		str = "Private";
		break;
	default:
		str = "{EnumNoFound}";
		break;
	}
	return str;
}

EAccessSpecifier Script::ToEnum(const QString& str, EAccessSpecifier& e)
{
	if (str == ToString(EAccessSpecifier::Public)) return EAccessSpecifier::Public;
	if (str == ToString(EAccessSpecifier::Protected)) return EAccessSpecifier::Protected;
	if (str == ToString(EAccessSpecifier::Private)) return EAccessSpecifier::Private;
	return EAccessSpecifier::Public;
}

QString Script::ToString(EVariantType e)
{
	QString str;
	switch (e)
	{
	case EVariantType::None:
		str = "{None}";
		break;
	case EVariantType::Bool:
		str = "Bool";
		break;
	case EVariantType::Int:
		str = "Int";
		break;
	case EVariantType::Double:
		str = "Double";
		break;
	case EVariantType::String:
		str = "String";
		break;
	case EVariantType::Class:
		str = "Class";
		break;
	case EVariantType::Enum:
		str = "Enum";
		break;
	default:
		str = "{EnumNoFound}";
		break;
	}
	return str;
}

EVariantType Script::ToEnum(const QString& str, EVariantType& e)
{
	if (str == ToString(EVariantType::None)) return EVariantType::None;
	if (str == ToString(EVariantType::Bool)) return EVariantType::Bool;
	if (str == ToString(EVariantType::Int)) return EVariantType::Int;
	if (str == ToString(EVariantType::Double)) return EVariantType::Double;
	if (str == ToString(EVariantType::String)) return EVariantType::String;
	if (str == ToString(EVariantType::Class)) return EVariantType::Class;
	if (str == ToString(EVariantType::Enum)) return EVariantType::Enum;
	return EVariantType::None;
}

QString Script::ToString(EVariantBoxing e)
{
	QString str;
	switch (e)
	{
	case EVariantBoxing::None:
		str = "{None}";
		break;
	case EVariantBoxing::Copy:
		str = "";
		break;
	case EVariantBoxing::Reference:
		str = "&";
		break;
	case EVariantBoxing::Pointer:
		str = "*";
		break;
	default:
		str = "{EnumNoFound}";
		break;
	}
	return str;
}

EVariantBoxing Script::ToEnum(const QString& str, EVariantBoxing& e)
{
	if (str == ToString(EVariantBoxing::None)) return EVariantBoxing::None;
	if (str == ToString(EVariantBoxing::Copy)) return EVariantBoxing::Copy;
	if (str == ToString(EVariantBoxing::Reference)) return EVariantBoxing::Reference;
	if (str == ToString(EVariantBoxing::Pointer)) return EVariantBoxing::Pointer;
	return EVariantBoxing::None;
}

QString Script::ToString(EFunctionAbstraction e)
{
	QString str;
	switch (e)
	{
	case EFunctionAbstraction::Normal:
		str = "Normal";
		break;
	case EFunctionAbstraction::Virtual:
		str = "Virtual";
		break;
	case EFunctionAbstraction::PureVirtual:
		str = "PureVirtual";
		break;
	default:
		str = "{EnumNoFound}";
		break;
	}
	return str;
}

EFunctionAbstraction Script::ToEnum(const QString& str, EFunctionAbstraction& e)
{
	if (str == ToString(EFunctionAbstraction::Normal)) return EFunctionAbstraction::Normal;
	if (str == ToString(EFunctionAbstraction::Virtual)) return EFunctionAbstraction::Virtual;
	if (str == ToString(EFunctionAbstraction::PureVirtual)) return EFunctionAbstraction::PureVirtual;
	return EFunctionAbstraction::Normal;
}
