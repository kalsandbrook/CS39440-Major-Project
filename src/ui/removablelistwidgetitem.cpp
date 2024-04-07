#include "removablelistwidgetitem.h"
#include "removableitemwidget.h"

RemovableListWidgetItem::RemovableListWidgetItem(const QString& text, QListWidget* parentListWidget)
    : QListWidgetItem(parentListWidget)
{
    RemovableItemWidget* widget = new RemovableItemWidget(text, parentListWidget);
    setSizeHint(widget->sizeHint());
    parentListWidget->setItemWidget(this, widget);

    QObject::connect(widget, &RemovableItemWidget::deleteRequested, parentListWidget, [=](RemovableItemWidget* item) {
        parentListWidget->removeItemWidget(this);
        delete this;
    });
}
