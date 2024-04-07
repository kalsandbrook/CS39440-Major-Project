//
// Created by kal on 07/03/24.
//

#ifndef GAMEPILE_GAMEHELPER_H
#define GAMEPILE_GAMEHELPER_H

#include "game.h"
#include <QIcon>
#include <QString>

namespace GameHelper {
QString statusToString(Game::Status status);

Game::Status stringToStatus(const QString& status);

QIcon getStatusIcon(const QString& status);

QIcon getStatusIcon(Game::Status status);

};

#endif // GAMEPILE_GAMEHELPER_H
