//
// Created by Kal on 23/02/2024.
//

#include "mainwindow.h"

#include "ui/gamedetailswidget.h"
#include "ui/gameitemdelegate.h"
#include <QSizePolicy>
#include <qnamespace.h>
#include <qstyleoption.h>

MainWindow::MainWindow()
{
    // TODO: Separate this constructor out into other functions to tidy it up. This is a mess.
    this->setWindowIcon(QIcon(":/icon.png"));

    helpMenu = new QMenu(helpButton);

    createActions();
    createToolBars();

    gameView = new GameView(this);
    gameLibraryModel = new GameLibraryModel(this);
    gameLibraryProxyModel = new QSortFilterProxyModel(this);
    gameLibraryProxyModel->setSourceModel(gameLibraryModel);

    gameView->setSortingEnabled(true);
    gameView->setModel(gameLibraryProxyModel);
    gameView->setItemDelegate(new GameItemDelegate(this));

    statusFilter = new StatusFilter(this);

    gameDetailsWidget = new GameDetailsWidget(this);

    QWidget* mainWidget = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(mainWidget);

    layout->addWidget(statusFilter,1);
    layout->addWidget(gameView,5);
    layout->addWidget(gameDetailsWidget,1);

    setCentralWidget(mainWidget);
    mainWidget->setLayout(layout);

    connect(gameView, &QAbstractItemView::clicked, gameDetailsWidget, &GameDetailsWidget::updateGame);

    connect(searchBar, &SearchBarWidget::searchUpdated, this, &MainWindow::onSearchUpdated);
    connect(statusFilter, &StatusFilter::filterChanged, this, &MainWindow::onStatusFilterUpdated);
    connect(statusFilter, &StatusFilter::filterCleared, this, &MainWindow::clearFilters);

    connect(addGameAction, &QAction::triggered, this, &MainWindow::onAddGameDialog);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAboutAction);
    connect(aboutQtAction, &QAction::triggered, this, &MainWindow::onAboutQtAction);
}

void MainWindow::createActions()
{
    addGameAction = new QAction(QIcon::fromTheme("list-add"), "&Add Game", this);
    aboutAction = new QAction(tr("About"),this);
    aboutAction -> setShortcut(QKeySequence("F1"));
    helpMenu->addAction(aboutAction);
    aboutQtAction = helpMenu->addAction(tr("About &Qt"));
}

void MainWindow::createToolBars()
{
    // Setup Main Toolbars
    mainToolBar = new QToolBar("Main Toolbar", this);
    mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    searchBar = new SearchBarWidget(this);

    helpButton = new QToolButton(this);
    helpButton->setIcon(QIcon::fromTheme("help-contextual"));
    helpButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    helpButton->setText(tr("&Help"));
    helpButton->setPopupMode(QToolButton::InstantPopup);

    // Main ToolBar layout:
    helpButton->setMenu(helpMenu);

    mainToolBar->addAction(addGameAction);
    mainToolBar->addSeparator();
    mainToolBar->addWidget(helpButton);
    mainToolBar->addSeparator();
    mainToolBar->addWidget(searchBar);

    addToolBar(mainToolBar);
}

void MainWindow::onAddGameDialog()
{
    addGameDialog = new GameEditDialog(this);
    addGameDialog->exec();
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

void MainWindow::onSearchUpdated(QString query)
{
    // TODO: Use Fuzzy Searching
    gameLibraryProxyModel->setFilterKeyColumn(0);
    gameLibraryProxyModel->setFilterRegularExpression(query);
}

void MainWindow::onStatusFilterUpdated(Game::Status statusFilter)
{
    // Filter by status - this will need to be changed as this only supports filtering by name OR status.
    gameLibraryProxyModel->setFilterKeyColumn(3);
    gameLibraryProxyModel->setFilterRegularExpression(GameHelper::statusToString(statusFilter));
}

void MainWindow::clearFilters()
{
    // Set filter to empty (match any pattern)
    gameLibraryProxyModel->setFilterRegularExpression(".*");
}
