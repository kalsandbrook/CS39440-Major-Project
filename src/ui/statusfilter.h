
#pragma once

#include "../data/game.h"
#include "../data/gamehelper.h"

#include <QLabel>
#include <QListWidgetItem>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

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
    void setIconsForStatuses();

    QVBoxLayout* layout;
    QLabel* statusFiltersLabel;
    QListWidget* statusFilterList;
};
