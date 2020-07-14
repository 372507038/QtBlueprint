/*************************************************
Copyright:Ver1.0
Author:Ivy
Date:2020-06-04
Description:���ͼ�ı������ݻ���
**************************************************/
#pragma once


#include "Runtime/EdGraph/EdGraph.h"
#include "Runtime/EdGraph/EdGraphNode.h"
#include "Runtime/EdGraph/EdGraphPin.h"
#include "../Kismet2/CompilerResultsLog.h"

#include <QPointer>

/** EdGraphCompilerUtilities.h -> EdGraphCompiler.cpp*/

class FGraphCompilerContext
{
public:

	FGraphCompilerContext(FCompilerResultsLog& InMessageLog);

	/** ��֤��������֮��Ļ�����ģʽ���ݵ� */
	virtual void ValidateLink(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const;

	/** ��֤����pin�������Ƿ���ģʽ���� */
	virtual void ValidatePin(const UEdGraphPin* Pin) const;

	/** ��֤�ڵ��Ƿ�ģʽ����*/
	virtual void ValidateNode(const UEdGraphNode* Node) const;

	/** ���Ժ��Դ˽ڵ��Խ��н�һ��������? */
	virtual bool CanIgnoreNode(const UEdGraphNode* Node) const;

	/** ��ʹû�е���ýڵ㣬ҲӦ�ñ����ýڵ���? */
	virtual bool ShouldForceKeepNode(const UEdGraphNode* Node) const;

	UEdGraphNode* FindNodeByClass(const UEdGraph* Graph, QPointer<UEdGraphNode>  NodeClass, bool bExpectedUnique) const;

	/** ɾ��ͼ��δ���ʵĽڵ�
	/** ���pin�Ƿ���ܲ�����������? */
	virtual bool PinIsImportantForDependancies(const UEdGraphPin* Pin) const;

	/** ��ͼ����ִ�б�׼��֤(���ָ�����룬ÿ�����벻����һ�����ӣ���������ƥ�䣬�ȵ�) */
	bool ValidateGraphIsWellFormed(UEdGraph* Graph) const;

	/** ɨ��ͼ��ָ����Ľڣ�����ӡ������ */
	virtual void PruneIsolatedNodes(const QList<UEdGraphNode*>& RootSet, QList<UEdGraphNode*>& GraphNodes);

	/**
	 * �Դ���Ľڵ�(�����γ�DAG)ͼִ���������򣬶����ǽ��е��ȡ�
	 * ���ͼ�д���ѭ����δ���ӵĽڵ㣬����ÿ��δ�ܽ��е��ȵĽڵ㽫���һ������
	 */
	void CreateExecutionSchedule(const QList<UEdGraphNode*>& GraphNodes, /*out*/ QList<UEdGraphNode*>& LinearExecutionSchedule) const;

	/** ��������ڵ���������(����������������) */
	qint64 CountIncomingEdges(const UEdGraphNode* Node) const;

public:
	FCompilerResultsLog& MessageLog;
};


