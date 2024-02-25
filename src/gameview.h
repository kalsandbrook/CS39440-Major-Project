//
// Created by kal on 25/02/24.
//

#ifndef GAMEPILE_GAMEVIEW_H
#define GAMEPILE_GAMEVIEW_H

#include <QAbstractItemView>

class GameView : public QAbstractItemView{
public:
    GameView(QWidget* parent);

    QRect visualRect(const QModelIndex &index) const override;

    void scrollTo(const QModelIndex &index, ScrollHint hint) override;

    QModelIndex indexAt(const QPoint &point) const override;

protected:
    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;

    int horizontalOffset() const override;

    int verticalOffset() const override;

    bool isIndexHidden(const QModelIndex &index) const override;

    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) override;

    QRegion visualRegionForSelection(const QItemSelection &selection) const override;
};


#endif //GAMEPILE_GAMEVIEW_H
