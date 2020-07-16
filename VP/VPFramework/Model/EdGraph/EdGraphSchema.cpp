#include "EdGraphSchema.h"
#include "EdGraph.h"

UEdGraphSchema::UEdGraphSchema()
	: UObject()
{
}

UEdGraphSchema::UEdGraphSchema(const UObjectInfo& info)
	: UObject(info)
{
}

UEdGraphSchema::UEdGraphSchema(QString ObjectType, QString ObjectName)
	: UObject(ObjectType.isEmpty() ? typeid(UEdGraphSchema).name() : ObjectType, ObjectName)
{
}

UEdGraphSchema::~UEdGraphSchema()
{
}
