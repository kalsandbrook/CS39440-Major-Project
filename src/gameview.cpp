//
// Created by kal on 25/02/24.
//

#include "gameview.h"

GameView::GameView(QWidget *parent) : QAbstractItemView(parent){}

QRect GameView::visualRect(const QModelIndex& index) const
{
    if(!index.isValid())
        return {};

    QRect itemRect = visualRect(index);

    return viewport()->rect().translated(horizontalOffset(),verticalOffset()).intersected(itemRect);
}

void GameView::scrollTo(const QModelIndex& index, QAbstractItemView::ScrollHint hint)
{
    if (!index.isValid())
        return;

    QRect rect = visualRect(index);
    QPoint targetPos = rect.center();
    QRect viewportRect = viewport()->rect();

    int dx = targetPos.x() - viewportRect.center().x();
    int dy = targetPos.y() - viewportRect.center().y();

    horizontalScrollBar()->setValue(horizontalScrollBar()->value() + dx);
    verticalScrollBar()->setValue(verticalScrollBar()->value() + dy);
}

QModelIndex GameView::indexAt(const QPoint& point) const
{
    QPoint viewportPoint = point + QPoint(horizontalOffset(), verticalOffset());
    return indexAt(viewportPoint);
}

QModelIndex GameView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    return QModelIndex();
}

int GameView::horizontalOffset() const
{
    QScrollBar *hScrollBar = horizontalScrollBar();
    if (hScrollBar)
    {
        // Return the current vertical scroll position of the viewport
        return hScrollBar->value();
    }
    else
    {
        // If there is no vertical scroll bar, return 0
        return 0;
    }
}

int GameView::verticalOffset() const
{
    QScrollBar *vScrollBar = verticalScrollBar();
    if (vScrollBar)
    {
        return vScrollBar->value();
    }
    else
    {
        return 0;
    }
}

bool GameView::isIndexHidden(const QModelIndex& index) const
{
    return false;
}

void GameView::setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags command)
{
    QModelIndex topLeftIndex = indexAt(rect.topLeft());
    QModelIndex bottomRightIndex = indexAt(rect.bottomRight());

    if (!topLeftIndex.isValid() || !bottomRightIndex.isValid())
        return;

    QItemSelection selection(topLeftIndex, bottomRightIndex);

    selectionModel()->select(selection, command);}

QRegion GameView::visualRegionForSelection(const QItemSelection& selection) const
{
    QRegion region;
    // Iterate over all selected indexes in the given selection
    for (const auto &indexRange : selection) {
        // Iterate over the range of indexes in the selection
        for (int row = indexRange.top(); row <= indexRange.bottom(); ++row) {
            for (int col = indexRange.left(); col <= indexRange.right(); ++col) {
                // Get the index for the current row and column
                QModelIndex index = model()->index(row, col);
                // Get the visual rectangle for the index and convert it to viewport coordinates
                QRect rect = visualRect(index).translated(-horizontalOffset(), -verticalOffset());
                // Add the rectangle to the region
                region += rect;
            }
        }
    }
    return region;
}
void GameView::paintEvent(QPaintEvent *event)
{
    QAbstractItemView::paintEvent(event);
}