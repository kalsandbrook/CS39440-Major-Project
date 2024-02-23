//
// Created by Kal on 18/02/2024.
//

#include "mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QVBoxLayout>

#include "models/gamelistmodel.h"
#include "models/gameListDelegate.cpp"
#include "data/hardcoded-data.cpp"

MainWindow::MainWindow()
{
    auto* widget = new QWidget;
    setCentralWidget(widget);

    auto* topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    gameListView = new QListView(this);
    gameListModel = new GameListModel(this);
    auto* gameListDelegate = new GameListDelegate(this);
    gameListView -> setModel(gameListModel);
    gameListView -> setItemDelegate(gameListDelegate);
    gameListModel -> populate();

    auto* bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto* layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(topFiller);
    layout->addWidget(gameListView);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle(tr("GamePile"));
    setMinimumSize(800, 600);
    resize(1280, 720);
}

void MainWindow::createActions()
{
    mainToolBar = addToolBar(tr("Main Toolbar"));

    addGameAct = new QAction(tr("&Add Game"), this);
    addGameAct->setShortcuts(QKeySequence::New);
    addGameAct->setStatusTip(tr("Add a new game to the database."));
    addGameAct->setIcon(QIcon::fromTheme("new"));
    mainToolBar->addAction(addGameAct);

    connect(addGameAct, &QAction::triggered, this, &MainWindow::addGame);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setShortcuts(QKeySequence::HelpContents);
    aboutAct->setStatusTip(tr("Show help information."));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction(tr("&About Qt"), this);
    aboutQtAct->setStatusTip(tr("Show information about Qt."));
    connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);
}

void MainWindow::createMenus()
{
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::addGame() const {
    // TODO: Implement proper addition of games.
}

void MainWindow::about()
{
    const auto title QStringLiteral("GamePile");
    const auto infoText QStringLiteral(
        "This is an application that helps users manage their video game collections. "
        "\n\n © Aberystwyth University, kas143");

    QMessageBox::about(this, title, infoText);
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}