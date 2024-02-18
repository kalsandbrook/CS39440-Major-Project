#include <iostream>
#include <limits>
#include <QDebug>
#include <QObject>

#include "gameentry.h"


int main(int argc, char *argv[]) {

    GameEntry game0("Factorio","A factory game", QStringList{"Factory","Sandbox","Automation"});
    GameEntry game1("Factorio","A factory game", QStringList{"Factory","Sandbox","Automation"});
    GameEntry game2("Factorio","A factory game", QStringList{"Factory","Sandbox","Automation"});

    QList<GameEntry*> gameList = {&game0, &game1, &game2};
    //game.log();

    return 0;
}
