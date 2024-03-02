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
#include "gameitemdelegate.h"

GameItemDelegate::GameItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void GameItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (!index.isValid())
        return;

    // Retrieve data for each field
    int id = index.model()->data(index.siblingAtColumn(0)).toInt();
    QString name = index.model()->data(index.siblingAtColumn(1)).toString();
    QString description = index.model()->data(index.siblingAtColumn(2)).toString();
    QString genres = index.model()->data(index.siblingAtColumn(3)).toString();

    // Set up the painter with the style options
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter->setClipRect(option.rect);

    // Draw background color for selected items
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    // Calculate the layout for the delegate's contents
    QRect contentRect = option.rect.adjusted(2, 2, -2, -2); // Adjust for margins
    int lineHeight = QFontMetrics(option.font).height(); // Height of each line

    // Paint the name
    QRect nameRect = QRect(contentRect.topLeft(), QSize(contentRect.width() / 3, lineHeight));
    painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignTop, name);

    // Paint the description
    QRect descriptionRect = nameRect.translated(0, lineHeight);
    painter->drawText(descriptionRect, Qt::AlignLeft | Qt::AlignTop, description);

    // Paint the description
    QRect genreRect = nameRect.translated(nameRect.width(), 0);
    painter->drawText(genreRect, Qt::AlignLeft | Qt::AlignTop, genres);

    painter->restore();
}

QSize GameItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return { 200, 50 }; // Adjust size as needed
}

bool GameItemDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option,
    const QModelIndex& index)
{

    auto* gameModel = qobject_cast<GameLibraryModel*>(model);

    if (event->type() == QEvent::MouseButtonRelease) {
        auto* mouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::RightButton) {
            QMenu menu;
            QAction* editAction = menu.addAction("Edit");
            menu.addSeparator();
            QAction* deleteAction = menu.addAction("Delete");

            QAction* selectedAction = menu.exec(mouseEvent->globalPosition().toPoint());
            if (selectedAction == editAction) {
                // Action 1 was triggered
            } else if (selectedAction == deleteAction) {
                // gameModel.deleteGameFromIndex(index);
            }
            return true;
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
