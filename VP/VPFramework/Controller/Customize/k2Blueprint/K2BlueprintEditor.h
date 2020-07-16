/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:蓝图控制K2
**************************************************/
#pragma once

#include "Controller/Blueprint/BlueprintEditor.h"
#include "Model/Customize/k2Blueprint/K2BlueprintFactories.h"


class K2BlueprintEditor : public BlueprintEditor
{
	Q_OBJECT

public:
	K2BlueprintEditor();
	virtual ~K2BlueprintEditor();

protected:
	/// virtual
	virtual QString BlueprintType();	//当前蓝图类名
	virtual UBlueprint* CreateBlueprint(const QString& name);	//创建Blueprint
	virtual IArchiveCreateObject GetIArchiveCreateObject();		//创建Object的接口
	/// virtual

};

