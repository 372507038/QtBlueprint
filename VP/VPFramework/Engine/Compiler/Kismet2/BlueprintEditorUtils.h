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
	/** ȷ���Ը������ĵ�������Ч�ģ������Ч��ɾ������ Makes sure that calls to parent functions are valid, and removes them if not */
	static void ConformCallsToParentFunctions(UBlueprint* Blueprint);

	/** ȷ�����Ǵ���������¼������ڣ���������ڣ���ʹ���Զ����¼��滻 Makes sure that all events we handle exist, and replace with custom events if not */
	static void ConformImplementedEvents(UBlueprint* Blueprint);

	/** ȷ������ʵ�ֵ����нӿڵ�����ͼ�ζ����ڣ���������ھ���� Makes sure that all graphs for all interfaces we implement exist, and add if not */
	static void ConformImplementedInterfaces(UBlueprint* Blueprint);
};

