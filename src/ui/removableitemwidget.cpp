#include "removableitemwidget.h"

RemovableItemWidget::RemovableItemWidget(const QString& text, QListWidget* parentListWidget)
    : QWidget(parentListWidget)
    , listWidget(parentListWidget)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    label = new QLabel(text, this);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(label);

    QPushButton* removeButton = new QPushButton(this);

    removeButton->setIcon(QIcon::fromTheme("delete"));
    removeButton->setMaximumSize({ 16, 16 });
    removeButton->setFlat(true);

    layout->addWidget(removeButton);

    connect(removeButton, &QPushButton::clicked, this, &RemovableItemWidget::deleteButtonClicked);
}

void RemovableItemWidget::deleteButtonClicked()
{
    emit deleteRequested(this);
}

QString RemovableItemWidget::getText() const
{
    return label->text();
}
