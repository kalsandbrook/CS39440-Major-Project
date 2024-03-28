#include <QString>

//
// Created by kal on 13/03/24.
//

#ifndef GAMEPILE_GAMEICONCONTROLLER_H
#define GAMEPILE_GAMEICONCONTROLLER_H

#include <QDir>
#include <QImage>

class GameIconController {
public:
    GameIconController();

    static QDir getIconDirectory();

    QImage getIcon(const QString& fileName);
private:
    QDir m_iconDirectory;

    void createIconDirectory();
};


#endif //GAMEPILE_GAMEICONCONTROLLER_H
