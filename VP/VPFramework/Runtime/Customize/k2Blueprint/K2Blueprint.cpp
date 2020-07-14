#include "K2Blueprint.h"

K2UBlueprint::K2UBlueprint()
	: UBlueprint()
{
}

K2UBlueprint::K2UBlueprint(const UObjectInfo& info)
	: UBlueprint(info)
{
}

K2UBlueprint::K2UBlueprint(QString ObjectType, QString ObjectName)
	: UBlueprint(ObjectType, ObjectName)
{
}

K2UBlueprint::K2UBlueprint(QString name)
	: K2UBlueprint(typeid(K2UBlueprint).name(), name)
{
}

K2UBlueprint::~K2UBlueprint()
{
}
