#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>

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
