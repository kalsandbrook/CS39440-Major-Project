#include "gameview.h"

#include "../data/model/gamelibrarymodel.h"
#include "gameeditdialog.h"
#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include <QSortFilterProxyModel>

GameView::GameView(QWidget* parent)
    : QTreeView(parent)
{
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setExpandsOnDoubleClick(false);
    setupContextMenu();

}

void GameView::setupContextMenu()
{
    QAction* editAction = new QAction("Edit", this);
    QAction* deleteAction = new QAction("Delete", this);

    connect(editAction, &QAction::triggered, this, &GameView::handleEdit);
    connect(deleteAction, &QAction::triggered, this, &GameView::handleDelete);

    addAction(editAction);
    addAction(deleteAction);
}

void GameView::handleEdit()
{
    QModelIndex index = currentIndex();
    if (index.isValid()) {
        // TODO: This should be moved.
        GameEditDialog editDialog(this);

        editDialog.exec(index.data(GameLibraryModel::GameRoles::IdRole).toInt());
    }
}

void GameView::handleDelete()
{
    QModelIndex index = currentIndex();
    if (index.isValid()) {
        GameLibrary::instance().deleteGame(index.data(GameLibraryModel::GameRoles::IdRole).toInt());
    }
}
