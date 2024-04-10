//
// Created by kal on 13/03/24.
//

#include "gameiconcontroller.h"
#include <QStandardPaths>
#include <qstandardpaths.h>

GameIconController::GameIconController(QObject* parent) : QObject(parent)
{
    m_iconDirectory = getIconDirectory();
    createIconDirectory();

}

QDir GameIconController::getIconDirectory()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    return QDir(path + "/icons");
}

void GameIconController::createIconDirectory()
{
    m_iconDirectory.mkpath(m_iconDirectory.path()) ? qDebug() << "Created icons path at: " << m_iconDirectory.path()
                                                   : qDebug() << "Icons Directory exists at: " << m_iconDirectory.path();
}

QImage GameIconController::getIcon(const QString& fileName)
{
    QString iconFile(m_iconDirectory.path() + "/" + fileName);

    QFile file(iconFile);
    QImage icon;

    if (file.exists() && fileName != "") {
        // qDebug() << "Loading icon: " << file.fileName();
        icon.load(iconFile);
        return icon;
    }
    return icon;
}

QString GameIconController::copyFileToIconsDir(QFile* file){
        QFileInfo iconFileInfo(file->fileName());
        QString saveDir = this->getIconDirectory().path() + "/" + iconFileInfo.fileName();
        file->copy(saveDir) ? qDebug() << "Writing file" << file->fileName() << "to icons folder." : qDebug() << file->fileName() << "already exists.";

        return iconFileInfo.fileName();
}

void GameIconController::downloadIcon(const QUrl& url, const QString& fileName) {
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QNetworkReply *reply = manager->get(QNetworkRequest(url));

        connect(reply, &QNetworkReply::finished, [=]() {
            if (reply->error() == QNetworkReply::NoError) {
                QFile file(getIconDirectory().filePath(fileName));
                if (file.open(QIODevice::WriteOnly)) {
                    file.write(reply->readAll());
                    file.close();
                    qDebug() << "Image downloaded successfully to" << fileName;
                } else {
                    qDebug() << "Failed to open file for writing:" << file.errorString();
                }
            } else {
                qDebug() << "Error downloading image:" << reply->errorString();
            }

            reply->deleteLater();
            manager->deleteLater();
        });
}
