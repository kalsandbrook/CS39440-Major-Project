//
// Created by kal on 24/02/24.
//

#ifndef GAMEPILE_GAMEITEMDELEGATE_H
#define GAMEPILE_GAMEITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class GameItemDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    explicit GameItemDelegate(QObject* parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


#endif //GAMEPILE_GAMEITEMDELEGATE_H
