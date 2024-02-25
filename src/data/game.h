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
    Game(QString name, QString desc, QStringList genre)
        : m_name(std::move(name))
        , m_desc(std::move(desc))
        , m_genre(std::move(genre))
    {
    }

    [[nodiscard]] QString name() const { return m_name; }
    [[nodiscard]] QString desc() const { return m_desc; }
    [[nodiscard]] QStringList genre() const { return m_genre; }

private:
    QString m_name;
    QString m_desc;
    QStringList m_genre;
};

#endif // GAME_H
