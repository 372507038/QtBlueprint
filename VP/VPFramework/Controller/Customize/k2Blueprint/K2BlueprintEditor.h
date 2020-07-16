/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:��ͼ����K2
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
	virtual QString BlueprintType();	//��ǰ��ͼ����
	virtual UBlueprint* CreateBlueprint(const QString& name);	//����Blueprint
	virtual IArchiveCreateObject GetIArchiveCreateObject();		//����Object�Ľӿ�
	/// virtual

};

