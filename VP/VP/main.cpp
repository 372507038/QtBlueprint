#include "VPMainFrame.h"
#include <QtWidgets/QApplication>
#include "VPFramework.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

#if 1

    //QMainWindow* vpWindow = VPFramework::CreateEditor(QCoreApplication::applicationDirPath() + "/Archive/TestArchive.bp");
    //vpWindow->setWindowTitle("VP");
    //vpWindow->show();
    //vpWindow->move(0, 0);
    //vpWindow->resize(1200, 800);


    QMainWindow* k2Window = VPFramework::CreateK2Editor(QCoreApplication::applicationDirPath() + "/Archive/TestK2Archive.bp");
    k2Window->setWindowTitle("VP K2");
    k2Window->show();
    k2Window->move(100, 100);
    k2Window->resize(1400, 900);

    int ret = a.exec();

    //delete vpWindow;
    delete k2Window;

    return ret;

#else
    VPMainFrame w;
    w.show();
    return a.exec();

#endif
}
