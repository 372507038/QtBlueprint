/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-11
Description:各种枚举
**************************************************/
#pragma once

#include "Object.h"

//修饰符
enum class EFieldModifiers
{
	Normal = 0x0,
	Static = 0x1,
	Const = 0x2,
	Inline = 0x4,
};

//访问权限
enum class EAccessSpecifier
{
	Public,
	Protected,
	Private,
};

//变量类型
enum class EVariantType
{
	None,		//error
	Bool,		//bool int4
	Int,		//int8 int16 int32 int64
	Double,		//float double
	String,		//char char[] string
	Class,		//class
	Enum,		//enum
};

//值传递类型
enum class EVariantBoxing
{
	None,		//error
	Copy,		//T a
	Reference,	//T& a
	Pointer		//T* a
};

//虚函数
enum class EFunctionAbstraction
{
	Normal,			//void func();
	Virtual,		//virtual void func();
	PureVirtual,	//virtual void func() = 0;
};

namespace Script
{
	extern QString ToString(EFieldModifiers e);
	extern QString ToString(EAccessSpecifier e);
	extern QString ToString(EVariantType e);
	extern QString ToString(EVariantBoxing e);
	extern QString ToString(EFunctionAbstraction e);

	extern EFieldModifiers			ToEnum(const QString& str, EFieldModifiers& e);
	extern EAccessSpecifier			ToEnum(const QString& str, EAccessSpecifier& e);
	extern EVariantType				ToEnum(const QString& str, EVariantType& e);
	extern EVariantBoxing			ToEnum(const QString& str, EVariantBoxing& e);
	extern EFunctionAbstraction		ToEnum(const QString& str, EFunctionAbstraction& e);
}


