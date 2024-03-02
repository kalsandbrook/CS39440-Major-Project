//
// Created by Kal on 24/02/2024.
//

#include "gamelibrarymodel.h"

GameLibraryModel::GameLibraryModel(QObject* parent)
    : QAbstractItemModel(parent)
    , m_gameLibrary(GameLibrary::instance())
{
    connect(&m_gameLibrary, &GameLibrary::gameAdded, this, &GameLibraryModel::onGameAdded);
    const QList<Game>& games = m_gameLibrary.games();

    // Insert data into the model
    for (const Game& game : games) {
        // Create a QModelIndex for the new row
        QModelIndex index = createIndex(m_games.size(), 0);

        beginInsertRows(QModelIndex(), index.row(), index.row());
        // Append the game to the model's internal list
        m_games.append(game);

        // Notify views of the new row
        endInsertRows();
    }
};

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
        return m_games.size();
    }
    return 0;
}

int GameLibraryModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    // This will be expanded to include other game properties soon
    return 4;
}

QVariant GameLibraryModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        if (index.row() < m_games.size()) {
            const Game& game = m_games.at(index.row());
            switch (index.column()) {
            case 0:
                return game.getId();
            case 1:
                return game.name();
            case 2:
                return game.desc();
            case 3:
                return game.genre();
            default:
                return {};
            }
        }
    }

    return {};
}

// void GameLibraryModel::addGame(const Game& game)
// {
//     int row = m_gameLibrary.games().count();
//     beginInsertRows(QModelIndex(), row, row);
//     m_gameLibrary.addGame(game);
//     endInsertRows();
// }

QHash<int, QByteArray> GameLibraryModel::roleNames() const
{
    return QAbstractItemModel::roleNames();
}

void GameLibraryModel::onGameAdded(const Game& game)
{
    m_games.append(game);
    emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

void GameLibraryModel::deleteGameFromIndex(const QModelIndex& index)
{
    if (!index.isValid()) {
        return;
    }
    beginRemoveRows(index.parent(), index.row(), index.row());

    // m_gameLibrary.removeGame(index.data)

    endRemoveRows();
}
