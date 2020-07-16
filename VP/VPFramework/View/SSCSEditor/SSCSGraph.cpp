#include "SSCSGraph.h"

SSCSGraph::SSCSGraph(QWidget* parent)
	: QGraphicsView(parent)
{
	m_Scene = new SSCSGraphScene(this);
	this->setScene(m_Scene);
}

SSCSGraph::~SSCSGraph()
{
}
