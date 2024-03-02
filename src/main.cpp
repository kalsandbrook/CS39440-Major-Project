#include <QApplication>

#include "data/gamedatabase.h"
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    GameDatabase db = GameDatabase::instance();
    db.open();
    db.setup();

    MainWindow mainWindow;

    mainWindow.resize(1280, 720);

    mainWindow.show();

    return QApplication::exec();
}
