//
// Created by kal on 25/02/24.
//

#include "gameview.h"

QRect GameView::visualRect(const QModelIndex& index) const
{
    return QRect();
}

void GameView::scrollTo(const QModelIndex& index, QAbstractItemView::ScrollHint hint)
{
}

QModelIndex GameView::indexAt(const QPoint& point) const
{
    return QModelIndex();
}

QModelIndex GameView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    return QModelIndex();
}

int GameView::horizontalOffset() const
{
    return 0;
}

int GameView::verticalOffset() const
{
    return 0;
}

bool GameView::isIndexHidden(const QModelIndex& index) const
{
    return false;
}

void GameView::setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags command)
{
}

QRegion GameView::visualRegionForSelection(const QItemSelection& selection) const
{
    return QRegion();
}

GameView::GameView(QWidget* parent)
    : QAbstractItemView(parent)
{
}
