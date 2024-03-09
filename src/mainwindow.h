//
// Created by Kal on 23/02/2024.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QListView>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QTreeView>
#include <QToolBar>
#include <QToolButton>
#include <QSortFilterProxyModel>

#include "ui/searchbarwidget.h"
#include "ui/gameview.h"
#include "ui/gameeditdialog.h"
#include "data/model/gamelibrarymodel.h"
#include "ui/gamedetailswidget.h"

/**
 * @brief The MainWindow class is the main window of the application.
 * 
 * This class represents the main window of the application, and contains the toolbar, game list view, and other UI elements.
 * 
 * It is a subclass of QMainWindow.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    /**
     * @brief Constructs a new MainWindow object.
     * 
     * This constructor creates a new MainWindow object.
     */
    MainWindow();

public slots:
    /**
     * @brief Shows the add game dialog.
     * 
     * This method shows the add game dialog.
     */
    void onAddGameDialog();

    /**
     * @brief Shows the about dialog.
     * 
     * This method shows the about dialog.
     */
    void onAboutAction();

    /**
     * @brief Shows the about Qt dialog.
     * 
     * This method shows the about Qt dialog.
     */
    void onAboutQtAction();

    void onSearchUpdated(QString query);

private:
    QToolBar* mainToolBar;
    QToolButton* helpButton;
    QMenu* helpMenu;
    SearchBarWidget* searchBar;

    QToolBar* gameDetailsBar;
    GameDetailsWidget* gameDetailsWidget;

    QAction* addGameAction;

    QAction* aboutAction;
    QAction* aboutQtAction;

    GameView* gameView;
    GameLibraryModel* gameLibraryModel;
    QSortFilterProxyModel* gameLibraryProxyModel;
    GameEditDialog* addGameDialog;
};

#endif // MAINWINDOW_H
