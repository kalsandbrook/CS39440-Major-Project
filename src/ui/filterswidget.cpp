#include "filterswidget.h"

#include "../data/game.h"
#include "attributefilter.h"

FiltersWidget::FiltersWidget(GameLibraryProxyModel* filterModel, QWidget* parent): QWidget(parent){
    m_filterModel = filterModel;

    layout = new QVBoxLayout();
    setLayout(layout);

    statusFilter = new StatusFilter(this);

    genreFilter = new AttributeFilter(Game::Attribute::GENRES,this);
    developerFilter = new AttributeFilter(Game::Attribute::DEVELOPERS,this);
    publisherFilter = new AttributeFilter(Game::Attribute::PUBLISHERS,this);
    platformFilter = new AttributeFilter(Game::Attribute::PLATFORMS,this);
    usertagsFilter = new AttributeFilter(Game::Attribute::USERTAGS,this);

    attributeFilters = {genreFilter, developerFilter, publisherFilter, platformFilter, usertagsFilter};

    layout->addWidget(statusFilter);
    connect(statusFilter, &StatusFilter::filterChanged, this, &FiltersWidget::statusFilterChanged);
    connect(statusFilter, &StatusFilter::filterCleared, this, &FiltersWidget::filterCleared);
    for(AttributeFilter* filter: attributeFilters){
        layout->addWidget(filter);
        connect(filter, &AttributeFilter::filterChanged, this, &FiltersWidget::attributeFilterChanged);
        connect(filter, &AttributeFilter::filterCleared, this, &FiltersWidget::filterCleared);
    }
}

void FiltersWidget::filterCleared(){

    m_filterModel->clearAllFilters();

    for(AttributeFilter* filter : attributeFilters){
        filter->clearSelection();
    }
    statusFilter->clearSelection();
}

void FiltersWidget::attributeFilterChanged(Game::Attribute attribute, QString filter){
    switch(attribute){
        case Game::Attribute::GENRES:
            m_filterModel->setFilter(3,filter);
            break;
        case Game::Attribute::DEVELOPERS:
            m_filterModel->setFilter(6,filter);
            break;
        case Game::Attribute::PUBLISHERS:
            m_filterModel->setFilter(7,filter);
            break;
        case Game::Attribute::PLATFORMS:
            m_filterModel->setFilter(8,filter);
            break;
        case Game::Attribute::USERTAGS:
            m_filterModel->setFilter(5,filter);
            break;
        default:
            break;
    }
}

void FiltersWidget::updateAttributeFilters(){
    for(AttributeFilter* filter:attributeFilters){
        filter->onGameUpdated();
    }
}

void FiltersWidget::statusFilterChanged(QString filter){
    m_filterModel->setFilter(2,filter);
}
