#include "statusfilter.h"
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <QLabel>

StatusFilter::StatusFilter(QWidget *parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* statusFiltersLabel = new QLabel(tr("Game Status"),this);
    QListWidget* statusFilterList = new QListWidget();

    // This should not be hard-coded.
    QStringList statusList = {"ANY","NONE","BACKLOG","PLAYING","COMPLETED","ABANDONED"};

    statusFilterList->addItems(statusList);

    layout->addWidget(statusFiltersLabel);
    layout->addWidget(statusFilterList);

    connect(statusFilterList,&QListWidget::itemActivated,this,&StatusFilter::onStatusFilterListActivated);
}

void StatusFilter::onStatusFilterListActivated(QListWidgetItem *item) {
    QString selectedItem = item->data(Qt::DisplayRole).toString();
    if(selectedItem == "ANY"){
        filterCleared();
    }
    else{
        Game::Status selectedStatus = GameHelper::stringToStatus(selectedItem);
        emit filterChanged(selectedStatus);
    }

}
