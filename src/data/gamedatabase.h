#ifndef GAMEDATABASE_H
#define GAMEDATABASE_H

#include <QSqlDatabase>

class GameDatabase {
public:
    GameDatabase();
    bool open();

private:
    QSqlDatabase db;
};

#endif // GAMEDATABASE_H
