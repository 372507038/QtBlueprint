/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:K2节点的基类
**************************************************/
#pragma once


#include "Runtime/EdGraph/EdGraphNode.h"

class UK2Node : public UEdGraphNode
{
public:
    UK2Node();
    UK2Node(const UObjectInfo& info);
	virtual ~UK2Node();

	/**(Ivy)这个函数如果用于需要CDO进行验证的节点(在展开之前调用) 
	This function if used for nodes that needs CDO for validation (Called before expansion)*/
	virtual void EarlyValidation(class FCompilerResultsLog& MessageLog) const;
};
