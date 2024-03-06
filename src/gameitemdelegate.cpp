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
#include "addgamedialog.h"

GameItemDelegate::GameItemDelegate(QObject* parent)
        : QStyledItemDelegate(parent)
        , gameLibrary(GameLibrary::instance())
{
}

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

    QRect nameRect = QRect(contentRect.topLeft(), QSize(contentRect.width() / 3, lineHeight));
    painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignTop, name);

//    QRect descriptionRect = nameRect.translated(0, lineHeight);
//    painter->drawText(descriptionRect, Qt::AlignLeft | Qt::AlignTop, description);
//
//    QRect genreRect = nameRect.translated(nameRect.width(), 0);
//    painter->drawText(genreRect, Qt::AlignLeft | Qt::AlignTop, genres);

    painter->restore();
}

QSize GameItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return { 200, 50 };
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
                if (gameModel) {
                    QVariant gameIdVariant = index.data(GameLibraryModel::IdRole);
                    if (gameIdVariant.isValid()) {
                        int gameId = gameIdVariant.toInt();
                        AddGameDialog dialog;
                        dialog.exec(gameId);
                    }
                }
            } else if (selectedAction == deleteAction) {
                if (gameModel) {
                    QVariant gameIdVariant = index.data(GameLibraryModel::IdRole);
                    if (gameIdVariant.isValid()) {
                        int gameId = gameIdVariant.toInt();
                        gameLibrary.deleteGame(gameId);
                    }
                }
            }
            return true;
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
