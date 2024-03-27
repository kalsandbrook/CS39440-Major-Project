//
// Created by kal on 13/03/24.
//

#include <QStandardPaths>
#include <qstandardpaths.h>
#include "gameiconcontroller.h"

GameIconController::GameIconController() {
    m_iconDirectory = getIconDirectory();

    createIconDirectory();
}

QDir GameIconController::getIconDirectory() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    return QDir(path + "/icons");
}

void GameIconController::createIconDirectory() {
    m_iconDirectory.mkpath(m_iconDirectory.path()) ? qDebug() << "Created icons path at: " << m_iconDirectory.path()
                                                       : qDebug() << "Icons Directory exists at: " << m_iconDirectory.path();
}

QIcon GameIconController::getIcon(const QString &fileName) {
    QString iconFile(m_iconDirectory.path() + "/" + fileName);

    QFile file(iconFile);
    QIcon icon;

    if(file.exists() && fileName != ""){
        // qDebug() << "Loading icon: " << file.fileName();
        icon.addFile(iconFile);
        return icon;
    } else{
        // qDebug() << "Couldn't find icon file: " << file.fileName();
        // Fallback icon if file can't be found.
        return icon.fromTheme("input-gamepad-symbolic");
    }
}
