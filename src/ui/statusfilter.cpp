#include "statusfilter.h"
#include <QLabel>
#include <qboxlayout.h>
#include <qlistwidget.h>

StatusFilter::StatusFilter(QWidget* parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    statusFiltersLabel = new QLabel(tr("Game Status"), this);
    statusFilterList = new QListWidget();

    // This should not be hard-coded.
    QStringList statusList = { "ANY", "NONE", "BACKLOG", "PLAYING", "COMPLETED", "ABANDONED" };

    statusFilterList->addItems(statusList);
    setIconsForStatuses();

    layout->addWidget(statusFiltersLabel);
    layout->addWidget(statusFilterList);

    connect(statusFilterList, &QListWidget::itemActivated, this, &StatusFilter::onStatusFilterListActivated);
}

void StatusFilter::onStatusFilterListActivated(QListWidgetItem* item)
{
    QString selectedItem = item->data(Qt::DisplayRole).toString();
    if (selectedItem == "ANY") {
        filterCleared();
    } else {
        Game::Status selectedStatus = GameHelper::stringToStatus(selectedItem);
        emit filterChanged(selectedStatus);
    }
}

void StatusFilter::setIconsForStatuses() {
    for (int i = 0; i < statusFilterList->count(); ++i) {
        auto item = statusFilterList->item(i);

        // Handles the "ANY" status in the list. This should not have an icon.
        if(item->text() != "ANY")
            item->setIcon(GameHelper::getStatusIcon(item->text()));
    }
}