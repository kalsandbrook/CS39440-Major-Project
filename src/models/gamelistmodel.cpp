//
// Created by Kal on 22/02/2024.
//

#include "gamelistmodel.h"

#include <iostream>
#include "../data/hardcoded-data.cpp"

#include <QModelIndex>
#include <QAbstractItemModel>

QModelIndex GameListModel::index(int row, int column, const QModelIndex &parent = QModelIndex()) const {
    if ( parent.isValid() || row < 0 || row >= m_data.size())
        return {};
    return createIndex(row, column, &m_data[row]);
}

QModelIndex GameListModel::parent(const QModelIndex &child) const {
    return {};
}

int GameListModel::rowCount(const QModelIndex& parent = QModelIndex()) const {
    if (parent.isValid())
        return 0;
    return m_data.size();
}
int GameListModel::columnCount(const QModelIndex &parent) const {
    return 3;
}
QVariant GameListModel::data(const QModelIndex &index, int role) const{
    if( !index.isValid() || index.row() < 0 || index.row() >= m_data.size())
        return {};
    const auto& entry = m_data[index.row()];
    if(role==Qt::DisplayRole) {
        switch(index.column()) {
            case 0: return entry.name();
            case 1: return entry.desc();
            case 2: return entry.genres();
            default: return {};
        }
    }
    return {};
}

void GameListModel::addEntry(const GameEntry& newGame) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_data.reserve(m_data.size()+1);
    m_data.append(GameEntry(newGame));

    endInsertRows();
}

void GameListModel::populate() {
    // TODO: Proper game loading, this is a temporary solution.
    beginResetModel();
    m_data.clear();
    m_data.reserve(3);
    m_data.append(gameList[0]);
    m_data.append(gameList[1]);
    m_data.append(gameList[2]);
    endResetModel();
}

