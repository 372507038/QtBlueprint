/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-16
Description:��ͼ������
**************************************************/
#pragma once

#include <QWidget>
#include "ui_SCompilerResults.h"

class SCompilerResults : public QWidget
{
	Q_OBJECT

public:
	SCompilerResults(QWidget *parent = Q_NULLPTR);
	~SCompilerResults();

private:
	Ui::SCompilerResults ui;
};
