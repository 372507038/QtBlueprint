/*************************************************
Copyright:Ver1.0
Author:zxf
Date:2020-06-12
Description:ͼ
**************************************************/
#pragma once

#include "SSCSNode.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsWidget>

class SSCSGraphScene;


class SSCSGraph : public QGraphicsView
{
public:
	SSCSGraph(QWidget* parent = nullptr);
	virtual ~SSCSGraph();

private:
	SSCSGraphScene* m_Scene;
};


class SSCSGraphScene : public QGraphicsScene
{
public:
	SSCSGraphScene(QObject* parent = nullptr) :QGraphicsScene(parent) {}
	virtual ~SSCSGraphScene() {}
};


