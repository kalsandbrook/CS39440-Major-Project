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

    if(query.exec()){
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

QList<Game>& GameLibrary::games() { return m_games; }

GameLibrary::GameLibrary()
{
    QList<Game> initialGameList = db.getGames();
    m_games.append(initialGameList);
}

GameLibrary::~GameLibrary() = default;
