//
// Created by kal on 07/03/24.
//

#ifndef GAMEPILE_GAMEDETAILSWIDGET_H
#define GAMEPILE_GAMEDETAILSWIDGET_H

#include "../data/model/gamelibrarymodel.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

class GameDetailsWidget : public QWidget {
public:
    GameDetailsWidget(QWidget* parent);
public slots:
    void updateGame(const QModelIndex& index);

private:
    GameLibraryModel* m_model;

    QVBoxLayout* layout;

    QLabel* titleLabel;

    QLabel* gameNameLabel;
    QLabel* gameDescriptionLabel;
    QLabel* gameGenresLabel;
    QLabel* gameIdLabel;
    QLabel* gameStatusLabel;
};

#endif // GAMEPILE_GAMEDETAILSWIDGET_H
