//
// Created by kal on 24/02/24.
//

#ifndef GAMEPILE_GAMEITEMDELEGATE_H
#define GAMEPILE_GAMEITEMDELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>

class GameItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit GameItemDelegate(QObject* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
private:
    GameLibrary& gameLibrary;
};

#endif // GAMEPILE_GAMEITEMDELEGATE_H
