/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-22
Description:¿∂ÕºUI≥£”√
**************************************************/
#pragma once

#include <QObject>


enum class EBlueprintItemType
{
	None,
	Function,
	Member,
};
extern QString ToString(EBlueprintItemType type);


enum class EBlueprintItemDetailType
{
	Function,
	Input,
	Output,
	Variable,
	DefaultValue,
};
extern QString ToString(EBlueprintItemDetailType type);


enum class EBlueprintEditorKey
{
	None,
	FunctionName,			//Function Item
	EFunctionAbstraction,	//Function Item
	EFieldModifiers,		//Function Item
	EAccessSpecifier,		//Function Item
	VariableName,			//Variable Item
	VariableType,			//Variable Item
	DefaultValue,			//Variable Item
};
extern QString ToString(EBlueprintEditorKey type);


