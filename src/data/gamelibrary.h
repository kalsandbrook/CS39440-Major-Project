//
// Created by Kal on 23/02/2024.
//

#ifndef GAMELIBRARY_H
#define GAMELIBRARY_H
#include "game.h"
#include "gamedatabase.h"
#include <QList>
#include <QObject>
#include <QSharedPointer>

class GameLibrary : public QObject {
    Q_OBJECT
public:
    static GameLibrary& instance();

    void addGame(Game& game);
    void deleteGame(int gameId);
    QList<Game>& games();

signals:
    void gameAdded(const Game& game);
    void gameDeleted(const int gameId);

private:
    GameLibrary(); // Private constructor - Singleton
    ~GameLibrary(); // Private destructor - no external deletion
    GameLibrary(const GameLibrary&) = delete;
    GameLibrary& operator=(const GameLibrary&) = delete;
    QList<Game> m_games;
    GameDatabase db = GameDatabase::instance();
};

#endif // GAMELIBRARY_H
