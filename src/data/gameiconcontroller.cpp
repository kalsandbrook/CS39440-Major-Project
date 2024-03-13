//
// Created by kal on 13/03/24.
//

#include "gameiconcontroller.h"

GameIconController::GameIconController() {
    m_iconDirectory = getIconDirectory();

    createIconDirectory();
}

QDir GameIconController::getIconDirectory() {
#ifdef linux
    QString dirPrefix = {};

    if (std::getenv("XDG_DATA_HOME")) {
        dirPrefix += qgetenv("XDG_DATA_HOME");
    } else {
        dirPrefix += qgetenv("HOME") + "/.local/share";
    }

    QDir iconsDirectory(dirPrefix + "/GamePile/icons");
    return iconsDirectory;
#endif
}

void GameIconController::createIconDirectory() {
    m_iconDirectory.mkpath(m_iconDirectory.path()) ? qDebug() << "Created icons path at: " << m_iconDirectory.path()
                                                       : qDebug() << "Icons Directory exists at: " << m_iconDirectory.path();
}

void GameIconController::loadIcons() {

}

QIcon GameIconController::getIcon(const QString &fileName) {
    QString iconFile(getIconDirectory().path() + "/" + fileName);

    QFile file(iconFile);
    QIcon icon;

    if(file.exists() && fileName != ""){
        qDebug() << "Loading icon: " << file.fileName();
        icon.addFile(iconFile);
        return icon;
    } else{
        qDebug() << "Couldn't find icon file: " << file.fileName();
        // Fallback icon if file can't be found.
        return icon.fromTheme("input-gamepad-symbolic");
    }
}
