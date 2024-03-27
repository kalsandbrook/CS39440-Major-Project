//
// Created by kal on 27/02/24.
//

#include "gamedatabase.h"
#include "gamehelper.h"
#include "qlogging.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>

GameDatabase& GameDatabase::instance()
{
    static GameDatabase instance;
    return instance;
}

bool GameDatabase::open()
{
    // TODO: Move this information to an environment variable
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setHostName("local");
    m_db.setDatabaseName("games");
    m_db.setUserName("app");
    m_db.setPassword("bqbzKJY9RJ4=");
    return m_db.open();
}

QSqlDatabase& GameDatabase::db() { return m_db; }

void GameDatabase::close()
{
    m_db.close();
}

void GameDatabase::setup()
{
    if (!m_db.isOpen())
        qFatal("Could not setup database.");
    QSqlQuery query(m_db);
    // creates games table if it doesn't exist
    m_db.transaction();
    query.exec(
        "CREATE TABLE IF NOT EXISTS games ("
        "GameId INTEGER PRIMARY KEY AUTOINCREMENT,"
        "IconName TEXT,"
        "Name TEXT NOT NULL,"
        "Status TEXT,"
        "Description TEXT,"
        "Genres TEXT"
        ")");
    m_db.commit();
}

void GameDatabase::beginTransaction()
{
    m_db.transaction();
}
void GameDatabase::endTransaction()
{
    m_db.commit();
}

QList<Game> GameDatabase::getGames()
{
    QSqlTableModel model;
    model.setTable("games");
    model.select();

    QList<Game> gameList;
    for (int i = 0; i < model.rowCount(); ++i) {
        int gameId = model.record(i).value("GameId").toInt();
        Game::Status gameStatus = GameHelper::stringToStatus(model.record(i).value("Status").toString());
        QString gameIcon = model.record(i).value("IconName").toString();
        QString gameName = model.record(i).value("Name").toString();
        QString gameDesc = model.record(i).value("Description").toString();
        QStringList genres = model.record(i).value("Genres").toStringList();

        Game game(gameId, gameName, gameDesc, genres);
        game.setIconName(gameIcon);
        game.setStatus(gameStatus);
        gameList.append(game);
    }
    return gameList;
}

GameDatabase::GameDatabase() = default;
