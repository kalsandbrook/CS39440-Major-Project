#include <QString>

//
// Created by kal on 13/03/24.
//

#ifndef GAMEPILE_GAMEICONCONTROLLER_H
#define GAMEPILE_GAMEICONCONTROLLER_H

#include <QByteArray>
#include <QDir>
#include <QEventLoop>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class GameIconController : public QObject {
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
