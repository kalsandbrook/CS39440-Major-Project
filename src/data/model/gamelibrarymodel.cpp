//
// Created by Kal on 24/02/2024.
//

#include "gamelibrarymodel.h"

GameLibraryModel::GameLibraryModel(QObject* parent)
    : QAbstractItemModel(parent)
    , m_gameLibrary(GameLibrary::instance())
{
    connect(&m_gameLibrary, &GameLibrary::gameAdded, this, &GameLibraryModel::onGameAdded);
    connect(&m_gameLibrary, &GameLibrary::gameDeleted, this, &GameLibraryModel::onGameDeleted);
    connect(&m_gameLibrary, &GameLibrary::gameUpdated, this, &GameLibraryModel::onGameUpdated);
    const QList<Game>& games = m_gameLibrary.games().values();

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

    const Game& game = m_games.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0:
            return game.name();
        case 1:
            return game.desc();
        case 2:
            return game.genres();
        case 3:
            return game.status_str();
        default:
            return {};
        }
    case IdRole:
        return game.id();
    case NameRole:
        return game.name();
    case DescRole:
        return game.desc();
    case GenreRole:
        return game.genres();
    case StatusRole:
        return game.status();
    default:
        return {};
    }
}

QHash<int, QByteArray> GameLibraryModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles[NameRole] = "name";
    roles[DescRole] = "desc";
    roles[GenreRole] = "genres";
    roles[IdRole] = "id";
    roles[StatusRole] = "status";
    // Add other custom role names if needed
    return roles;
}

void GameLibraryModel::onGameAdded(const Game& game)
{
    int row = m_games.size();
    beginInsertRows(QModelIndex(), row, row);
    m_games.append(game);
    endInsertRows();
    // emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}
void GameLibraryModel::onGameDeleted(const int gameId)
{
    QModelIndexList matchingIndexes = match(index(0, 0), IdRole, gameId, 1, Qt::MatchExactly);

    if (!matchingIndexes.isEmpty()) {
        QModelIndex matchedIndex = matchingIndexes.first();

        beginRemoveRows(QModelIndex(), matchedIndex.row(), matchedIndex.row());
        m_games.removeAt(matchedIndex.row());
        endRemoveRows();
    }
}
void GameLibraryModel::onGameUpdated(const Game& game)
{
    QModelIndexList matchingIndexes = match(index(0, 0), IdRole, game.id(), 1, Qt::MatchExactly);

    if (!matchingIndexes.isEmpty()) {
        QModelIndex matchedIndex = matchingIndexes.first();

        m_games[matchedIndex.row()] = game;

        emit dataChanged(matchedIndex, matchedIndex, { Qt::DisplayRole, NameRole, DescRole, GenreRole, StatusRole });
    }
}

QVariant GameLibraryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section < columnCount() && orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return "Name";
        case 1:
            return "Description";
        case 2:
            return "Genres";
        case 3:
            return "Status";
        }
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

Game GameLibraryModel::getGame(QModelIndex index)
{
    return m_gameLibrary.getGameById(data(index, IdRole).toInt());
}