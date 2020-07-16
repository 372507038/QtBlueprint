#include "SSCSMdiWidget.h"

SSCSMdiWidget::SSCSMdiWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

SSCSMdiWidget::~SSCSMdiWidget()
{
}

void SSCSMdiWidget::InitUI(QString name)
{
	ui.label->setText(name);
}

SSCSGraph* SSCSMdiWidget::Graph()
{
	return ui.graphicsView;
}
