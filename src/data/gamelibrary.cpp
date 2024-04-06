//
// Created by Kal on 23/02/2024.
//

#include "gamelibrary.h"
#include "gamehelper.h"
#include "qlogging.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>

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

    query.prepare("INSERT INTO games (status, name, iconName, description)"
                  "VALUES (:status, :name, :iconName, :description)");

    query.bindValue(":status", GameHelper::statusToString(game.status()));
    query.bindValue(":name", game.name());
    query.bindValue(":iconName", game.iconName());
    query.bindValue(":description", game.desc());

    if (query.exec()) {
        qint64 lastInsertedId = query.lastInsertId().toLongLong();

        setGameGenres(lastInsertedId, game.genres());

        game.setId(lastInsertedId);

        db.endTransaction();
        m_games[game.id()] = game;

        gameAdded(game);
    } else {
        qFatal("Failed to add a game to the DB.");
        db.endTransaction();
    }
}

void GameLibrary::setGameGenres(int gameId, QStringList genres){
        for(const auto& genre : genres){
            addGenre(genre);

            QSqlQuery findGenreQuery(db.db());
            findGenreQuery.prepare("SELECT genreId FROM genres WHERE name = :genreName");
            findGenreQuery.bindValue(":genreName", genre);
            findGenreQuery.exec();

            if (findGenreQuery.next()) {
                int genreId = findGenreQuery.value(0).toInt();
                QSqlQuery genreQuery(db.db());
                genreQuery.prepare(
                    "INSERT INTO game_genres (gameId, genreId) "
                    "VALUES (:gameId, :genreId)"
                );
                genreQuery.bindValue(":gameId", gameId);
                genreQuery.bindValue(":genreId", genreId);
                genreQuery.exec();
            }   else {
            qWarning() << "Genre" << genre << "not found in the genres table.";
            }
        }
}

void GameLibrary::removeUnusedGenres(){
    QSqlQuery getGenresQuery(db.db());
    getGenresQuery.exec(R"""(
        DELETE FROM genres
        WHERE NOT EXISTS (
          SELECT 1
          FROM game_genres
          WHERE game_genres.genreId = genres.genreId
        );
    )""");
};

void GameLibrary::addGenre(const QString& genreName){
    QSqlQuery checkQuery(db.db());
    checkQuery.prepare("SELECT genreId FROM genres WHERE name = :name");
    checkQuery.bindValue(":name",genreName);
    checkQuery.exec();

    if(checkQuery.next()){
        qDebug() << "Genre already exists.";
        return;
    }

    QSqlQuery insertQuery(db.db());
    insertQuery.prepare("INSERT INTO genres (name) VALUES (:name)");
    insertQuery.bindValue(":name", genreName);

    insertQuery.exec() ? qDebug() << "Genre added." : qWarning() << "Failed to add genre:" << insertQuery.lastError().text();
}

QStringList GameLibrary::getGameGenres(Game game){
    QStringList genres;
    QSqlQuery query(db.db());

    query.prepare(R"""(
        SELECT genres.name
        FROM game_genres
        JOIN genres ON game_genres.genreId = genres.genreId
        WHERE game_genres.gameId = :gameId;
    )""");
    query.bindValue(":gameId", game.id());

    if(query.exec()){
        while(query.next()){
            QString genreName = query.value(0).toString();
            genres.append(genreName);
        }
    }

    return genres;
};

QStringList GameLibrary::getAllGenres(){
    removeUnusedGenres();
    QStringList genres;
    QSqlQuery query(db.db());

    query.exec("SELECT name FROM genres");
    while(query.next()){
        genres.append(query.value(0).toString());
    }
    return genres;
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

void GameLibrary::updateGame(Game& game)
{
    db.beginTransaction();
    QSqlQuery query(db.db());

    query.prepare("UPDATE games "
                  "SET status = :status, name = :name, iconName = :iconName, description = :desc"
                  "WHERE gameId = :gameId");

    query.bindValue(":status", GameHelper::statusToString(game.status()));
    query.bindValue(":name", game.name());
    query.bindValue(":iconName", game.iconName());
    query.bindValue(":desc", game.desc());
    query.bindValue(":gameId", game.id());

    query.exec();

    // Handle genres
    QSqlQuery deleteQuery(db.db());
    deleteQuery.prepare("DELETE FROM game_genres WHERE gameId = :gameId");
    deleteQuery.bindValue(":gameId", game.id());
    deleteQuery.exec();

    setGameGenres(game.id(), game.genres());

    db.endTransaction();

    m_games[game.id()] = game;
    gameUpdated(game);
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
        int gameId = model.record(i).value("GameId").toInt();
        Game::Status gameStatus = GameHelper::stringToStatus(model.record(i).value("Status").toString());
        QString gameIcon = model.record(i).value("IconName").toString();
        QString gameName = model.record(i).value("Name").toString();
        QString gameDesc = model.record(i).value("Description").toString();
        QStringList genres = model.record(i).value("Genres").toStringList();

        Game game(gameId, gameName, gameDesc);
        game.setGenres(genres);
        game.setIconName(gameIcon);
        game.setStatus(gameStatus);
        game.setGenres(getGameGenres(game));
        initialGameList.append(game);
    }

    for (const auto& game : initialGameList) {
        m_games[game.id()] = game;
    }

    iconController = new GameIconController();
}

const Game& GameLibrary::getGameById(int gameId) const
{
    // Uses QMap.find to avoid memory issues.
    auto it = m_games.find(gameId);
    if (it != m_games.end())
        return it.value();
    else
        qFatal("Unable to fetch Game from GameLibrary.");
}

GameLibrary::~GameLibrary() = default;
