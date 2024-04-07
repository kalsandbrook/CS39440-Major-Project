#include "statusfilter.h"
#include "../data/gamehelper.h"
#include <QLabel>
#include <qboxlayout.h>
#include <qlistwidget.h>

StatusFilter::StatusFilter(QWidget* parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    statusFiltersLabel = new QLabel(tr("Game Status"), this);
    statusFilterList = new QListWidget(this);

    // This should not be hard-coded.
    QStringList statusList = { "ANY", "NONE", "BACKLOG", "PLAYING", "COMPLETED", "ABANDONED" };

    statusFilterList->addItems(statusList);
    setIconsForStatuses();

    layout->addWidget(statusFiltersLabel);
    layout->addWidget(statusFilterList);

    connect(statusFilterList, &QListWidget::itemClicked, this, &StatusFilter::onFilterListActivated);
}

void StatusFilter::onFilterListActivated(QListWidgetItem* item)
{
    QString selectedItem = item->data(Qt::DisplayRole).toString();
    if (selectedItem == "ANY") {
        emit filterCleared();
    } else {
        emit filterChanged(selectedItem);
    }
}

void StatusFilter::setIconsForStatuses()
{
    for (int i = 0; i < statusFilterList->count(); ++i) {
        auto item = statusFilterList->item(i);

        // Handles the "ANY" status in the list. This should not have an icon.
        if (item->text() == "ANY")
            item->setIcon(QIcon::fromTheme("object-rows"));
        else
            item->setIcon(GameHelper::getStatusIcon(item->text()));
    }
}

void StatusFilter::clearSelection(){
    statusFilterList->clearSelection();
}
