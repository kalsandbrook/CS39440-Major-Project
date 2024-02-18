//
// Created by Kal on 18/02/2024.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
private slots:
    void about();
    void aboutQt();
private:
    void createActions();
    void createMenus();

    QMenu *helpMenu;

    QAction *aboutAct;
    QAction *aboutQtAct;
    QLabel *infoLabel;
};

#endif //MAINWINDOW_H
