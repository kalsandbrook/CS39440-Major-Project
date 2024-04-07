
#pragma once

#include <QLabel>
#include <QListWidgetItem>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

class StatusFilter : public QWidget {
    Q_OBJECT
public:
    StatusFilter(QWidget* parent);
    void clearSelection();
private slots:
    void onFilterListActivated(QListWidgetItem* item);
signals:
    void filterChanged(QString newFilter);
    void filterCleared();

private:
    void setIconsForStatuses();

    QVBoxLayout* layout;
    QLabel* statusFiltersLabel;
    QListWidget* statusFilterList;
};
