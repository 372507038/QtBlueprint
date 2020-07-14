#include "EdGraphCompilerUtilities.h"

FGraphCompilerContext::FGraphCompilerContext(FCompilerResultsLog& InMessageLog)
	: MessageLog(InMessageLog)
{
}

void FGraphCompilerContext::ValidateLink(const UEdGraphPin * PinA, const UEdGraphPin * PinB) const
{
}
void FGraphCompilerContext::ValidatePin(const UEdGraphPin * Pin) const
{
}
void FGraphCompilerContext::ValidateNode(const UEdGraphNode * Node) const
{
}
bool FGraphCompilerContext::CanIgnoreNode(const UEdGraphNode * Node) const
{
	return false;
}

bool FGraphCompilerContext::ShouldForceKeepNode(const UEdGraphNode * Node) const
{
	return false;
}

UEdGraphNode * FGraphCompilerContext::FindNodeByClass(const UEdGraph * Graph, QPointer<UEdGraphNode> NodeClass, bool bExpectedUnique) const
{
	return nullptr;
}

bool FGraphCompilerContext::PinIsImportantForDependancies(const UEdGraphPin * Pin) const
{
	return false;
}

bool FGraphCompilerContext::ValidateGraphIsWellFormed(UEdGraph * Graph) const
{
	return false;
}

void FGraphCompilerContext::PruneIsolatedNodes(const QList<UEdGraphNode*>& RootSet, QList<UEdGraphNode*>& GraphNodes)
{
}

void FGraphCompilerContext::CreateExecutionSchedule(const QList<UEdGraphNode*>& GraphNodes, QList<UEdGraphNode*>& LinearExecutionSchedule) const
{
}

qint64 FGraphCompilerContext::CountIncomingEdges(const UEdGraphNode * Node) const
{
	return qint64();
}

