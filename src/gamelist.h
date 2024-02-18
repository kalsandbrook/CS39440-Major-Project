//
// Created by Kal on 18/02/2024.
//

#ifndef GAMELIST_H
#define GAMELIST_H

#include <QObject>
#include <QString>
#include <qqml.h>

#include "gameentry.h"

class GameList : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString READ gameList WRITE setGameList NOTIFY gameListChanged)
    QML_ELEMENT

public:
    explicit GameList(QObject *parent = nullptr);

    QObjectList gameList();
    void setGameList(const QObjectList &gameList);

signals:
    void gameListChanged();

private:
    QObjectList m_gameList;
};


#endif //GAMELIST_H
