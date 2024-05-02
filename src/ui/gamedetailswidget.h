//
// Created by kal on 07/03/24.
//

#ifndef GAMEPILE_GAMEDETAILSWIDGET_H
#define GAMEPILE_GAMEDETAILSWIDGET_H

#include "../data/model/gamelibrarymodel.h"

#include <QFileInfo>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class GameDetailsLine : public QLineEdit {
public:
    GameDetailsLine(QString content, QWidget* parent);
};

/**
 * @brief A class representing the game details widget.
 * Displays the details of a game in the library. Uses readOnly QLineEdit for displaying game details.
 * A button is provided to launch the game, which is only enabled when a valid executable path is set.
*/
class GameDetailsWidget : public QWidget {
public:
    GameDetailsWidget(QWidget* parent);
public slots:
    void updateGame(const QModelIndex& index);

    void launchGame();

private:
    GameLibraryModel* m_model;

    QFileInfo* m_execPath;

    QVBoxLayout* layout;

    QLabel* titleLabel;

    QLabel* gameNameLabel;
    GameDetailsLine* gameName;
    QLabel* gameDescriptionLabel;
    QTextEdit* gameDescription;
    QLabel* gameStatusLabel;
    GameDetailsLine* gameStatus;

    QLabel* gameGenresLabel;
    GameDetailsLine* gameGenres;
    QLabel* gameDevelopersLabel;
    GameDetailsLine* gameDevelopers;
    QLabel* gamePublishersLabel;
    GameDetailsLine* gamePublishers;
    QLabel* gamePlatformsLabel;
    GameDetailsLine* gamePlatforms;
    QLabel* gameTagsLabel;
    GameDetailsLine* gameTags;

    QLabel* gameIdLabel;
    GameDetailsLine* gameId;

    QPushButton* launchButton;
};

#endif // GAMEPILE_GAMEDETAILSWIDGET_H
