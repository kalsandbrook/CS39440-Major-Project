//
// Created by kal on 24/02/24.
//

#ifndef GAMEPILE_GAMEITEMDELEGATE_H
#define GAMEPILE_GAMEITEMDELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>

/**
 * @brief A delegate for painting game items in a list view.
 * 
 * This class is a delegate for painting game items in a list view.
*/
class GameItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    /**
     * @brief Constructs a new GameItemDelegate object.
     * 
     * This constructor creates a new GameItemDelegate object with the given parent.
     * 
     * @param parent The parent of the delegate.
    */
    explicit GameItemDelegate(QObject* parent = nullptr);

    /**
     * @brief Paints the game item.
     * 
     * This method paints the game item using the given painter, style option, and model index.
     * 
     * @param painter The painter to use for painting the item.
     * @param option The style option for the item.
     * @param index The model index of the item.
    */
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    /**
     * @brief Handles editor events.
     * 
     * This method handles editor events (such as the context menu) for the given event, model, style option, and model index.
     * 
     * @param event The event to handle.
     * @param model The model to use.
     * @param option The style option to use.
     * @param index The model index to use.
     * @return True if the event was handled, false if not.
    */
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;

    /**
     * @brief Returns the size hint for the game item.
     * 
     * This method returns the size hint for the game item using the given style option and model index.
     * 
     * The size hint is the recommended size of the delegate.
     *  
     * @param option The style option for the item.
     * @param index The model index of the item.
     * @return The size hint for the item.
    */
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

private:
    GameLibrary& gameLibrary;
};

#endif // GAMEPILE_GAMEITEMDELEGATE_H
