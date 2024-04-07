#include "attributefilter.h"

#include "../data/gamelibrary.h"
#include <qlistwidget.h>


AttributeFilter::AttributeFilter(Game::Attribute attribute, QWidget* parent) : QWidget(parent){
    m_attribute = attribute;

    layout = new QVBoxLayout(this);
    QString filterName;
    switch(attribute){
        case Game::Attribute::GENRES:
            filterName = "Genres";
            break;
        case Game::Attribute::DEVELOPERS:
            filterName = "Developers";
            break;
        case Game::Attribute::PUBLISHERS:
            filterName = "Publishers";
            break;
        case Game::Attribute::PLATFORMS:
            filterName = "Platforms";
            break;
        case Game::Attribute::USERTAGS:
            filterName = "Tags";
            break;
        default:
            filterName = "";
            break;
    }
    filterLabel = new QLabel(filterName, this);

    filterList = new QListWidget(this);

    setupFilterList();

    layout->addWidget(filterLabel);
    layout->addWidget(filterList);

    connect(filterList, &QListWidget::itemClicked, this, &AttributeFilter::onFilterListActivated);
}

void AttributeFilter::onGameUpdated(){
    setupFilterList();
}

void AttributeFilter::setupFilterList(){
    QStringList attributeList = GameLibrary::instance().getAllOfAttribute(m_attribute);
    attributeList.removeDuplicates();

    filterList->clear();

    QListWidgetItem* anyItem = new QListWidgetItem(QIcon::fromTheme("object-rows"), "ANY");
    filterList->addItem(anyItem);

    filterList->addItems(attributeList);
}

void AttributeFilter::onFilterListActivated(QListWidgetItem* item){
    QString selectedItem = item->data(Qt::DisplayRole).toString();
    if (selectedItem == "ANY") {
        emit filterCleared();
    } else {
        emit filterChanged(m_attribute, selectedItem);
    }
}

void AttributeFilter::clearSelection(){
    filterList->clearSelection();
}



