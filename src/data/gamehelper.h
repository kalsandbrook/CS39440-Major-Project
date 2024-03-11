//
// Created by kal on 07/03/24.
//

#ifndef GAMEPILE_GAMEHELPER_H
#define GAMEPILE_GAMEHELPER_H

#include "game.h"
#include <QString>

namespace GameHelper {
QString statusToString(Game::Status status);

Game::Status stringToStatus(const QString& status);
};

#endif // GAMEPILE_GAMEHELPER_H
