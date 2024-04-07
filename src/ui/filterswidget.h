#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QList>
#include <qsortfilterproxymodel.h>
#include "gamelibraryproxymodel.h"
#include "statusfilter.h"
#include "attributefilter.h"


class FiltersWidget: public QWidget{
    Q_OBJECT
public:
    FiltersWidget(GameLibraryProxyModel* filterModel, QWidget* parent);

public slots:
    void attributeFilterChanged(Game::Attribute attribute, QString filter);
    void filterCleared();

    void statusFilterChanged(QString filter);

    void updateAttributeFilters();
private:
    GameLibraryProxyModel* m_filterModel;
    QVBoxLayout* layout;
    QList<AttributeFilter*> attributeFilters;

    StatusFilter* statusFilter;
    AttributeFilter* genreFilter;
    AttributeFilter* developerFilter;
    AttributeFilter* publisherFilter;
    AttributeFilter* platformFilter;
    AttributeFilter* usertagsFilter;
};
