/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:可视化编程接口
**************************************************/
#pragma once

#include "vpframework_global.h"
#include <QApplication>
#include <QMainWindow>

class VPFRAMEWORK_EXPORT VPFramework
{
public:
	/** zxf 2020-6-16
	* 指定蓝图文件，创建蓝图编辑器
	* 1、当文件不存在时，创建蓝图文件后启动
	* 2、当文件存在时，读取蓝图文件后启动
	* 3、不能同时打开一个文件，否则返回nullptr（TODO）
	*/
	static QMainWindow* CreateEditor(QString fileName);
	static QMainWindow* CreateK2Editor(QString fileName);
};

