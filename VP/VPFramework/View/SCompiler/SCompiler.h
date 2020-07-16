/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-16
Description:¿∂Õº±‡“Îπ§æﬂ¿∏
**************************************************/
#pragma once

#include <QWidget>
#include "ui_SCompiler.h"

class SCompiler : public QWidget
{
	Q_OBJECT

public:
	SCompiler(QWidget *parent = Q_NULLPTR);
	~SCompiler();

private:
	Ui::SCompiler ui;
};
