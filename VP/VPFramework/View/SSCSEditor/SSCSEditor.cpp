#include "SSCSEditor.h"

SSCSEditor::SSCSEditor(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

SSCSEditor::~SSCSEditor()
{
}

void SSCSEditor::InitUI()
{
	//add test
	for (int i = 0; i < 3; i++)
	{
		QString name = "Test Graph " + QString::number(i + 1);

		SSCSMdiWidget* mdiWidget = new SSCSMdiWidget;
		mdiWidget->InitUI(name);

		QMdiSubWindow* subWindow = ui.mdiArea->addSubWindow(mdiWidget);
		subWindow->setWindowTitle(name);
	}
}
