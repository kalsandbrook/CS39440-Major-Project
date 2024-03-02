//
// Created by Kal on 23/02/2024.
//

#ifndef GAME_H
#define GAME_H
#include <QList>
#include <QString>
#include <utility>

class Game {
public:
    Game(int id, QString name, QString desc, QStringList genre)
        : m_id(id)
        , m_name(std::move(name))
        , m_desc(std::move(desc))
        , m_genre(std::move(genre))
    {
    }

    void setId(int newId) { m_id = newId; }
    int getId() const { return m_id; }
    [[nodiscard]] QString name() const { return m_name; }
    [[nodiscard]] QString desc() const { return m_desc; }
    [[nodiscard]] QStringList genre() const { return m_genre; }

private:
    int m_id;
    QString m_name;
    QString m_desc;
    QStringList m_genre;
};

#endif // GAME_H
