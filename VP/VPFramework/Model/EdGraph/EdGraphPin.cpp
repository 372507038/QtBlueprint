#include "EdGraphPin.h"
#include "EdGraphSchema.h"
#include "EdGraphNode.h"

UEdGraphPin::UEdGraphPin()
	: UObject()
{
}

UEdGraphPin::UEdGraphPin(const UObjectInfo& info)
	: UObject(info)
{
}

UEdGraphPin::UEdGraphPin(QString ObjectType, QString ObjectName)
	: UObject(ObjectType.isEmpty() ? typeid(UEdGraphPin).name() : ObjectType, ObjectName)
{
}

UEdGraphPin::~UEdGraphPin()
{
}

void UEdGraphPin::Serialize(QDataStream & Ar) const
{
	__super::Serialize(Ar);

	Ar << NodeGuid << ConnPinGuid;
}

void UEdGraphPin::Deserialize(QDataStream & Ar)
{
	__super::Deserialize(Ar);

	Ar >> NodeGuid >> ConnPinGuid;
}
