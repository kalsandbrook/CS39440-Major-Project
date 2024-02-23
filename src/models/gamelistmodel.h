//
// Created by Kal on 22/02/2024.
//

#ifndef GAMELISTMODEL_H
#define GAMELISTMODEL_H

#include "../data/gameentry.h"

#include <qabstractitemmodel.h>

class GameListModel : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit GameListModel(QObject* parent = nullptr): QAbstractItemModel(parent){};
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex& parent ) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void addEntry(const GameEntry& newGame);

    void populate();
private:
    QList<GameEntry> m_data;
};

#endif //GAMELISTMODEL_H
