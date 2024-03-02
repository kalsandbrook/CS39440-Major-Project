//
// Created by Kal on 24/02/2024.
//

#ifndef GAMELIBRARYMODEL_H
#define GAMELIBRARYMODEL_H

#include <QAbstractItemModel>

#include "gamelibrary.h"

class GameLibraryModel : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit GameLibraryModel(QObject* parent = nullptr);
    enum GameRoles { NameRole = Qt::UserRole + 1,
        DescRole,
        GenreRole };

    QModelIndex index(int row, int column,
        const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& child) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index,
        int role = Qt::DisplayRole) const override;
    void addGame(const Game& game);
    void deleteGameFromIndex(const QModelIndex& index);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    GameLibrary& m_gameLibrary;
};

#endif // GAMELIBRARYMODEL_H
