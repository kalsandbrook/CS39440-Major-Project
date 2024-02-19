#include <QApplication>
#include <QFile>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

#ifdef WIN32
    Q_INIT_RESOURCE(breeze);

    QFile file(":/dark/stylesheet.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    app.setStyleSheet(stream.readAll());
#endif

    MainWindow window;

    window.show();

    return QApplication::exec();
}
