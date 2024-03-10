
#pragma once

#include "../data/game.h"

#include <QToolBar>

class FilterToolBar : public QToolBar{
    Q_OBJECT
public:
    FilterToolBar(QWidget* parent);

signals:
    void filterChanged(Game::Status newStatus);
};
