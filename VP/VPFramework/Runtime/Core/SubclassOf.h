/*************************************************
Copyright:Ver1.0
Author:Ivy
Date:2020-06-23
Description:
**************************************************/
#pragma once

#include "Class.h"


/**
 * (Ivy)模板允许TClassType在类型安全的情况下传递 Template to allow TClassType's to be passed around with type safety
 */
template<class TClass>
class TSubclassOf
{
public:
	///** 复制构造函数，只有在类型兼容时才编译  Copy Constructor, will only compile if types are compatible */
	//template <class TClassA, class = decltype(ImplicitConv<TClass*>((TClassA*)nullptr))>
	//FORCEINLINE TSubclassOf(const TSubclassOf<TClassA>& From) :
	//	Class(*From)
	//{
	//}

	///** 赋值运算符，只有在类型兼容时才编译 Assignment operator, will only compile if types are compatible */
	//template <class TClassA, class = decltype(ImplicitConv<TClass*>((TClassA*)nullptr))>
	//FORCEINLINE TSubclassOf& operator=(const TSubclassOf<TClassA>& From)
	//{
	//	Class = *From;
	//	return *this;
	//}

	///** 来自UClass的赋值操作符，类型在get not on set上检查 Assignment operator from UClass, the type is checked on get not on set */
	//FORCEINLINE TSubclassOf& operator=(TClassType* From)
	//{
	//	Class = From;
	//	return *this;
	//}
};