#pragma once

#include <qabstractitemmodel.h>
#include <qsortfilterproxymodel.h>

class GameLibraryProxyModel : public QSortFilterProxyModel {
public:
    GameLibraryProxyModel(QObject* parent, QAbstractItemModel* sourceModel);

public slots:
    void onSearchUpdated();

    void setFilter(int column, QString filter);

    void clearFilter(int column, QString filter);

    void clearAllFilters();
};
