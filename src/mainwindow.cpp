//
// Created by Kal on 23/02/2024.
//

#include "mainwindow.h"

#include "ui/gameitemdelegate.h"
#include "ui/gamedetailswidget.h"
#include <qnamespace.h>
#include <qstyleoption.h>
#include <QSizePolicy>

MainWindow::MainWindow()
{
    this->setWindowIcon(QIcon(":/icon.png"));

    mainToolBar = addToolBar("Main Toolbar");
    mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    addGameAction = new QAction(QIcon::fromTheme("list-add"), "&Add Game", this);
    mainToolBar->addAction(addGameAction);

    mainToolBar->addSeparator();

    searchBar = new SearchBarWidget(this);
    mainToolBar->addWidget(searchBar);


    mainToolBar->addSeparator();


    helpButton = new QToolButton(this);
    helpButton->setIcon(QIcon::fromTheme("help-contextual"));
    helpButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    helpButton->setText(tr("&Help"));
    helpButton->setPopupMode(QToolButton::InstantPopup);

    helpMenu = new QMenu(helpButton);
    aboutAction = helpMenu->addAction(tr("&About"));
    aboutQtAction = helpMenu->addAction(tr("About &Qt"));

    helpButton->setMenu(helpMenu);
    mainToolBar->addWidget(helpButton);

    filterToolBar = new FilterToolBar(this);
    addToolBar(Qt::LeftToolBarArea, filterToolBar);

    gameView = new GameView(this);
    gameLibraryModel = new GameLibraryModel(this);
    gameLibraryProxyModel = new QSortFilterProxyModel(this);
    gameLibraryProxyModel->setSourceModel(gameLibraryModel);

    gameView->setSortingEnabled(true);
    gameView->setModel(gameLibraryProxyModel);
    gameView->setItemDelegate(new GameItemDelegate(this));

    setCentralWidget(gameView);

    gameDetailsBar = new QToolBar("Game Details Toolbar",this);
    addToolBar(Qt::RightToolBarArea,gameDetailsBar);
    gameDetailsBar->setMovable(false);
    gameDetailsWidget = new GameDetailsWidget(gameLibraryModel,this);
    gameDetailsBar->addWidget(gameDetailsWidget);

    connect(gameView, &QAbstractItemView::clicked, gameDetailsWidget, &GameDetailsWidget::updateGame);

    connect(searchBar,&SearchBarWidget::searchUpdated,this,&MainWindow::onSearchUpdated);

    connect(addGameAction, &QAction::triggered, this,&MainWindow::onAddGameDialog);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAboutAction);
    connect(aboutQtAction, &QAction::triggered, this, &MainWindow::onAboutQtAction);
}

void MainWindow::onAddGameDialog() { addGameDialog->exec(); }

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

void MainWindow::onSearchUpdated(QString query) {
    // TODO: Use Fuzzy Searching
    gameLibraryProxyModel->setFilterRegularExpression(query);
}
