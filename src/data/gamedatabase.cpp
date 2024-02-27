//
// Created by kal on 27/02/24.
//

#include "gamedatabase.h"

GameDatabase::GameDatabase() {};
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