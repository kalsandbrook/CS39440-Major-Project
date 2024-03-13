//
// Created by Kal on 22/02/2024.
//
#include <QEvent>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QTextItem>
#include <QVBoxLayout>

#include "gameitemdelegate.h"

GameItemDelegate::GameItemDelegate(QObject *parent)
        : QStyledItemDelegate(parent) {
}

void GameItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid()) return;

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter->setClipRect(option.rect);

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    QRect contentRect = option.rect.adjusted(2,0,-2,0);

    int lineHeight = QFontMetrics(option.font).height();

    QRect iconRect;
    QRect valueRect;
    // This is throwing an error, and I'm not sure why
    QIcon icon = index.data(Qt::DecorationRole).value<QIcon>();


    if (index.column() == 0) {

        iconRect = QRect(contentRect.topLeft(), QSize(lineHeight * 3, lineHeight * 3));
        icon.paint(painter, iconRect);
        valueRect = QRect(iconRect.topRight(), QSize(contentRect.width()+11 - lineHeight*3, lineHeight * 3));

    } else {
        valueRect = QRect(contentRect.topLeft(), QSize(contentRect.width(), lineHeight * 3));
    }

    painter->drawText(valueRect, Qt::AlignLeft | Qt::AlignVCenter, index.data().toString());

    painter->restore();
}

QSize GameItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    int height = QFontMetrics(option.font).height()*3;
    height += 2;

    return {200, height};
}
