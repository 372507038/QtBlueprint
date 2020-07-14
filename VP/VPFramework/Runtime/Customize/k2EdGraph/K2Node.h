/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-04
Description:K2�ڵ�Ļ���
**************************************************/
#pragma once


#include "Runtime/EdGraph/EdGraphNode.h"

class UK2Node : public UEdGraphNode
{
public:
    UK2Node();
    UK2Node(const UObjectInfo& info);
	virtual ~UK2Node();

	/**(Ivy)����������������ҪCDO������֤�Ľڵ�(��չ��֮ǰ����) 
	This function if used for nodes that needs CDO for validation (Called before expansion)*/
	virtual void EarlyValidation(class FCompilerResultsLog& MessageLog) const;
};
