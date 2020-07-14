/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-05
Description:
**************************************************/
#pragma once

#include "K2Node.h"

class UK2Node_EditablePinBase : public UK2Node
{
public:
	UK2Node_EditablePinBase();
	UK2Node_EditablePinBase(const UObjectInfo& info);
	virtual ~UK2Node_EditablePinBase();
};
