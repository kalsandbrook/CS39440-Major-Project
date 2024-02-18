//
// Created by Kal on 18/02/2024.
//

#include <QVBoxLayout>
#include <QMessageBox>
#include <QMenuBar>
#include "mainwindow.h"

MainWindow::MainWindow() {
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new QLabel(tr("A test program, to see how Qt works with C++."));

    infoLabel -> setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel -> setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(5,5,5,5);
    layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle(tr("GamePile"));
    setMinimumSize(800,600);
    resize(1280,720);
}

void MainWindow::createActions() {
    aboutAct = new QAction(tr("&About"), this);
    aboutAct -> setShortcuts(QKeySequence::HelpContents);
    aboutAct -> setStatusTip(tr("Show help information."));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction(tr("&About Qt"), this);
    aboutQtAct -> setStatusTip(tr("Show information about Qt."));
    connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);
}

void MainWindow::createMenus() {
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu -> addAction(aboutAct);
    helpMenu -> addAction(aboutQtAct);
}

void MainWindow::about(){
    auto title = QStringLiteral("GamePile");
    auto infoText QStringLiteral("This is an application that helps users manage their video game collections. \n\n © Aberystwyth University, kas143");

    QMessageBox::about(this,title,infoText);
}

void MainWindow::aboutQt() {
    QMessageBox::aboutQt(this);
}