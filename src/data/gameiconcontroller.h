#include <QString>

//
// Created by kal on 13/03/24.
//

#ifndef GAMEPILE_GAMEICONCONTROLLER_H
#define GAMEPILE_GAMEICONCONTROLLER_H

#include <QDir>
#include <QImage>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

class GameIconController: public QObject {
    Q_OBJECT
public:
    GameIconController(QObject* parent = nullptr);

    QString copyFileToIconsDir(QFile* file);

    void downloadIcon(const QUrl& URLString, const QString& filePath);

    static QDir getIconDirectory();

    QImage getIcon(const QString& fileName);

private:
    QDir m_iconDirectory;
    void createIconDirectory();
};

#endif // GAMEPILE_GAMEICONCONTROLLER_H
