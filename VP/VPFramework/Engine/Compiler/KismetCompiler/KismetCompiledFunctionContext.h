/*************************************************
Copyright:Ver1.0
Author:Ivy
Date:2020-06-08
Description:
**************************************************/
#pragma once

#include "Runtime/EdGraph/EdGraph.h"
#include "Runtime/EdGraph/EdGraphNode.h"
#include "Runtime/Blueprint/Blueprint.h"

#include "Runtime/Customize/k2EdGraph/K2Node_FunctionEntry.h"

/** FKismetFunctionContext */
/** KismetCompiledFunctionContext.h -> KismetCompilerMisc.cpp*/

struct FKismetFunctionContext
{
public:
	FKismetFunctionContext();
	~FKismetFunctionContext();

public:
	/** 蓝图源 Blueprint source */
	UBlueprint* Blueprint;

	UEdGraph* SourceGraph;

	/** 名义功能入口点 The nominal function entry point*/
	//UK2Node_FunctionEntry* EntryPoint;

	/** 线性执行时间表 Linear execution schedule */
	QList<UEdGraphNode*> LinearExecutionList;
};