//
// Created by kal on 27/02/24.
//

#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include "qlogging.h"
#include "gamedatabase.h"
#include "gamelibrary.h"


GameDatabase& GameDatabase::instance()
{
    static GameDatabase instance;
    return instance;
}
bool GameDatabase::open()
{
    // TODO: Move this information to an environment variable
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("local");
    db.setDatabaseName("games");
    db.setUserName("app");
    db.setPassword("bqbzKJY9RJ4=");
    return db.open();
}
void GameDatabase::setup(){
    if (!db.isOpen())
        qFatal("Could not setup database.");
    QSqlQuery query(db);
    // creates games table if it doesn't exist
    db.transaction();
    query.exec(
            "CREATE TABLE IF NOT EXISTS games ("
            "GameID INTEGER PRIMARY KEY,"
            "Name TEXT NOT NULL,"
            "Description TEXT,"
            "Genres TEXT"
            ")");
    // Add example game. TODO: Remove with data persistence
    if(query.next()) {
        query.exec("INSERT INTO games"
                   "VALUES (0, 'Factorio', 'A factory building game','Sandbox,Automation')");
    }
    db.commit();
}

QList<QSharedPointer<Game>> GameDatabase::getGames() {
    QSqlTableModel model;
    model.setTable("games");
    model.select();


    QList<QSharedPointer<Game>> gameList;
    for (int i = 0; i < model.rowCount(); ++i) {
        int gameId = model.record(i).value("GameID").toInt();
        QString gameName = model.record(i).value("Name").toString();
        QString gameDesc = model.record(i).value("Description").toString();
        QStringList genres = model.record(i).value("Genres").toStringList();

        QSharedPointer<Game> game(new Game(gameId,gameName,gameDesc,genres));
        gameList.append(game);
    }
    return gameList;
}

GameDatabase::GameDatabase() = default;