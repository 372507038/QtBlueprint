/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:��ͼ�༭����
**************************************************/
#pragma once

#include "SSCSMdiWidget.h"
#include "ui_SSCSEditor.h"
#include <QMdiSubWindow>


class SSCSEditor : public QWidget
{
	Q_OBJECT

public:
	SSCSEditor(QWidget* parent = Q_NULLPTR);
	~SSCSEditor();

	void InitUI();

private:
	Ui::SSCSEditor ui;
};
