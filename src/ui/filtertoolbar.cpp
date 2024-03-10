#include "filtertoolbar.h"
#include <qboxlayout.h>
#include <qlistwidget.h>

FilterToolBar::FilterToolBar(QWidget* parent) : QToolBar(parent){
    QVBoxLayout* layout = new QVBoxLayout(this);

    QListWidget* statusFilterList = new QListWidget();

    // This should not be hard-coded.
    QStringList statusList = {"NONE","BACKLOG","PLAYING","COMPLETED","ABANDONED"};

    statusFilterList->addItems(statusList);
}
