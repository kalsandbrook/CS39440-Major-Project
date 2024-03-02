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

    void setup();

    QList<Game> getGames();

private:
    GameDatabase();
    QSqlDatabase db;
};

#endif // GAMEDATABASE_H
