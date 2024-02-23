//
// Created by Kal on 18/02/2024.
//

#ifndef GAMEENTRY_H
#define GAMEENTRY_H
#include <qlist.h>
#include <qstring.h>

#include <utility>


class GameEntry
{
public:
    GameEntry();
    GameEntry(const QString& name, const QString& desc, const QList<QString>& genres)
    : m_name(name),
      m_desc(desc),
      m_genres(genres) {
    }

    GameEntry(QString&& name, QString&& desc, QList<QString>&& genres)
        : m_name(std::move(name)),
          m_desc(std::move(desc)),
          m_genres(std::move(genres)) {
    }
    [[nodiscard]] QString name() const { return m_name; }
    [[nodiscard]] QString desc() const { return m_desc; }
    [[nodiscard]] QList<QString> genres() const { return m_genres; }
private:
    QString m_name;
    QString m_desc;
    QList<QString> m_genres;
};

#endif //GAMEENTRY_H
