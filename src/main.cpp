#include <QApplication>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;

    mainWindow.resize(1280,720);

    mainWindow.show();

    return QApplication::exec();
}
