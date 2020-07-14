/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:���ӻ���̽ӿ�
**************************************************/
#pragma once

#include "vpframework_global.h"
#include <QApplication>
#include <QMainWindow>

class VPFRAMEWORK_EXPORT VPFramework
{
public:
	/** zxf 2020-6-16
	* ָ����ͼ�ļ���������ͼ�༭��
	* 1�����ļ�������ʱ��������ͼ�ļ�������
	* 2�����ļ�����ʱ����ȡ��ͼ�ļ�������
	* 3������ͬʱ��һ���ļ������򷵻�nullptr��TODO��
	*/
	static QMainWindow* CreateEditor(QString fileName);
	static QMainWindow* CreateK2Editor(QString fileName);
};

