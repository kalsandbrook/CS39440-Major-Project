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

#include "data/gamelibrarymodel.h"
#include "gamedetailswidget.h"
#include "gameitemdelegate.h"
#include "gameeditdialog.h"

GameItemDelegate::GameItemDelegate(QObject* parent)
        : QStyledItemDelegate(parent)
        , gameLibrary(GameLibrary::instance())
{}

void GameItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (!index.isValid())
        return;

    QString name = index.data().toString();

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter->setClipRect(option.rect);

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    QRect contentRect = option.rect.adjusted(2, 2, -2, -2);
    int lineHeight = QFontMetrics(option.font).height();

    QRect nameRect = QRect(contentRect.topLeft(), QSize(contentRect.width(), lineHeight*2));
    painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignTop, name);

    painter->restore();
}

QSize GameItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return { 200, 50 };
}
