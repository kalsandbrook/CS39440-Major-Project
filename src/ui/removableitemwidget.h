#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>

/**
 * @brief A class representing a removable item widget.
 * 
 * This is a variation of QListWidget, where items have a trash button to remove them. Used for attribute lists in the GameEditDialog.
*/
class RemovableItemWidget : public QWidget {
    Q_OBJECT
public:
    RemovableItemWidget(const QString& text, QListWidget* parentListWidget);
    QString getText() const;

private slots:
    void deleteButtonClicked();

signals:
    void deleteRequested(RemovableItemWidget* item);

private:
    QLabel* label;
    QListWidget* listWidget;
};
