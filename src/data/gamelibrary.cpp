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

    query.prepare("INSERT INTO games (status, name, iconName, description, releaseDate, execPath)"
                  "VALUES (:status, :name, :iconName, :description, :releasedate, :execpath)");

    query.bindValue(":status", GameHelper::statusToString(game.status()));
    query.bindValue(":name", game.name());
    query.bindValue(":iconName", game.iconName());
    query.bindValue(":description", game.desc());
    query.bindValue(":releasedate", game.releaseDate().toString("yyyy-MM-dd"));
    query.bindValue(":execpath", game.execPath());

    if (query.exec()) {
        qint64 lastInsertedId = query.lastInsertId().toLongLong();

        setGameAttribute(lastInsertedId, Game::Attribute::GENRES, game.genres());
        setGameAttribute(lastInsertedId, Game::Attribute::DEVELOPERS, game.developers());
        setGameAttribute(lastInsertedId, Game::Attribute::PUBLISHERS, game.publishers());
        setGameAttribute(lastInsertedId, Game::Attribute::PLATFORMS, game.platforms());
        setGameAttribute(lastInsertedId, Game::Attribute::USERTAGS, game.userTags());

        game.setId(lastInsertedId);

        db.endTransaction();
        m_games[game.id()] = game;

        gameAdded(game);
        gameChanged();
    } else {
        qFatal("Failed to add a game to the DB.");
        db.endTransaction();
    }
}

void GameLibrary::setGameAttribute(int gameId, Game::Attribute attribute, QStringList attributeList)
{
    for (const auto& attributeValue : attributeList) {
        addAttribute(attribute, attributeValue);
        QStringList attributeDbInfo = GameAttributeHelper::getDbInfo(attribute);
        // ID, Table, Relation Table

        QSqlQuery findAttrbQuery(db.db());
        findAttrbQuery.prepare(
            QString(
                "SELECT %1 FROM %2 WHERE name = :name")
                .arg(attributeDbInfo[0], attributeDbInfo[1]));
        findAttrbQuery.bindValue(":name", attributeValue);
        findAttrbQuery.exec();

        if (findAttrbQuery.next()) {
            int attrbId = findAttrbQuery.value(0).toInt();
            QSqlQuery genreQuery(db.db());
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
    QSqlQuery query(db.db());
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
    QSqlQuery checkQuery(db.db());
    checkQuery.prepare(QString("SELECT %1 FROM %2 WHERE name = :name").arg(idField, tableName));
    checkQuery.bindValue(":name", name);

    checkQuery.exec();

    if (checkQuery.next()) {
        qDebug() << "Attribute"
                 << "already exists.";
        return;
    }

    QSqlQuery insertQuery(db.db());
    insertQuery.prepare(QString("INSERT INTO %1 (name) VALUES (:name)").arg(tableName));
    insertQuery.bindValue(":name", name);

    insertQuery.exec() ? qDebug() << "Attribute added." : qWarning() << "Failed to add attribute:" << insertQuery.lastError().text();
}

QStringList GameLibrary::getGameAttribute(Game game, Game::Attribute attribute)
{
    QStringList attributeDbInfo = GameAttributeHelper::getDbInfo(attribute);
    // ID, Table, Relation Table

    QStringList result;
    QSqlQuery query(db.db());

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
    QSqlQuery query(db.db());

    query.exec(QString("SELECT name FROM %1").arg(tableName));
    while (query.next()) {
        result.append(query.value(0).toString());
    }
    return result;
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
    gameChanged();
}

void GameLibrary::updateGame(Game& game)
{
    db.beginTransaction();
    QSqlQuery query(db.db());

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
    QSqlQuery deleteQuery(db.db());
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

    db.endTransaction();

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
    QSqlTableModel model;
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
