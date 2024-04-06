//
// Created by kal on 27/02/24.
//

#include "gamedatabase.h"
#include "qlogging.h"
#include <QSqlQuery>
#include <QDir>
#include <QSqlRecord>
#include <QSqlError>
#include <QStringList>
#include <QStandardPaths>

GameDatabase& GameDatabase::instance()
{
    static GameDatabase instance;
    return instance;
}

bool GameDatabase::open()
{
    // TODO: Move this information to an environment variable

    QString databaseDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setHostName("local");
    m_db.setDatabaseName(databaseDir + "/data.sqlite");
    m_db.setUserName("app");
    m_db.setPassword("bqbzKJY9RJ4=");

    return m_db.open();

}

QSqlDatabase GameDatabase::db() { return m_db; }

void GameDatabase::close()
{
    m_db.close();
}

void GameDatabase::setup()
{
    if (!m_db.isOpen())
        qFatal("Could not setup database.");


    QSqlQuery fkSetupQuery(m_db);
    fkSetupQuery.exec("PRAGMA foreign_keys = ON;");

    QSqlQuery query(m_db);
    // creates games table if it doesn't exist
    m_db.transaction();

    query.exec(R"""(
    CREATE TABLE IF NOT EXISTS "games" (
	"gameId"	INTEGER NOT NULL UNIQUE,
	"iconName"	TEXT,
	"name"	TEXT NOT NULL,
	"status"	TEXT NOT NULL DEFAULT 'NONE',
	"description"	TEXT,
	PRIMARY KEY("gameId" AUTOINCREMENT))
    )""");

    query.exec(R"""(
    CREATE TABLE IF NOT EXISTS "genres" (
	"genreId"	INTEGER NOT NULL UNIQUE,
	"name"	TEXT NOT NULL,
	PRIMARY KEY("genreId" AUTOINCREMENT))
    )""");

    query.exec(R"""(
    CREATE TABLE IF NOT EXISTS "developers" (
	"developerId"	INTEGER NOT NULL UNIQUE,
	"name"	TEXT NOT NULL,
	PRIMARY KEY("developerId" AUTOINCREMENT))
    )""");

    query.exec(R"""(
    CREATE TABLE IF NOT EXISTS "publishers" (
	"publisherId"	INTEGER NOT NULL UNIQUE,
	"name"	TEXT NOT NULL,
	PRIMARY KEY("publisherId" AUTOINCREMENT))
    )""");

    query.exec(R"""(
    CREATE TABLE IF NOT EXISTS "platforms" (
	"platformId"	INTEGER NOT NULL UNIQUE,
	"name"	TEXT NOT NULL,
	PRIMARY KEY("platformId" AUTOINCREMENT))
    )""");

    query.exec(R"""(
    CREATE TABLE IF NOT EXISTS "user_tags" (
	"userTagId"	INTEGER NOT NULL UNIQUE,
	"name"	INTEGER NOT NULL,
	PRIMARY KEY("userTagId" AUTOINCREMENT))
    )""");

    query.exec(R"""(
    CREATE TABLE IF NOT EXISTS "game_genres" (
	"gameId"	INTEGER NOT NULL,
	"genreId"	INTEGER NOT NULL,
	FOREIGN KEY("genreId") REFERENCES "genres"("genreId"),
	FOREIGN KEY("gameId") REFERENCES "games"("gameId") ON DELETE CASCADE)
    )""");

    query.exec(R"""(
    CREATE TABLE IF NOT EXISTS "game_developers" (
	"gameId"	INTEGER NOT NULL,
	"developerId"	INTEGER NOT NULL,
	FOREIGN KEY("gameId") REFERENCES "games"("gameId") ON DELETE CASCADE,
	FOREIGN KEY("developerId") REFERENCES "developers"("developerId"))
    )""");

    query.exec(R"""(
    CREATE TABLE IF NOT EXISTS "game_publishers" (
	"gameId"	INTEGER NOT NULL,
	"publisherId"	INTEGER NOT NULL,
	FOREIGN KEY("gameId") REFERENCES "games"("gameId") ON DELETE CASCADE,
	FOREIGN KEY("publisherId") REFERENCES "publishers"("publisherId"))
    )""");

    query.exec(R"""(
    CREATE TABLE IF NOT EXISTS "game_platforms" (
	"gameId"	INTEGER NOT NULL,
	"platformId"	INTEGER NOT NULL,
	FOREIGN KEY("platformId") REFERENCES "platforms"("platformId"),
	FOREIGN KEY("gameId") REFERENCES "games"("gameId") ON DELETE CASCADE)
    )""");

    query.exec(R"""(
    CREATE TABLE IF NOT EXISTS "game_user_tags" (
	"gameId"	INTEGER NOT NULL,
	"userTagId"	INTEGER NOT NULL,
	FOREIGN KEY("gameId") REFERENCES "games"("gameId") ON DELETE CASCADE,
	FOREIGN KEY("userTagId") REFERENCES "user_tags"("userTagId"))
    )""");

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


GameDatabase::GameDatabase() = default;
