#pragma once

#include "../data/game.h"

#include <QLabel>
#include <QListWidgetItem>
#include <QSortFilterProxyModel>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

/**
 * @brief A class representing the attribute filter.
 * Used to filter games by attribute.
 * @see FiltersWidget
*/
class AttributeFilter : public QWidget {
    Q_OBJECT
public:
    AttributeFilter(Game::Attribute attribute, QWidget* parent);
    void clearSelection();
public slots:
    void onFilterListActivated(QListWidgetItem* item);
    void onGameUpdated();
signals:
    void filterChanged(Game::Attribute attribute, QString newFilter);
    void filterCleared();

private:
    void setupFilterList();

    Game::Attribute m_attribute;
    QVBoxLayout* layout;
    QLabel* filterLabel;
    QListWidget* filterList;
};
