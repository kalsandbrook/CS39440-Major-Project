
#pragma once

#include "../data/game.h"
#include "../data/gamehelper.h"

#include <QListWidgetItem>
#include <QToolBar>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class StatusFilter : public QWidget {
    Q_OBJECT
public:
    StatusFilter(QWidget* parent);
private slots:
    void onStatusFilterListActivated(QListWidgetItem* item);
signals:
    void filterChanged(Game::Status newStatusFilter);
    void filterCleared();

private:
    QVBoxLayout* layout;
    QLabel* statusFiltersLabel;
    QListWidget* statusFilterList;
};
