#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <qlogging.h>
#include <QDebug>
#include <QString>
#include <QObject>

#include "gameentry.h"


using namespace std;

GameEntry::GameEntry(QString name, QString desc, QStringList genres)
    : m_name{std::move(name)}
      , m_desc{std::move(desc)}
      , m_genres{std::move(genres)} {
}


void GameEntry::log() {
    // qDebug() << printf("GameEntry(%s, %s, %s)",name.c_str(),desc.c_str(),genre_string.c_str());
    const QString objString = QString("GameEntry(%1, %2, %3)").arg(m_name, m_desc, m_genres.join(","));

    qDebug() << objString;
}

#include "gameentry.moc"
