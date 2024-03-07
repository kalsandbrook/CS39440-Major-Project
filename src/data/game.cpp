//
// Created by kal on 07/03/24.
//

#include "game.h"

Game::Game(int id, QString name, QString desc, QStringList genres)
        : m_id(id)
        , m_name(std::move(name))
        , m_desc(std::move(desc))
        , m_genres(std::move(genres))
        {}

int Game::id() const { return m_id; }

QString Game::name() const { return m_name; }

QString Game::desc() const { return m_desc; }

QStringList Game::genres() const { return m_genres; }

void Game::setId(int newId) { m_id = newId; }

void Game::setName(QString name) { m_name = std::move(name); }

void Game::setDesc(QString desc) { m_desc = std::move(desc); }

void Game::setGenres(QStringList genres) { m_genres = std::move(genres); }
