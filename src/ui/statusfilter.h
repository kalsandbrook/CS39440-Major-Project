
#pragma once

#include "../data/game.h"
#include "../data/gamehelper.h"

#include <QToolBar>
#include <QWidget>
#include <QListWidgetItem>

class StatusFilter : public QWidget{
    Q_OBJECT
public:
    StatusFilter(QWidget* parent);
private slots:
    void onStatusFilterListActivated(QListWidgetItem *item);
signals:
    void filterChanged(Game::Status newStatusFilter);
    void filterCleared();
};
