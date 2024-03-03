//
// Created by Kal on 24/02/2024.
//

#ifndef GAMELIBRARYMODEL_H
#define GAMELIBRARYMODEL_H

#include <QAbstractItemModel>

#include "gamelibrary.h"

/**
 * @brief A model for the game library.
 * 
 * This class is a model for the game library, and provides the data for the game library view.
 * 
 * It is a subclass of QAbstractItemModel, and provides the data for the game library view.
 */
class GameLibraryModel : public QAbstractItemModel {
    Q_OBJECT
public:
    /**
     * @brief Constructs a new GameLibraryModel object.
     * 
     * This constructor creates a new GameLibraryModel object with the given parent.
     * 
     * @param parent The parent of the model.
     */
    explicit GameLibraryModel(QObject* parent = nullptr);

    /**
     * @brief The roles of the model.
     * 
     * This enum represents the roles of the model, such as the name, description, genres and id of the game.
     * 
     * These roles are used to access the data of the model.
     */
    enum GameRoles { 
        NameRole = Qt::UserRole + 1,
        DescRole,
        GenreRole,
        IdRole
    };

    /**
     * @brief Returns the index of the item in the model.
     * 
     * This method returns the index of the item in the model with the given row, column, and parent index.
     * 
     * @param row The row of the item.
     * @param column The column of the item.
     * @param parent The parent index of the item.
     * @return The index of the item.
     */
    QModelIndex index(int row, int column,
        const QModelIndex& parent = QModelIndex()) const override;

    /**
     * @brief Returns the parent index of the child index.
     * 
     * This method returns the parent index of the child index. As this model is flat, there are no parents, so it always returns an invalid index.
     * 
     * It is only here as it is a pure virtual method of QAbstractItemModel, and is therefore required to be implemented.
     * 
     * @param child The child index.
     */
    QModelIndex parent(const QModelIndex& child) const override;

    /**
     * @brief Returns the number of rows in the model.
     * 
     * This method returns the number of rows in the model. In this case, the number of games in the library.
     * 
     * @param parent The parent index.
     * @return The number of rows in the model.
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    /**
     * @brief Returns the number of columns in the model.
     * 
     * This method returns the number of columns in the model. In this case, the number of properties of the game.
     * 
     * @param parent The parent index.
     * @return The number of columns in the model.
     */
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    /**
     * @brief Returns the data of the model.
     * 
     * This method returns the data of the model with the given index and role.
     * 
     * @param index The index of the item.
     * @param role The role of the item.
     * @return The data of the item.
     */
    QVariant data(const QModelIndex& index,
        int role = Qt::DisplayRole) const override;

public slots:
    /**
     * @brief Updates the model when a game is added to the library.
     * 
     * This method updates the model when a game is added to the library.
     * 
     * @param game The game that was added.
     */
    void onGameAdded(const Game& game);

    /**
     * @brief Updates the model when a game is deleted from the library.
     * 
     * This method updates the model when a game is deleted from the library.
     * 
     * @param gameId The ID of the game that was deleted.
     */
    void onGameDeleted(int gameId);

protected:
    /**
     * @brief Returns the role names of the model.
     * 
     * This method returns the role names of the model.
     * 
     * @return The role names of the model.
     * 
     * @see GameRoles
     */
    QHash<int, QByteArray> roleNames() const override;

private:
    GameLibrary& m_gameLibrary;
    QList<Game> m_games;
};

#endif // GAMELIBRARYMODEL_H
