//
// Created by kal on 09/03/24.
//

#include "searchbarwidget.h"

SearchBarWidget::SearchBarWidget(QWidget *parent) : QWidget(parent){
    layout = new QHBoxLayout();

    searchLabel = new QLabel(tr("Search: "));
    searchIcon = QIcon::fromTheme("search");

    searchBox = new QLineEdit();
    completer = new QCompleter();

    layout->addWidget(searchLabel);
    layout->addWidget(searchBox);


    setMaximumWidth(250);
    setLayout(layout);
}
