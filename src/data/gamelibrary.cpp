//
// Created by Kal on 23/02/2024.
//

#include "gamelibrary.h"
#include "game.h"
#include "gameattributehelper.h"
#include "gamehelper.h"
#include "qlogging.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QStandardPaths>


GameLibrary& GameLibrary::instance()
{
    static GameLibrary instance;
    return instance;
}

void GameLibrary::addGame(Game& game)
{
    // Add game to GameDatabase
    m_db.transaction();
    QSqlQuery query(m_db);

    query.prepare("INSERT INTO games (status, name, iconName, description, releaseDate, execPath)"
                  "VALUES (:status, :name, :iconName, :description, :releasedate, :execpath)");

    query.bindValue(":status", GameHelper::statusToString(game.status()));
    query.bindValue(":name", game.name());
    query.bindValue(":iconName", game.iconName());
    query.bindValue(":description", game.desc());
    query.bindValue(":releasedate", game.releaseDate().toString("yyyy-MM-dd"));
    query.bindValue(":execpath", game.execPath());

    if (query.exec()) {
        int lastInsertedId = query.lastInsertId().toInt();

        setGameAttribute(lastInsertedId, Game::Attribute::GENRES, game.genres());
        setGameAttribute(lastInsertedId, Game::Attribute::DEVELOPERS, game.developers());
        setGameAttribute(lastInsertedId, Game::Attribute::PUBLISHERS, game.publishers());
        setGameAttribute(lastInsertedId, Game::Attribute::PLATFORMS, game.platforms());
        setGameAttribute(lastInsertedId, Game::Attribute::USERTAGS, game.userTags());

        game.setId(lastInsertedId);

        m_db.commit();
        m_games[game.id()] = game;

        gameAdded(game);
        gameChanged();
    } else {
        qWarning("Failed to add a game to the DB.");
        m_db.commit();
    }
}

void GameLibrary::setGameAttribute(int gameId, Game::Attribute attribute, QStringList attributeList)
{
    for (const auto& attributeValue : attributeList) {
        addAttribute(attribute, attributeValue);
        QStringList attributeDbInfo = GameAttributeHelper::getDbInfo(attribute);
        // ID, Table, Relation Table

        QSqlQuery findAttrbQuery(m_db);
        findAttrbQuery.prepare(
            QString(
                "SELECT %1 FROM %2 WHERE name = :name")
                .arg(attributeDbInfo[0], attributeDbInfo[1]));
        findAttrbQuery.bindValue(":name", attributeValue);
        findAttrbQuery.exec();

        if (findAttrbQuery.next()) {
            int attrbId = findAttrbQuery.value(0).toInt();
            QSqlQuery genreQuery(m_db);
            genreQuery.prepare(
                QString(
                    "INSERT INTO %2 (gameId, %1) "
                    "VALUES (:gameId, :attrbId)")
                    .arg(attributeDbInfo[0], attributeDbInfo[2]));
            genreQuery.bindValue(":gameId", gameId);
            genreQuery.bindValue(":attrbId", attrbId);
            genreQuery.exec();
        } else {
            qWarning() << "Attribute" << attribute << "not found in the attributes table.";
        }
    }
}

void GameLibrary::removeUnusedAttribute(Game::Attribute attribute)
{
    QString tableName = GameAttributeHelper::getDbTableName(attribute);
    QString relationTableName = GameAttributeHelper::getDbRelationTableName(attribute);
    QString idField = GameAttributeHelper::getIdField(attribute);
    QSqlQuery query(m_db);
    query.exec(
        QString(R"""(
        DELETE FROM %1
        WHERE NOT EXISTS (
          SELECT 1
          FROM %2
          WHERE %2.%3 = %1.%3
        );
        )""")
            .arg(tableName, relationTableName, idField));
};

void GameLibrary::addAttribute(const Game::Attribute attribute, const QString& name)
{
    QString tableName = GameAttributeHelper::getDbTableName(attribute);
    QString idField = GameAttributeHelper::getIdField(attribute);
    QSqlQuery checkQuery(m_db);
    checkQuery.prepare(QString("SELECT %1 FROM %2 WHERE name = :name").arg(idField, tableName));
    checkQuery.bindValue(":name", name);

    checkQuery.exec();

    if (checkQuery.next()) {
        qDebug() << "Attribute"
                 << "already exists.";
        return;
    }

    QSqlQuery insertQuery(m_db);
    insertQuery.prepare(QString("INSERT INTO %1 (name) VALUES (:name)").arg(tableName));
    insertQuery.bindValue(":name", name);

    insertQuery.exec() ? qDebug() << "Attribute added." : qWarning() << "Failed to add attribute:" << insertQuery.lastError().text();
}

QStringList GameLibrary::getGameAttribute(Game game, Game::Attribute attribute)
{
    QStringList attributeDbInfo = GameAttributeHelper::getDbInfo(attribute);
    // ID, Table, Relation Table

    QStringList result;
    QSqlQuery query(m_db);

    query.prepare(QString(R"""(
        SELECT %2.name
        FROM %3
        JOIN %2 ON %3.%1 = %2.%1
        WHERE %3.gameId = :gameId;
    )""")
                      .arg(attributeDbInfo[0], attributeDbInfo[1], attributeDbInfo[2]));
    query.bindValue(":gameId", game.id());

    if (query.exec()) {
        while (query.next()) {
            QString name = query.value(0).toString();
            result.append(name);
        }
    }

    return result;
};

