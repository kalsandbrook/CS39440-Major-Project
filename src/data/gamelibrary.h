//
// Created by Kal on 23/02/2024.
//

#ifndef GAMELIBRARY_H
#define GAMELIBRARY_H
#include "game.h"
#include <QList>
#include <QSharedPointer>

class GameLibrary {
public:
    static GameLibrary& instance();

    void addGame(const QSharedPointer<Game>& game);
    QList<QSharedPointer<Game>>& games();

private:
    GameLibrary(); // Private constructor - Singleton
    ~GameLibrary(); // Private destructor - no external deletion
    QList<QSharedPointer<Game>> m_games;
};

#endif // GAMELIBRARY_H
