//
// Created by kal on 09/03/24.
//

#ifndef GAMEPILE_SEARCHBARWIDGET_H
#define GAMEPILE_SEARCHBARWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QLineEdit>
#include <QCompleter>

class SearchBarWidget : public QWidget {
public:
    SearchBarWidget(QWidget* parent);
private:
    QHBoxLayout* layout;
    QLabel* searchLabel;
    QIcon searchIcon;
    QLineEdit* searchBox;
    QCompleter* completer;
};


#endif //GAMEPILE_SEARCHBARWIDGET_H
