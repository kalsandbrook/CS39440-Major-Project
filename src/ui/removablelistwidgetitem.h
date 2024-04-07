#pragma once

#include <QListWidgetItem>

class RemovableListWidgetItem : public QListWidgetItem {
public:
    RemovableListWidgetItem(const QString& text, QListWidget* parentListWidget);
};
