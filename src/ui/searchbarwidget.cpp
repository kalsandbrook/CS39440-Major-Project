//
// Created by kal on 09/03/24.
//

#include "searchbarwidget.h"

SearchBarWidget::SearchBarWidget(QWidget* parent)
    : QWidget(parent)
{
    layout = new QHBoxLayout();

    searchLabel = new QLabel(tr("Search: "));
    searchIcon = QIcon::fromTheme("search");

    searchBox = new QLineEdit();

    layout->addWidget(searchLabel);
    layout->addWidget(searchBox);

    setLayout(layout);

    connect(searchBox, &QLineEdit::editingFinished, this, &SearchBarWidget::searchBoxEdited);
}

void SearchBarWidget::searchBoxEdited()
{
    searchUpdated(searchBox->text());
}

QString SearchBarWidget::getQuery()
{
    return searchBox->text();
}
