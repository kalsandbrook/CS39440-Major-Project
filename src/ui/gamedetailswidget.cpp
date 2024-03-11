//
// Created by kal on 07/03/24.
//

#include "gamedetailswidget.h"

GameDetailsWidget::GameDetailsWidget(QWidget* parent)
    : QWidget(parent)
{
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

void GameDetailsWidget::updateGame(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    // TODO: Add a role that returns a struct of data.
    QString id = index.data(GameLibraryModel::GameRoles::IdRole).toString();
    QString name = index.data(GameLibraryModel::GameRoles::NameRole).toString();
    QString description = index.data(GameLibraryModel::GameRoles::DescRole).toString();
    QString genres = index.data(GameLibraryModel::GameRoles::GenreRole).toString();
    QString status = index.data(GameLibraryModel::GameRoles::StatusRole).toString();

    gameIdLabel->setText("Id: " + id);
    gameNameLabel->setText("Name: " + name);
    gameDescriptionLabel->setText("Description: " + description);
    gameGenresLabel->setText("Genres: " + genres);
    gameStatusLabel->setText("Status: " + status);
}
