/*************************************************
Copyright:Ver1.0
Author:Ivy
Date:2020-06-04
Description:相关图的编译内容基类
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

	/** 验证两个引脚之间的互连是模式兼容的 */
	virtual void ValidateLink(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const;

	/** 验证单个pin的连接是否与模式兼容 */
	virtual void ValidatePin(const UEdGraphPin* Pin) const;

	/** 验证节点是否模式兼容*/
	virtual void ValidateNode(const UEdGraphNode* Node) const;

	/** 可以忽略此节点以进行进一步处理吗? */
	virtual bool CanIgnoreNode(const UEdGraphNode* Node) const;

	/** 即使没有到达该节点，也应该保留该节点吗? */
	virtual bool ShouldForceKeepNode(const UEdGraphNode* Node) const;

	UEdGraphNode* FindNodeByClass(const UEdGraph* Graph, QPointer<UEdGraphNode>  NodeClass, bool bExpectedUnique) const;

	/** 删除图中未访问的节点
	/** 这个pin是否可能参与数据依赖? */
	virtual bool PinIsImportantForDependancies(const UEdGraphPin* Pin) const;

	/** 在图形上执行标准验证(输出指向输入，每个输入不超过一个连接，两端类型匹配，等等) */
	bool ValidateGraphIsWellFormed(UEdGraph* Graph) const;

	/** 扫描图中指定类的节，并打印出警告 */
	virtual void PruneIsolatedNodes(const QList<UEdGraphNode*>& RootSet, QList<UEdGraphNode*>& GraphNodes);

	/**
	 * 对传入的节点(期望形成DAG)图执行拓扑排序，对它们进行调度。
	 * 如果图中存在循环或未连接的节点，对于每个未能进行调度的节点将输出一个错误。
	 */
	void CreateExecutionSchedule(const QList<UEdGraphNode*>& GraphNodes, /*out*/ QList<UEdGraphNode*>& LinearExecutionSchedule) const;

	/** 计数这个节点的输入边数(沿着所有输入引脚) */
	qint64 CountIncomingEdges(const UEdGraphNode* Node) const;

public:
	FCompilerResultsLog& MessageLog;
};


