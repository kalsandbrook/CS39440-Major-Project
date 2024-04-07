//
// Created by kal on 13/03/24.
//

#include "gameiconcontroller.h"
#include <QStandardPaths>
#include <qstandardpaths.h>

GameIconController::GameIconController()
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
