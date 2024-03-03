//
// Created by kal on 25/02/24.
//

#ifndef GAMEPILE_GAMEVIEW_H
#define GAMEPILE_GAMEVIEW_H

#include <QAbstractItemView>

/**
 * @brief A view for displaying games in a grid.
 * 
 * This class is a view for displaying games in a grid, and provides the functionality for scrolling, selecting, and navigating the list of games.
 *
 * It is a subclass of QAbstractItemView.
 *
 * At this time, it is not used in the application, but it will be used in future as a part of MainWindow.
 * @todo Implement the functionality for displaying the games in a grid.
*/
class GameView : public QAbstractItemView {
public:
    /**
     * @brief Constructs a new GameView object.
     * 
     * This constructor creates a new GameView object with the given parent.
     * 
     * @param parent The parent of the view.
    */
    GameView(QWidget* parent);

    QRect visualRect(const QModelIndex& index) const override;

    void scrollTo(const QModelIndex& index, ScrollHint hint) override;

    QModelIndex indexAt(const QPoint& point) const override;

protected:
    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;

    int horizontalOffset() const override;

    int verticalOffset() const override;

    bool isIndexHidden(const QModelIndex& index) const override;

    void setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags command) override;

    QRegion visualRegionForSelection(const QItemSelection& selection) const override;
};

#endif // GAMEPILE_GAMEVIEW_H
