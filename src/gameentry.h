//
// Created by Kal on 18/02/2024.
//

#ifndef GAMEENTRY_H
#define GAMEENTRY_H

#include<QObject>

class GameEntry : public QObject{
    Q_OBJECT
public:
    QString m_name;
    QString m_desc;
    QList<QString> m_genres;

    // Constructor
    GameEntry(QString name, QString desc, QList<QString> genres);
};

#endif //GAMEENTRY_H
