#include "Blueprint.h"

UBlueprint::UBlueprint()
	: UObject()
{
}

UBlueprint::UBlueprint(const UObjectInfo& info)
	: UObject(info)
{
}

UBlueprint::UBlueprint(QString ObjectType, QString ObjectName)
	: UObject(ObjectType, ObjectName)
{
}

UBlueprint::UBlueprint(QString name)
	: UBlueprint(typeid(UBlueprint).name(), name)
{
}

UBlueprint::~UBlueprint()
{
}

void UBlueprint::Serialize(QDataStream & Ar) const
{
	__super::Serialize(Ar);

	Ar << m_Class << m_Graphs;

	int a = 0;
}

void UBlueprint::Deserialize(QDataStream & Ar)
{
	__super::Deserialize(Ar);

	Ar >> m_Class >> m_Graphs;

	int a = 0;
}

void UBlueprint::GetAllGraphs(QList<UEdGraph*>& Graphs) const
{
	//todo
}