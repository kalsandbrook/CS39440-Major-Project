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


/*!
 * \class MainWindow
 * \brief The MainWindow class is the main window of the application.
 *
 * It contains a toolbar with an action to add a game, and a list view to
 * display the games.
 *
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

public slots:
    void onAddGameDialog();

private:
    QListView* gameListView;
    GameLibrary& gameLibrary;
    GameLibraryModel* gameLibraryModel;
    AddGameDialog* addGameDialog;
    QAction* addGameAction;
};

#endif // MAINWINDOW_H
