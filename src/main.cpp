#include <QApplication>

#include "mainwindow.h"
#include "data/gamelibrary.h"

/**
 * The main entry function. This initialises and sets up the application and databases, then shows the Main Window.
 * @see MainWindow()
 *
 */
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;

    mainWindow.resize(1280, 720);

    mainWindow.show();

    return QApplication::exec();
}

/**
 * \mainpage GamePile Documentation
 * \author Kal Sandbrook - kas143
 * \date 2024-03-03
 *
 *
 * This is the documentation for the GamePile application. GamePile is a C++ Qt application designed to facilitate convenient and informative management of your video game collection.
 *
 * This project is being made as a part of the CS39440 module at Aberystwyth University.
 *
 */
