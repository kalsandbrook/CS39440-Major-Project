//
// Created by Kal on 23/02/2024.
//

#include "gamelibrary.h"
#include "qlogging.h"
#include <QSqlQuery>

GameLibrary& GameLibrary::instance()
{
    static GameLibrary instance;
    return instance;
}

void GameLibrary::addGame(Game& game)
{
    // Add game to GameDatabase
    db.beginTransaction();
    QSqlQuery query(db.db());

    query.prepare("INSERT INTO games (Name, Description, Genres)"
                  "VALUES (:name, :description,:genres)");
    query.bindValue(0, game.name());
    query.bindValue(1, game.desc());
    query.bindValue(2, game.genre());

    if (query.exec()) {
        qint64 lastInsertedId = query.lastInsertId().toLongLong();

        game.setId(lastInsertedId);

        db.endTransaction();
        m_games.append(game);
        gameAdded(game);
    } else {
        qFatal("Failed to add a game to the DB.");
        db.endTransaction();
    }
}

void GameLibrary::deleteGame(int gameId)
{
    db.beginTransaction();
    QSqlQuery query(db.db());

    query.prepare("DELETE FROM games WHERE GameId = :gameId");
    query.bindValue(0, gameId);
    query.exec();

    db.endTransaction();
    // Uses a predicate and deletes the game if the id matches.
    m_games.removeIf([&gameId](const Game& game) {
        return game.getId() == gameId;
    });
    gameDeleted(gameId);
}

QList<Game>& GameLibrary::games() { return m_games; }

GameLibrary::GameLibrary()
{
    // TODO: db.getGames() should be moved to be a part of this function.
    QList<Game> initialGameList = db.getGames();
    m_games.append(initialGameList);
}

GameLibrary::~GameLibrary() = default;
