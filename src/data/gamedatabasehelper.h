//
// Created by kal on 07/03/24.
//

#ifndef GAMEPILE_GAMEDATABASEHELPER_H
#define GAMEPILE_GAMEDATABASEHELPER_H

#include <QString>
#include "game.h"

namespace GameDBHelper {
    QString statusToString(Game::Status status);

    Game::Status stringToStatus(const QString& status);
};


#endif //GAMEPILE_GAMEDATABASEHELPER_H
