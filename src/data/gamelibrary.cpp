//
// Created by Kal on 23/02/2024.
//

#include "gamelibrary.h"
#include "gamedatabase.h"

GameLibrary& GameLibrary::instance()
{
    static GameLibrary instance;
    return instance;
}

void GameLibrary::addGame(const QSharedPointer<Game>& game)
{
    m_games.append(game);
}

QList<QSharedPointer<Game>>& GameLibrary::games() { return m_games; }

GameLibrary::GameLibrary(){
    auto db = GameDatabase::instance();

    QList<QSharedPointer<Game>> initialGameList = db.getGames();
    m_games.append(initialGameList);
}

GameLibrary::~GameLibrary() = default;
