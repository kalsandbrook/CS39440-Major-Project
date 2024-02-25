//
// Created by Kal on 24/02/2024.
//

#include "gamelibrarymodel.h"

GameLibraryModel::GameLibraryModel(QObject* parent)
    : QAbstractItemModel(parent)
    , m_gameLibrary(GameLibrary::instance()) {};

QModelIndex GameLibraryModel::index(int row, int column,
    const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent)) {
        return {};
    }
    if (!parent.isValid()) {
        // For top level item, creates an index.
        return createIndex(row, column);
    }
    // If no child items:
    return {};
}

QModelIndex GameLibraryModel::parent(const QModelIndex& child) const
{
    // At the moment, this model is flat, so there are no parents.
    Q_UNUSED(child)
    return {};
}

int GameLibraryModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return m_gameLibrary.games().size();
    }
    return 0;
}

int GameLibraryModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    // This will be expanded to include other game properties soon
    return 3;
}

QVariant GameLibraryModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        if (index.row() < m_gameLibrary.games().size()) {
            const QSharedPointer<Game>& game = m_gameLibrary.games().at(index.row());
            switch (index.column()) {
            case 0:
                // Maybe change to use QSharedPointer<Game>& game =
                // m_gameLibrary.games().at(index.row());
                return game->name();
            case 1:
                return game->desc();
            case 2:
                return game->genre();
            default:
                return {};
            }
        }
    }

    return {};
}

void GameLibraryModel::addGame(const QSharedPointer<Game>& game)
{
    int row = m_gameLibrary.games().count();
    beginInsertRows(QModelIndex(), row, row);
    m_gameLibrary.addGame(game);
    endInsertRows();
}

QHash<int, QByteArray> GameLibraryModel::roleNames() const
{
    return QAbstractItemModel::roleNames();
}

void GameLibraryModel::deleteGameFromIndex(const QModelIndex &index) {
    if(!index.isValid()){
        return;
    }
    beginRemoveRows(index.parent(),index.row(),index.row());

    //m_gameLibrary.removeGame(index.data)

    endRemoveRows();

}
