#include "gamelibraryproxymodel.h"

GameLibraryProxyModel::GameLibraryProxyModel(QObject* parent, QAbstractItemModel* sourceModel) : QSortFilterProxyModel(parent){
    setSourceModel(sourceModel);
}

void GameLibraryProxyModel::setFilter(int column, QString filter){
    setFilterKeyColumn(column);

    setFilterFixedString(filter);
}

void GameLibraryProxyModel::clearAllFilters(){
    setFilterFixedString("");
}
