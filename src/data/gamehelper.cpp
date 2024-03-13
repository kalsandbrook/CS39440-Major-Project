//
// Created by kal on 07/03/24.
//

#include "gamehelper.h"

namespace GameHelper {
QString statusToString(Game::Status status)
{
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

Game::Status stringToStatus(const QString& status)
{
    if (status == "NONE")
        return Game::Status::NONE;
    if (status == "BACKLOG")
        return Game::Status::BACKLOG;
    if (status == "PLAYING")
        return Game::Status::PLAYING;
    if (status == "COMPLETED")
        return Game::Status::COMPLETED;
    if (status == "ABANDONED")
        return Game::Status::ABANDONED;

    return Game::Status::NONE;
}

    QIcon getStatusIcon(const QString &status) {
        return getStatusIcon(stringToStatus(status));
    }

    QIcon getStatusIcon(Game::Status status) {
        // TODO: Implement proper icons.
        switch(status){
            case Game::NONE:
                return QIcon::fromTheme("edit-none-symbolic");
            case Game::BACKLOG:
                return QIcon::fromTheme("dialog-layers-symbolic");
            case Game::PLAYING:
                return QIcon::fromTheme("media-playback-start-symbolic");
            case Game::COMPLETED:
                return QIcon::fromTheme("checkmark-symbolic");
            case Game::ABANDONED:
                return QIcon::fromTheme("dropboxstatus-logo-symbolic");
            default:
                return {};
        }
    }

}