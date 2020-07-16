/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:K2节点的基类
**************************************************/
#pragma once


#include "Model/EdGraph/EdGraphNode.h"

class UK2Node : public UEdGraphNode
{
public:
    UK2Node();
    UK2Node(const UObjectInfo& info);
	virtual ~UK2Node();
};
