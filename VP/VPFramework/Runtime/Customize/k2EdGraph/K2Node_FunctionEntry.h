/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-05
Description:
**************************************************/
#pragma once

#include "K2Node_FunctionTerminator.h"

class UK2Node_FunctionEntry : public UK2Node_FunctionTerminator
{
public:
	UK2Node_FunctionEntry();
	UK2Node_FunctionEntry(const UObjectInfo& info);
	virtual ~UK2Node_FunctionEntry();
};
