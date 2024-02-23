//
// Created by Kal on 18/02/2024.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QListView>

#include "models/gamelistmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private slots:
    void addGame() const;
    void about();
    void aboutQt();

private:
    void createActions();
    void createMenus();

    QMenu* helpMenu;
    QToolBar* mainToolBar;

    QAction* addGameAct;
    QAction* aboutAct;
    QAction* aboutQtAct;

    // TODO: Update this to custom QAbstractItemView class
    QListView* gameListView;
    GameListModel* gameListModel;
};

#endif //MAINWINDOW_H
