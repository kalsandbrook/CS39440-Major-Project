//
// Created by kal on 07/03/24.
//

#include "game.h"

Game::Game(int id, QString name, QString desc, QStringList genres)
    : m_id(id)
    , m_name(std::move(name))
    , m_desc(std::move(desc))
    , m_genres(std::move(genres))
{
    m_status = NONE;
}

int Game::id() const { return m_id; }

QString Game::name() const { return m_name; }

QString Game::desc() const { return m_desc; }

QStringList Game::genres() const { return m_genres; }

Game::Status Game::status() const { return m_status; }

void Game::setId(int newId) { m_id = newId; }

void Game::setName(QString name) { m_name = std::move(name); }

void Game::setDesc(QString desc) { m_desc = std::move(desc); }

void Game::setGenres(QStringList genres) { m_genres = std::move(genres); }

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
