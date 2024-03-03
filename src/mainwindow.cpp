//
// Created by Kal on 23/02/2024.
//

#include "mainwindow.h"

#include "data/gamelibrary.h"
#include "gameitemdelegate.h"
#include <qnamespace.h>
#include <qstyleoption.h>

MainWindow::MainWindow()
    : gameLibrary(GameLibrary::instance())
{
    toolBar = addToolBar("Main Toolbar");
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    addGameAction = new QAction(QIcon::fromTheme("list-add"), "&Add Game", this);
    toolBar->addAction(addGameAction);
    toolBar->addSeparator();

    helpButton = new QToolButton(this);
    helpButton->setIcon(QIcon::fromTheme("help-contextual"));
    helpButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    helpButton->setText(tr("&Help"));
    helpButton->setPopupMode(QToolButton::InstantPopup);

    helpMenu = new QMenu(helpButton);
    aboutAction = helpMenu->addAction(tr("&About"));
    aboutQtAction = helpMenu->addAction(tr("About &Qt"));

    helpButton->setMenu(helpMenu);
    toolBar->addWidget(helpButton);

    gameListView = new QListView(this);
    gameLibraryModel = new GameLibraryModel(this);
    gameListView->setContextMenuPolicy(Qt::ActionsContextMenu);
    gameListView->setItemDelegate(new GameItemDelegate(this));
    gameListView->setModel(gameLibraryModel);
    setCentralWidget(gameListView);

    connect(addGameAction, &QAction::triggered, this,
        &MainWindow::onAddGameDialog);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAboutAction);
    connect(aboutQtAction, &QAction::triggered, this, &MainWindow::onAboutQtAction);
}

void MainWindow::onAddGameDialog() {
    AddGameDialog addGameDialog(this);
    addGameDialog.exec();
}

void MainWindow::onAboutAction()
{
    QMessageBox::about(this,
        "About GamePile",
        "A C++ Qt application designed to facilitate convenient and informative management of your video game collection."
        "\n\n"
        "Made by kas143 as a part of the CS39440 module at Aberystwyth University.");
}

void MainWindow::onAboutQtAction()
{
    QMessageBox::aboutQt(this);
}
