//
// Created by Kal on 15/02/2024.
//
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>

using namespace std;


class GameEntry : public QObject{
    Q_OBJECT
private:
    QString m_name;
    QString m_desc;
    // TODO: Convert to Genre object.
    QStringList m_genres;
public:
    GameEntry(QString name, QString desc, QStringList genres);

    void log();

    [[nodiscard]] QString getName() const { return m_name; }
    [[nodiscard]] QString getDesc() const { return m_desc; }
    [[nodiscard]] QStringList getGenres() const { return m_genres; }
};


#endif //GAMEOBJECT_H
