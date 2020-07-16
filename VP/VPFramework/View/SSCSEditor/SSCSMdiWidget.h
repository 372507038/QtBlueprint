/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:À¶Í¼±à¼­´°¿Ú
**************************************************/
#pragma once

#include "ui_SSCSMdiWidget.h"
#include "SSCSGraph.h"


class SSCSMdiWidget : public QWidget
{
	Q_OBJECT

public:
	SSCSMdiWidget(QWidget *parent = Q_NULLPTR);
	~SSCSMdiWidget();

	void InitUI(QString name);

	SSCSGraph* Graph();

private:
	Ui::SSCSMdiWidget ui;
};
