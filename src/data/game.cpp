//
// Created by kal on 07/03/24.
//

#include "game.h"

#include <utility>

Game::Game(int id, QString name, QString desc)
    : m_id(id)
    , m_name(std::move(name))
    , m_desc(std::move(desc))
{
    m_status = NONE;
    m_genres = {};
    m_developers = {};
    m_publishers = {};
    m_platforms = {};
    m_releaseDate = {};
    m_user_tags = {};
}

int Game::id() const { return m_id; }

QString Game::name() const { return m_name; }

QString Game::desc() const { return m_desc; }

QStringList Game::genres() const { return m_genres; }

QString Game::iconName() const { return m_iconName; }

Game::Status Game::status() const { return m_status; }

void Game::setId(int newId) { m_id = newId; }

void Game::setName(QString name) { m_name = std::move(name); }

void Game::setDesc(QString desc) { m_desc = std::move(desc); }

void Game::setGenres(QStringList genres) { m_genres = std::move(genres); }

void Game::setIconName(QString iconName) {
    m_iconName = std::move(iconName);
}

void Game::setStatus(Status status)
{
    m_status = status;
}

QString Game::status_str() const
{
    switch (m_status) {
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

QStringList Game::developers() const{
    return m_developers;
};

QStringList Game::publishers() const{
    return m_publishers;
};

QStringList Game::platforms() const{
    return m_platforms;
};

QStringList Game::userTags() const{
    return m_user_tags;
};

QDate Game::releaseDate() const{
    return m_releaseDate;
};
