#include <QApplication>
#include <QPushButton>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;

    window.show();

    return QApplication::exec();
}
