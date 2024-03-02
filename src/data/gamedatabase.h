#ifndef GAMEDATABASE_H
#define GAMEDATABASE_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include "game.h"

class GameDatabase {
public:
    static GameDatabase& instance();

    bool open();
    void setup();

    QList<QSharedPointer<Game>> getGames();

private:
    GameDatabase();
    QSqlDatabase db;
};

#endif // GAMEDATABASE_H
