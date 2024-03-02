#ifndef GAMEDATABASE_H
#define GAMEDATABASE_H

#include "game.h"
#include <QSqlDatabase>
#include <QSqlTableModel>

class GameDatabase {
public:
    static GameDatabase& instance();

    bool open();
    void close();

    void beginTransaction();
    void endTransaction();

    QSqlDatabase& db();

    void setup();

    QList<Game> getGames();

private:
    GameDatabase();
    QSqlDatabase m_db;
};

#endif // GAMEDATABASE_H
