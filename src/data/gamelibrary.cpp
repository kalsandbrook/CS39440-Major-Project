//
// Created by Kal on 23/02/2024.
//

#include "gamelibrary.h"
#include "gamehelper.h"
#include "qlogging.h"
#include <QSqlQuery>
#include <QSqlError>

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

    query.prepare("INSERT INTO games (Status, Name, Description, Genres)"
                  "VALUES (:status, :name, :description,:genres)");

    query.bindValue(":status", GameHelper::statusToString(game.status()));
    query.bindValue(":name", game.name());
    query.bindValue(":description", game.desc());
    query.bindValue(":genres", game.genres());

    if (query.exec()) {
        qint64 lastInsertedId = query.lastInsertId().toLongLong();

        game.setId(lastInsertedId);

        db.endTransaction();
        m_games[game.id()] = game;

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
    m_games.remove(gameId);
    gameDeleted(gameId);
}

void GameLibrary::updateGame(Game &game) {
    db.beginTransaction();
    QSqlQuery query(db.db());

    query.prepare("UPDATE games "
                  "SET Status = :status, Name = :name, Description = :desc, Genres = :genres "
                  "WHERE GameId = :gameId");

    query.bindValue(":status", GameHelper::statusToString(game.status()));
    query.bindValue(":name",game.name());
    query.bindValue(":desc",game.desc());
    query.bindValue(":genres",game.genres());
    query.bindValue(":gameId",game.id());

    query.exec();

    db.endTransaction();

    m_games[game.id()] = game;
    gameUpdated(game);
}

QMap<int, Game> & GameLibrary::games() {
    return m_games;
}

GameLibrary::GameLibrary()
{
    // TODO: db.getGames() should be moved to be a part of this function.
    QList<Game> initialGameList = db.getGames();

    for (const auto& game : initialGameList ){
        m_games[game.id()] = game;
    }
}

const Game& GameLibrary::getGameById(int gameId) const {
    // Uses QMap.find to avoid memory issues.
    auto it = m_games.find(gameId);
    if ( it != m_games.end() )
        return it.value();
    else qFatal("Unable to fetch Game from GameLibrary.");
}

GameLibrary::~GameLibrary() = default;
