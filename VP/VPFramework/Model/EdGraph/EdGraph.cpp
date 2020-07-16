#include "EdGraph.h"

UEdGraph::UEdGraph()
	: UObject()
{
}

UEdGraph::UEdGraph(const UObjectInfo& info)
	: UObject(info)
{
}

UEdGraph::~UEdGraph()
{
}

UEdGraph::UEdGraph(QString ObjectType, QString ObjectName)
	: UObject(ObjectType.isEmpty() ? typeid(UEdGraph).name() : ObjectType, ObjectName)
{
}

void UEdGraph::Serialize(QDataStream & Ar) const
{
	__super::Serialize(Ar);

	Ar << SchemaGuid << Nodes ;
}

void UEdGraph::Deserialize(QDataStream & Ar)
{
	__super::Deserialize(Ar);

	Ar >> SchemaGuid >> Nodes ;
}
