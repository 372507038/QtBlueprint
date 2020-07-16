#include "CommEnum.h"

QString ToString(EBlueprintItemType type)
{
	QString str;
	switch (type)
	{
	case EBlueprintItemType::None:		str = "None";		break;
	case EBlueprintItemType::Function:	str = "Function";	break;
	case EBlueprintItemType::Member:	str = "Member";		break;
	}
	return str;
}

QString ToString(EBlueprintItemDetailType type)
{
	QString str;
	switch (type)
	{
	case EBlueprintItemDetailType::Function:		str = "Function";		break;
	case EBlueprintItemDetailType::Input:			str = "Input";			break;
	case EBlueprintItemDetailType::Output:			str = "Output";			break;
	case EBlueprintItemDetailType::Variable:		str = "Variable";		break;
	case EBlueprintItemDetailType::DefaultValue:	str = "DefaultValue";	break;
	}
	return str;
}

QString ToString(EBlueprintEditorKey type)
{
	QString str;
	switch (type)
	{
	case EBlueprintEditorKey::None:
		str = "None";
		break;
	case EBlueprintEditorKey::FunctionName:
		str = "FunctionName";
		break;
	case EBlueprintEditorKey::EFunctionAbstraction:
		str = "Abstraction";
		break;
	case EBlueprintEditorKey::EFieldModifiers:
		str = "Modifiers";
		break;
	case EBlueprintEditorKey::EAccessSpecifier:
		str = "Access Specifier";
		break;
	case EBlueprintEditorKey::VariableName:
		str = "Variable Name";
		break;
	case EBlueprintEditorKey::VariableType:
		str = "Variable Type";
		break;
	case EBlueprintEditorKey::DefaultValue:
		str = "Default Value";
		break;
	}
	return str;
}

