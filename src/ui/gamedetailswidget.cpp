//
// Created by kal on 07/03/24.
//

#include "gamedetailswidget.h"

#include <QProcess>

GameDetailsLine::GameDetailsLine(QString content, QWidget* parent): QLineEdit(){
    setReadOnly(true);
    setText(content);
}

GameDetailsWidget::GameDetailsWidget(QWidget* parent)
    : QWidget(parent)
{
    m_execPath = new QFileInfo();
    layout = new QVBoxLayout(this);

    titleLabel = new QLabel(tr("Game Details"));

    gameNameLabel = new QLabel("Name:");
    gameName = new GameDetailsLine("",this);

    gameDescriptionLabel = new QLabel("Description:");
    gameDescription = new QTextEdit("",this);
    gameDescription->setReadOnly(true);

    gameStatusLabel = new QLabel("Status:");
    gameStatus = new GameDetailsLine("",this);

    gameGenresLabel = new QLabel("Genres:");
    gameGenres = new GameDetailsLine("",this);
    gameDevelopersLabel = new QLabel("Developers:");
    gameDevelopers = new GameDetailsLine("",this);
    gamePublishersLabel = new QLabel("Publishers:");
    gamePublishers = new GameDetailsLine("",this);
    gamePlatformsLabel = new QLabel("Platforms:");
    gamePlatforms = new GameDetailsLine("",this);
    gameTagsLabel = new QLabel("Tags:");
    gameTags = new GameDetailsLine("",this);

    gameIdLabel = new QLabel("ID:");
    gameId = new GameDetailsLine("",this);

    launchButton = new QPushButton(QIcon::fromTheme("media-playback-start-symbolic"),"Launch",this);
    launchButton->setEnabled(false);

    layout->addWidget(titleLabel);

    layout->addWidget(gameNameLabel);
    layout->addWidget(gameName);
    layout->addWidget(gameDescriptionLabel);
    layout->addWidget(gameDescription);
    layout->addWidget(gameStatusLabel);
    layout->addWidget(gameStatus);

    layout->addWidget(gameGenresLabel);
    layout->addWidget(gameGenres);
    layout->addWidget(gameDevelopersLabel);
    layout->addWidget(gameDevelopers);
    layout->addWidget(gamePublishersLabel);
    layout->addWidget(gamePublishers);
    layout->addWidget(gamePlatformsLabel);
    layout->addWidget(gamePlatforms);
    layout->addWidget(gameTagsLabel);
    layout->addWidget(gameTags);

    layout->addWidget(gameIdLabel);
    layout->addWidget(gameId);

    layout->addWidget(launchButton);

    layout->insertStretch(-1, 1);

    setLayout(layout);

    connect(launchButton, &QPushButton::clicked, this, &GameDetailsWidget::launchGame);
};

void GameDetailsWidget::updateGame(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    // TODO: Add a role that returns a struct of data.
    QString id = index.data(GameLibraryModel::GameRoles::IdRole).toString();
    QString name = index.data(GameLibraryModel::GameRoles::NameRole).toString();
    QString description = index.data(GameLibraryModel::GameRoles::DescRole).toString();
    QString status = index.siblingAtColumn(3).data().toString();
    QString genres = index.data(GameLibraryModel::GameRoles::GenreRole).toString();
    QString developers = index.data(GameLibraryModel::GameRoles::DeveloperRole).toString();
    QString publishers = index.data(GameLibraryModel::GameRoles::PublisherRole).toString();
    QString platforms = index.data(GameLibraryModel::GameRoles::PlatformRole).toString();
    QString tags = index.data(GameLibraryModel::GameRoles::TagsRole).toString();

    gameId -> setText(id);
    gameName -> setText(name);
    gameDescription -> setText(description);
    gameStatus -> setText(status);
    gameGenres -> setText(genres);
    gameDevelopers -> setText(developers);
    gamePublishers -> setText(publishers);
    gamePlatforms -> setText(platforms);
    gameTags -> setText(tags);


    QString execPath = index.data(GameLibraryModel::GameRoles::ExecRole).toString();

    m_execPath->setFile(execPath);

    if(m_execPath->isExecutable()){
        launchButton->setEnabled(true);
    } else {
        launchButton->setEnabled(false);
    }
}

void GameDetailsWidget::launchGame(){
    QProcess* gameProc = new QProcess(this);

    gameProc->start(m_execPath->absoluteFilePath());

    gameProc->setParent(nullptr);
}
