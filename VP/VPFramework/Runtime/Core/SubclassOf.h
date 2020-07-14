/*************************************************
Copyright:Ver1.0
Author:Ivy
Date:2020-06-23
Description:
**************************************************/
#pragma once

#include "Class.h"


/**
 * (Ivy)ģ������TClassType�����Ͱ�ȫ������´��� Template to allow TClassType's to be passed around with type safety
 */
template<class TClass>
class TSubclassOf
{
public:
	///** ���ƹ��캯����ֻ�������ͼ���ʱ�ű���  Copy Constructor, will only compile if types are compatible */
	//template <class TClassA, class = decltype(ImplicitConv<TClass*>((TClassA*)nullptr))>
	//FORCEINLINE TSubclassOf(const TSubclassOf<TClassA>& From) :
	//	Class(*From)
	//{
	//}

	///** ��ֵ�������ֻ�������ͼ���ʱ�ű��� Assignment operator, will only compile if types are compatible */
	//template <class TClassA, class = decltype(ImplicitConv<TClass*>((TClassA*)nullptr))>
	//FORCEINLINE TSubclassOf& operator=(const TSubclassOf<TClassA>& From)
	//{
	//	Class = *From;
	//	return *this;
	//}

	///** ����UClass�ĸ�ֵ��������������get not on set�ϼ�� Assignment operator from UClass, the type is checked on get not on set */
	//FORCEINLINE TSubclassOf& operator=(TClassType* From)
	//{
	//	Class = From;
	//	return *this;
	//}
};