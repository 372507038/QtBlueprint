#include "EdGraphNode.h"
#include "EdGraph.h"

UEdGraphNode::UEdGraphNode()
	: UObject()
{
}

UEdGraphNode::UEdGraphNode(const UObjectInfo& info)
	: UObject(info)
{
}

UEdGraphNode::UEdGraphNode(QString ObjectType, QString ObjectName)
	: UObject(ObjectType.isEmpty() ? typeid(UEdGraphNode).name() : ObjectType, ObjectName)
{
}

UEdGraphNode::~UEdGraphNode()
{
}

void UEdGraphNode::Serialize(QDataStream & Ar) const
{
	__super::Serialize(Ar);

	Ar << GraphGuid << Inputs << Outputs ;
}

void UEdGraphNode::Deserialize(QDataStream & Ar)
{
	__super::Deserialize(Ar);

	Ar >> GraphGuid >> Inputs >> Outputs ;
}
