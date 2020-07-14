#include "VPFramework.h"
#include "Engine/Blueprint/BlueprintEditor.h"
#include "Engine/Customize/k2Blueprint/K2BlueprintEditor.h"
#include <QMetaType>

QMainWindow* VPFramework::CreateEditor(QString fileName)
{
	BlueprintEditor* editor = new BlueprintEditor;
	editor->Init(fileName);
	return editor->GetMainWindow();
}

QMainWindow* VPFramework::CreateK2Editor(QString fileName)
{
	K2BlueprintEditor* k2editor = new K2BlueprintEditor;
	k2editor->Init(fileName);
	return k2editor->GetMainWindow();
}
