/*************************************************
Copyright:Ver1.0
Author:Ivy
Date:2020-06-23
Description:所有接口的基类
**************************************************/
#pragma once

#include "Object.h"

/**
 * (Ivy) 所有接口的基类 Base class for all interfaces
 *
 */
class UInterface : public UObject
{
	//DECLARE_CLASS_INTRINSIC(UInterface, UObject, CLASS_Interface | CLASS_Abstract, TEXT("/Script/CoreUObject"))
};

class IInterface
{
protected:

	virtual ~IInterface() {}

public:

	typedef UInterface UClassType;
};