//
// Created by Kal on 23/02/2024.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QListView>
#include <QMainWindow>
#include <QTableView>

#include "addgamedialog.h"
#include "data/gamelibrarymodel.h"
#include "gameview.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

public slots:
    void onAddGameDialog();
    void onGameAdded(const QSharedPointer<Game>& game);

private:
    QListView* gameListView;
    GameLibraryModel* gameLibraryModel;
    AddGameDialog* addGameDialog;
    QAction* addGameAction;
};

#endif // MAINWINDOW_H
