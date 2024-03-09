//
// Created by kal on 07/03/24.
//

#include "gamedatabasehelper.h"

namespace GameDBHelper {
    QString statusToString(Game::Status status) {
        switch (status) {
            case Game::Status::NONE:
                return "NONE";
            case Game::Status::BACKLOG:
                return "BACKLOG";
            case Game::Status::PLAYING:
                return "PLAYING";
            case Game::Status::COMPLETED:
                return "COMPLETED";
            case Game::Status::ABANDONED:
                return "ABANDONED";
            default:
                return {};
        }
    }

    Game::Status stringToStatus(const QString &status) {
        if (status == "NONE") return Game::Status::NONE;
        if (status == "BACKLOG") return Game::Status::BACKLOG;
        if (status == "PLAYING") return Game::Status::PLAYING;
        if (status == "COMPLETED") return Game::Status::COMPLETED;
        if (status == "ABANDONED") return Game::Status::ABANDONED;

        return Game::Status::NONE;
    }
}