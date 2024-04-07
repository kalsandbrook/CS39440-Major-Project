//
// Created by Kal on 22/02/2024.
//
#include <QEvent>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QStyledItemDelegate>
#include <QTextItem>
#include <QVBoxLayout>

#include "gameitemdelegate.h"

GameItemDelegate::GameItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void GameItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (!index.isValid())
        return;

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter->setClipRect(option.rect);

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    QRect contentRect = option.rect.adjusted(2, 0, -2, 0);

    int lineHeight = QFontMetrics(option.font).height();

    QRect iconRect;
    QRect valueRect;
    // This is throwing an error, and I'm not sure why - update: it's just CLion being weird.
    QVariant data = index.data(Qt::DecorationRole);
    QSize iconSize(lineHeight * 3, lineHeight * 3);

    if (index.column() == 0) {

        iconRect = QRect(contentRect.topLeft(), iconSize).adjusted(0, 2, 0, 0);
        if (data.canConvert<QIcon>()) {
            QIcon icon = data.value<QIcon>();
            icon.paint(painter, iconRect);
        } else if (data.canConvert<QImage>()) {
            QImage image = data.value<QImage>();
            painter->drawImage(iconRect, image);
        }
        valueRect = QRect(iconRect.topRight(), QSize(contentRect.width() - lineHeight * 3, lineHeight * 3)).adjusted(11, -2, 0, 0);

    } else {
        valueRect = QRect(contentRect.topLeft(), QSize(contentRect.width(), lineHeight * 3));
    }

    painter->drawText(valueRect, Qt::AlignLeft | Qt::AlignVCenter, index.data().toString());

    painter->restore();
}

QSize GameItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    int height = QFontMetrics(option.font).height() * 3;
    height += 2;

    return { 200, height };
}
