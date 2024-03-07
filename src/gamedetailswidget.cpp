//
// Created by kal on 07/03/24.
//

#include "gamedetailswidget.h"

GameDetailsWidget::GameDetailsWidget(GameLibraryModel* model, QWidget *parent) : QWidget(parent){
    m_model = model;
    layout = new QVBoxLayout(this);

    gameIdLabel = new QLabel();
    gameNameLabel = new QLabel();
    gameDescriptionLabel = new QLabel();
    gameGenresLabel = new QLabel();
    gameStatusLabel = new QLabel();

    layout->addWidget(gameIdLabel);
    layout->addWidget(gameNameLabel);
    layout->addWidget(gameDescriptionLabel);
    layout->addWidget(gameGenresLabel);
    layout->addWidget(gameStatusLabel);

    setLayout(layout);
};

void GameDetailsWidget::updateGame(const QModelIndex &index) {
    if(!index.isValid()) return;

    const Game &game = m_model->getGame(index);

    gameIdLabel->setText("Id: " + QString::number(game.id()));
    gameNameLabel->setText("Name: " + game.name());
    gameDescriptionLabel->setText("Description: " + game.desc());
    gameGenresLabel->setText("Genres: " + game.genres().join(','));
    gameStatusLabel->setText("Status: " + game.status_str());
}
