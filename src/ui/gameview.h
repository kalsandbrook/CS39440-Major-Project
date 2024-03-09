//
// Created by kal on 25/02/24.
//

#ifndef GAMEPILE_GAMEVIEW_H
#define GAMEPILE_GAMEVIEW_H

#include <QTreeView>
#include <QScrollBar>

/**
 * @brief A view for displaying games in a grid.
 * 
 * This class is a view for displaying games in a list, and provides the functionality for scrolling, selecting, and navigating the list of games.
 *
 *
 * It is a subclass of QTreeView.
 *
 * In future, this may instead display games in a grid, instead subclassing QAbstractItemView.
 * @todo Investigate grid views
*/
class GameView : public QTreeView {
public:
    /**
     * @brief Constructs a new GameView object.
     * 
     * This constructor creates a new GameView object with the given parent.
     * 
     * @param parent The parent of the view.
    */
    GameView(QWidget* parent);

protected:
    void setupContextMenu();

private slots:
    void handleEdit();
    void handleDelete();
};

#endif // GAMEPILE_GAMEVIEW_H
