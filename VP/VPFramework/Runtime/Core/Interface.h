/*************************************************
Copyright:Ver1.0
Author:Ivy
Date:2020-06-23
Description:���нӿڵĻ���
**************************************************/
#pragma once

#include "Object.h"

/**
 * (Ivy) ���нӿڵĻ��� Base class for all interfaces
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