QStringList GameLibrary::getAllOfAttribute(Game::Attribute attribute)
{
    removeUnusedAttribute(attribute);

    QString tableName = GameAttributeHelper::getDbTableName(attribute);

    QStringList result;
    QSqlQuery query(m_db);

    query.exec(QString("SELECT name FROM %1").arg(tableName));
    while (query.next()) {
        result.append(query.value(0).toString());
    }
    return result;
}

void GameLibrary::deleteGame(int gameId)
{
    m_db.transaction();
    QSqlQuery query(m_db);

    query.prepare("DELETE FROM games WHERE GameId = :gameId");
    query.bindValue(0, gameId);
    query.exec();

    m_db.commit();
    // Uses a predicate and deletes the game if the id matches.
    m_games.remove(gameId);
    gameDeleted(gameId);
    gameChanged();
}

void GameLibrary::updateGame(Game& game)
{
    m_db.transaction();
    QSqlQuery query(m_db);

    query.prepare("UPDATE games "
                  "SET status = :status, name = :name, iconName = :iconName, description = :desc, releaseDate = :releasedate, execPath = :execpath "
                  "WHERE gameId = :gameId");

    query.bindValue(":status", GameHelper::statusToString(game.status()));
    query.bindValue(":name", game.name());
    query.bindValue(":iconName", game.iconName());
    query.bindValue(":desc", game.desc());
    query.bindValue(":releasedate", game.releaseDate().toString("yyyy-MM-dd"));
    query.bindValue(":execpath", game.execPath());
    query.bindValue(":gameId", game.id());

    query.exec();

    // Remove old attributes
    QSqlQuery deleteQuery(m_db);
    QStringList tables = {"game_genres", "game_developers", "game_publishers", "game_platforms", "game_user_tags"};

    foreach(const QString &table, tables) {
        QString deleteStatement = QString("DELETE FROM %1 WHERE gameId = :gameId").arg(table);
        deleteQuery.prepare(deleteStatement);
        deleteQuery.bindValue(":gameId", game.id());
        deleteQuery.exec();
    }

    setGameAttribute(game.id(), Game::Attribute::GENRES, game.genres());
    setGameAttribute(game.id(), Game::Attribute::DEVELOPERS, game.developers());
    setGameAttribute(game.id(), Game::Attribute::PUBLISHERS, game.publishers());
    setGameAttribute(game.id(), Game::Attribute::PLATFORMS, game.platforms());
    setGameAttribute(game.id(), Game::Attribute::USERTAGS, game.userTags());

    m_db.commit();

    m_games[game.id()] = game;
    gameUpdated(game);
    gameChanged();
}

QMap<int, Game>& GameLibrary::games()
{
    return m_games;
}

GameLibrary::GameLibrary()
{
    setupDb();

    QSqlTableModel model(this, m_db);
    model.setTable("games");
    model.select();

    QList<Game> initialGameList;
    for (int i = 0; i < model.rowCount(); ++i) {
        int gameId = model.record(i).value("gameId").toInt();
        Game::Status gameStatus = GameHelper::stringToStatus(model.record(i).value("status").toString());
        QString gameIcon = model.record(i).value("iconName").toString();
        QString gameName = model.record(i).value("name").toString();
        QString gameDesc = model.record(i).value("description").toString();
        QDate gameReleaseDate = model.record(i).value("releaseDate").toDate();
        QString gameExecPath = model.record(i).value("execPath").toString();

        Game game(gameId, gameName, gameDesc);
        game.setIconName(gameIcon);
        game.setStatus(gameStatus);
        game.setReleaseDate(gameReleaseDate);
        game.setExecPath(gameExecPath);
        game.setGenres(getGameAttribute(game, Game::Attribute::GENRES));
        game.setDevelopers(getGameAttribute(game, Game::Attribute::DEVELOPERS));
        game.setPublishers(getGameAttribute(game, Game::Attribute::PUBLISHERS));
        game.setPlatforms(getGameAttribute(game, Game::Attribute::PLATFORMS));
        game.setUserTags(getGameAttribute(game, Game::Attribute::USERTAGS));
        initialGameList.append(game);
    }

    for (const auto& game : initialGameList) {
        m_games[game.id()] = game;
    }

    iconController = new GameIconController(this);
}

const Game& GameLibrary::getGameById(int gameId) const
{
    auto it = m_games.find(gameId);
    if (it != m_games.end())
        return it.value();
    else
        qFatal("Unable to fetch Game from GameLibrary.");
}

GameLibrary::~GameLibrary() = default;

bool GameLibrary::setupDb(){

    QString databaseDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dbDir;
    dbDir.mkdir(databaseDir);

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setHostName("local");
    qDebug() << "Using db name:" << databaseDir + "/data.sqlite";
    m_db.setDatabaseName(databaseDir + "/data.sqlite");
    m_db.setUserName("app");
    m_db.setPassword("bqbzKJY9RJ4=");

    m_db.open();

    if(!m_db.isOpen()){
        return false;
    };

    QSqlQuery fkSetupQuery(m_db);
    fkSetupQuery.exec("PRAGMA foreign_keys = ON;");

    QSqlQuery query(m_db);
    m_db.transaction();

    query.exec(R"""(
    CREATE TABLE IF NOT EXISTS "games" (
	"gameId"	INTEGER NOT NULL UNIQUE,
	"iconName"	TEXT,
	"name"	TEXT NOT NULL,
	"status"	TEXT NOT NULL DEFAULT 'NONE',
	"description"	TEXT,
    "releaseDate"   TEXT,
    "execPath"  TEXT,
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

    return true;
}

void GameLibrary::setDb(QString dbname){
    if(!m_db.isOpen())
        return;

    qDebug() << "Setting database to:" << dbname;
    m_db.setDatabaseName(dbname);

}
