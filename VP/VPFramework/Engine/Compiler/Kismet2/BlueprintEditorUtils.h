/*************************************************
Copyright:Ver1.0
Author:Ivy
Date:2020-06-23
Description:
**************************************************/
#pragma once

class UBlueprint;

class FBlueprintEditorUtils
{
	FBlueprintEditorUtils();
	virtual ~FBlueprintEditorUtils();
public:
	/** 确保对父函数的调用是有效的，如果无效则删除它们 Makes sure that calls to parent functions are valid, and removes them if not */
	static void ConformCallsToParentFunctions(UBlueprint* Blueprint);

	/** 确保我们处理的所有事件都存在，如果不存在，则使用自定义事件替换 Makes sure that all events we handle exist, and replace with custom events if not */
	static void ConformImplementedEvents(UBlueprint* Blueprint);

	/** 确保我们实现的所有接口的所有图形都存在，如果不存在就添加 Makes sure that all graphs for all interfaces we implement exist, and add if not */
	static void ConformImplementedInterfaces(UBlueprint* Blueprint);
};

