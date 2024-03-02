//
// Created by Kal on 23/02/2024.
//

#include "mainwindow.h"

#include "data/gamelibrary.h"
#include "gameitemdelegate.h"
#include <QToolBar>

/*!
 * \class MainWindow
 * \brief The MainWindow class is the main window of the application.
 *
 * It contains a toolbar with an action to add a game, and a list view to
 * display the games.
 *
 */
MainWindow::MainWindow()
    : gameLibrary(GameLibrary::instance())
{
    QToolBar* toolBar = addToolBar("Main Toolbar");
    addGameDialog = new AddGameDialog(this);

    addGameAction = toolBar->addAction(tr("Add Game"));

    gameListView = new QListView(this);
    gameLibraryModel = new GameLibraryModel(this);
    // gameListView->setResizeMode(QListView::Adjust);
    gameListView->setContextMenuPolicy(Qt::ActionsContextMenu);
    // gameListView->setGridSize({128,128});
    gameListView->setItemDelegate(new GameItemDelegate(this));
    gameListView->setModel(gameLibraryModel);
    setCentralWidget(gameListView);

    connect(addGameAction, &QAction::triggered, this,
        &MainWindow::onAddGameDialog);
}

void MainWindow::onAddGameDialog() { addGameDialog->exec(); }
