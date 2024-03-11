//
// Created by kal on 09/03/24.
//

#ifndef GAMEPILE_SEARCHBARWIDGET_H
#define GAMEPILE_SEARCHBARWIDGET_H

#include <QCompleter>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

class SearchBarWidget : public QWidget {
    Q_OBJECT
public:
    SearchBarWidget(QWidget* parent);
    QString getQuery();

signals:
    void searchUpdated(QString query);

private slots:
    void searchBoxEdited();

private:
    QHBoxLayout* layout;
    QLabel* searchLabel;
    QIcon searchIcon;
    QLineEdit* searchBox;
};

#endif // GAMEPILE_SEARCHBARWIDGET_H
