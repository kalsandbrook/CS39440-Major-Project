#ifndef GAMEDATABASE_H
#define GAMEDATABASE_H

#include "game.h"
#include "gamehelper.h"
#include <QSqlDatabase>
#include <QSqlTableModel>

/**
 * @brief A class representing the database of games.
 *
 * This class represents the database of games, and contains methods for interacting with the database.
 *
 * This class is a singleton, and can be accessed using the instance() method.
 */
class GameDatabase {
public:
    /**
     * @brief Returns the instance of the GameDatabase.
     *
     * This method returns the instance of the GameDatabase, creating it if it doesn't exist.
     *
     * @return The instance of the GameDatabase.
     */
    static GameDatabase& instance();

    /**
     * @brief Opens the database.
     *
     * This method opens the database, returning true if successful, and false if not.
     *
     * @return True if the database was opened successfully, false if not.
     */
    bool open();

    /**
     * @brief Closes the database.
     */
    void close();

    /**
     * @brief Begins a transaction.
     */
    void beginTransaction();

    /**
     * @brief Ends a transaction.
     */
    void endTransaction();

    /**
     * @brief Returns the database.
     */
    QSqlDatabase& db();

    /**
     * @brief Sets up the database.
     *
     * This method sets up the database, creating the games table if it doesn't exist.
     */
    void setup();

    /**
     * @brief Returns a list of games from the database.
     *
     * This method returns a list of games from the database.
     *
     * @todo This functionality will be moved to the GameLibrary class in the future.
     *
     * @return A list of games from the database.
     */
    QList<Game> getGames();

private:
    GameDatabase();
    QSqlDatabase m_db;
};

#endif // GAMEDATABASE_H
