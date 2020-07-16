#include "K2BlueprintEditor.h"

K2BlueprintEditor::K2BlueprintEditor()
	: BlueprintEditor()
{
}

K2BlueprintEditor::~K2BlueprintEditor()
{
}

/// virtual
QString K2BlueprintEditor::BlueprintType()
{
	return QString(typeid(K2UBlueprint).name());
}

/// virtual
UBlueprint* K2BlueprintEditor::CreateBlueprint(const QString& name)
{
	return K2UBlueprintFactories::CreateBlueprint(name);
}

/// virtual
IArchiveCreateObject K2BlueprintEditor::GetIArchiveCreateObject()
{
	return K2UObjectFactory::CreateObject;
}

