//
// Created by Kal on 23/02/2024.
//

#ifndef GAMELIBRARY_H
#define GAMELIBRARY_H
#include "game.h"
#include "gameiconcontroller.h"
#include <QList>
#include <QObject>
#include <QSharedPointer>
#include <QSqlDatabase>

/**
 * @brief A class representing the library of games.
 *
 * This class represents the library of games, and contains methods for adding and deleting games from the library.
 * It functions as a single source of truth for the games in the library, performing the actions of a Data Access Object (DAO).
 *
 * This class is a singleton, and can be accessed using the instance() method.
 *
 * This should probably be merged with GameLibraryModel, as they handle very similar responsibilities.
 */
class GameLibrary : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Returns the instance of the GameLibrary.
     *
     * This method returns the instance of the GameLibrary, creating it if it doesn't exist.
     *
     * @return The instance of the GameLibrary.
     */
    static GameLibrary& instance();

    const Game& getGameById(int gameId) const;

    /**
     * @brief Adds a game to the library.
     *
     * This method adds the given game to the library.
     *
     * @param game The game to add.
     */
    void addGame(Game& game);

    /**
     * @brief Adds an attribute to the library.
     * @param attribute The attribute to add.
     * @param name The name of the attribute.
     * @see Game::Attribute
    */
    void addAttribute(const Game::Attribute attribute, const QString& name);

    /**
     * @brief Sets the attribute of a game.
     * @param gameId The ID of the game.
     * @param attribute The attribute to set.
     * @param attributeList The list of attributes.
     * @see Game::Attribute
    */
    void setGameAttribute(int gameId, Game::Attribute attribute, QStringList attributeList);

    /**
     * @brief Removes attribute values from the database that are not used by any game.
     * @param attribute The attribute to remove.
     * @see Game::Attribute
    */
    void removeUnusedAttribute(Game::Attribute attribute);

    /**
     * @brief Deletes all games from the library.
     * Mainly used in testing.
    */
    void deleteAllGames();

    /**
     * @brief Returns the list of games in the library.
     * @return The list of games in the library.
     * @see Game
    */
    QStringList getGameAttribute(Game game, Game::Attribute attribute);

    /**
     * @brief Returns the list of all values of a given attribute.
     * @param attribute The attribute to get the values of.
     * @return The list of all values of the given attribute.
     * 
     * Used to autofill on the add game dialog.
    */
    QStringList getAllOfAttribute(Game::Attribute attribute);

    /**
     * @brief Deletes a game from the library.
     *
     * This method deletes the game with the given ID from the library.
     *2
     * @param gameId The ID of the game to delete.
     */
    void deleteGame(int gameId);

    /**
     * @brief Updates a game in the library.
     *
     * This method updates a game in the library with new details.
     *
     * @param game The game to update.
     */
    void updateGame(Game& game);

    /**
     * @brief Returns the list of games in the library.
     *
     * This method returns the list of games in the library.
     *
     * @return The list of games in the library.
     */
    QMap<int, Game>& games();
    
    /**
     * @brief Sets the database name.
     * 
     * Used to set a custom database name for testing, so tests don't interfere with the main database.
    */
    void setDb(QString dbname);

    /**
     * @brief The icon controller for the library.
    */
    GameIconController* iconController;

signals:

    /**
     * @brief Signals that a game has been added to the library.
     *
     * This signal is emitted when a game is added to the library.
     *
     * @param game The game that was added.
     * @see GameLibraryModel::onGameAdded()
     */
    void gameAdded(const Game& game);

    /**
     * @brief Signals that a game has been deleted from the library.
     *
     * This signal is emitted when a game is deleted from the library.
     *
     * @param gameId The ID of the game that was deleted.
     * @see GameLibraryModel::onGameDeleted()
     */
    void gameDeleted(const int gameId);
    /**
     * @brief Signals that a game in the library has been updated.
     *
     * This signal is emitted when a game in the library is updated.
     *
     * @param game The game that is updated..
     * @see GameLibraryModel::onGameUpdated()
     */
    void gameUpdated(const Game& game);

    /**
     * @brief Signals that the game library has changed.
    */
    void gameChanged();



private:
    GameLibrary(); // Private constructor - Singleton
    ~GameLibrary(); // Private destructor - no external deletion
    GameLibrary(const GameLibrary&) = delete;
    GameLibrary& operator=(const GameLibrary&) = delete;

    QMap<int, Game> m_games;
    // GameDatabase db = GameDatabase::instance();

    bool setupDb();
    QSqlDatabase m_db;

    QString customDbName = ""; // For testing ONLY.
};

#endif // GAMELIBRARY_H
