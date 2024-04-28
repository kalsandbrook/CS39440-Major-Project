//
// Created by Kal on 24/02/2024.
//

#include <QCompleter>
#include <QMessageBox>
#include <QStringList>
#include <QVBoxLayout>
#include <qnamespace.h>

#include "../data/game.h"
#include "../data/gamehelper.h"
#include "../data/gamelibrary.h"
#include "gameeditdialog.h"
#include "removableitemwidget.h"
#include "removablelistwidgetitem.h"

GameEditDialog::GameEditDialog(QWidget* parent)
    : QDialog(parent)
    , editingGame(false)
    , iconFileDialog(new QFileDialog(this, "Choose Icon"))
    , m_api(new GamePileAPI(this))
    , execPathDialog(new QFileDialog(this, "Choose Executable"))
    , m_selectedIconFile(new QFile())
    , m_iconURL("")
{
    m_gameLibrary = &GameLibrary::instance();
    m_iconController = m_gameLibrary->iconController;

    pickIconLabel = new QLabel(tr("Icon:"));
    pickIconButton = new QPushButton(QIcon::fromTheme("document-open"), tr("Choose file..."), this);

    nameLabel = new QLabel(tr("Name:"));
    nameLineEdit = new QLineEdit(this);

    execPathLabel = new QLabel(tr("Executable:"));
    execPathEdit = new QLineEdit(this);
    execPathButton = new QPushButton(QIcon::fromTheme("document-open-data"),"",this);

    apiFetchButton = new QPushButton(QIcon::fromTheme("download"),"", this);

    gameIcon = new QIcon();

    descLabel = new QLabel(tr("Description:"));
    descTextEdit = new QTextEdit(this);

    releaseDateLabel = new QLabel(tr("Release Date:"));
    // This can't accept null values, so defaults do 01/01/2000
    releaseDateEdit = new QDateEdit(this);

    createAttributeEdits();

    statusLabel = new QLabel(tr("Status:"));
    statusBox = new QComboBox(this);
    statusBox->addItems({ "NONE", "BACKLOG", "PLAYING", "COMPLETED", "ABANDONED" });
    statusBox->setCurrentIndex(0); // Default to NONE

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &GameEditDialog::verify);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &GameEditDialog::reject);

    layout = new QGridLayout();

    QGridLayout* leftForm = new QGridLayout();

    leftForm->addWidget(pickIconLabel, 0, 0, 1, 1, Qt::AlignRight);
    leftForm->addWidget(pickIconButton, 0, 1, 1, 2);

    leftForm->addWidget(nameLabel, 1, 0, 1, 1, Qt::AlignRight);
    leftForm->addWidget(nameLineEdit, 1, 1, 1, 1);

    leftForm->addWidget(execPathLabel, 2, 0, 1, 1, Qt::AlignRight);
    leftForm->addWidget(execPathEdit, 2, 1, 1, 1);
    leftForm->addWidget(execPathButton, 2, 2, 1, 1);

    leftForm->addWidget(apiFetchButton, 1,2,1,1);

    leftForm->addWidget(descLabel, 3, 0, 1, 1, Qt::AlignRight);
    leftForm->addWidget(descTextEdit, 3, 1, 1, 2);

    leftForm->addWidget(releaseDateLabel, 6, 0, 1, 1, Qt::AlignRight);
    leftForm->addWidget(releaseDateEdit, 6, 1,1,2);

    leftForm->addWidget(statusLabel, 7, 0, 1, 1, Qt::AlignRight);
    leftForm->addWidget(statusBox, 7, 1, 1, 2);

    // leftForm->addWidget(buttonBox, 6, 1, 1, 2);

    leftForm->setColumnStretch(1, 20);

    QVBoxLayout* rightForm = new QVBoxLayout();

    // Refactor to a function that returns a QGridLayout*?

    QGridLayout* genreLayout = new QGridLayout();
    genreLayout->addWidget(genreLabel, 0, 0, 1, 1, Qt::AlignRight);
    genreLayout->addWidget(genreLineEdit, 0, 1);
    genreLayout->addWidget(genreList, 1, 1);
    genreLayout->setColumnMinimumWidth(0, 100);
    rightForm->addLayout(genreLayout);

    QGridLayout* developerLayout = new QGridLayout();
    developerLayout->addWidget(developerLabel, 0, 0, 1, 1, Qt::AlignRight);
    developerLayout->addWidget(developerLineEdit, 0, 1);
    developerLayout->addWidget(developerList, 1, 1);
    developerLayout->setColumnMinimumWidth(0, 100);
    rightForm->addLayout(developerLayout);

    QGridLayout* publisherLayout = new QGridLayout();
    publisherLayout->addWidget(publisherLabel, 0, 0, 1, 1, Qt::AlignRight);
    publisherLayout->addWidget(publisherLineEdit, 0, 1);
    publisherLayout->addWidget(publisherList, 1, 1);
    publisherLayout->setColumnMinimumWidth(0, 100);
    rightForm->addLayout(publisherLayout);

    QGridLayout* platformLayout = new QGridLayout();
    platformLayout->addWidget(platformLabel, 0, 0, 1, 1, Qt::AlignRight);
    platformLayout->addWidget(platformLineEdit, 0, 1);
    platformLayout->addWidget(platformList, 1, 1);
    platformLayout->setColumnMinimumWidth(0, 100);
    rightForm->addLayout(platformLayout);

    QGridLayout* usertagsLayout = new QGridLayout();
    usertagsLayout->addWidget(usertagsLabel, 0, 0, 1, 1, Qt::AlignRight);
    usertagsLayout->addWidget(usertagsLineEdit, 0, 1);
    usertagsLayout->addWidget(usertagsList, 1, 1);
    usertagsLayout->setColumnMinimumWidth(0, 100);
    rightForm->addLayout(usertagsLayout);

    layout->addLayout(leftForm, 0, 0);

    layout->addLayout(rightForm, 0, 1);

    layout->addWidget(buttonBox, 1, 1);

    setLayout(layout);

    resize({ 800, 640 });
    connect(pickIconButton, &QPushButton::clicked, this, &GameEditDialog::openIconFileDialog);
    connect(execPathButton, &QPushButton::clicked, this, &GameEditDialog::openExecFileDialog);
    connect(apiFetchButton, &QPushButton::clicked, this, &GameEditDialog::apiButtonClicked);
    connect(m_api, &GamePileAPI::lookupGameResult, this, &GameEditDialog::setFieldsFromAPI);
}

void GameEditDialog::createAttributeEdits()
{
    GameLibrary& gameLibrary = GameLibrary::instance();

    genreLabel = new QLabel("Genres:");
    genreLineEdit = new QLineEdit(this);
    genreList = new QListWidget(this);
    QStringList allGenres = gameLibrary.getAllOfAttribute(Game::Attribute::GENRES);
    setupAttributeEditField(genreLineEdit, allGenres, genreList);

    developerLabel = new QLabel("Developers:");
    developerLineEdit = new QLineEdit(this);
    developerList = new QListWidget(this);
    QStringList allDevelopers = gameLibrary.getAllOfAttribute(Game::Attribute::DEVELOPERS);
    setupAttributeEditField(developerLineEdit, allDevelopers, developerList);

    publisherLabel = new QLabel("Publishers:");
    publisherLineEdit = new QLineEdit(this);
    publisherList = new QListWidget(this);
    QStringList allPublishers = gameLibrary.getAllOfAttribute(Game::Attribute::PUBLISHERS);
    setupAttributeEditField(publisherLineEdit, allPublishers, publisherList);

    platformLabel = new QLabel("Platforms:");
    platformLineEdit = new QLineEdit(this);
    platformList = new QListWidget(this);
    QStringList allPlatforms = gameLibrary.getAllOfAttribute(Game::Attribute::PUBLISHERS);
    setupAttributeEditField(platformLineEdit, allPlatforms, platformList);

    usertagsLabel = new QLabel("Tags:");
    usertagsLineEdit = new QLineEdit(this);
    usertagsList = new QListWidget(this);
    QStringList allUsertags = gameLibrary.getAllOfAttribute(Game::Attribute::USERTAGS);
    setupAttributeEditField(usertagsLineEdit, allUsertags, usertagsList);
}

void GameEditDialog::setupAttributeEditField(QLineEdit* lineEdit, const QStringList& itemList, QListWidget* listWidget)
{
    QCompleter* completer = new QCompleter(itemList, this);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    lineEdit->setCompleter(completer);

    QAction* addAction = new QAction(QIcon::fromTheme("list-add"), tr("Add"), this);

    addAction->setIcon(QIcon::fromTheme("list-add"));
    lineEdit->addAction(addAction, QLineEdit::ActionPosition::TrailingPosition);

    connect(addAction, &QAction::triggered, this, [lineEdit, listWidget]() {
        QString newItem = lineEdit->text();
        if (!newItem.isEmpty()) {
            new RemovableListWidgetItem(newItem, listWidget);
            lineEdit->clear();
        }
    });
}
void GameEditDialog::verify()
{
    if (!nameLineEdit->text().isEmpty()) {
        accept();
    } else {
        QMessageBox::information(this, tr("Error"),
            tr("Games need a name."));
    }
}

void GameEditDialog::accept()
{


    QString gameIconName = "";

    // TODO: This functionality should be moved to a helper class.

    if (m_selectedIconFile->exists()) {
        gameIconName = m_iconController->copyFileToIconsDir(m_selectedIconFile);
    } if (m_iconURL != ""){
        gameIconName = getName() + "_icon.jpg";
        m_iconController->downloadIcon(m_iconURL, gameIconName);
    }

    // TODO: This can be optimised!!
    if (editingGame) {
        editedGame.setName(getName());
        editedGame.setDesc(getDesc());
        editedGame.setExecPath(getExecPath());
        editedGame.setReleaseDate(getReleaseDate());
        editedGame.setGenres(getAttributeList(genreList));
        editedGame.setDevelopers(getAttributeList(developerList));
        editedGame.setPublishers(getAttributeList(publisherList));
        editedGame.setPlatforms(getAttributeList(platformList));
        editedGame.setUserTags(getAttributeList(usertagsList));
        editedGame.setStatus(getStatus());
        editedGame.setIconName(gameIconName);
        m_gameLibrary->updateGame(editedGame);
    } else {
        Game newGame(0, getName(), getDesc());
        newGame.setGenres(getAttributeList(genreList));
        newGame.setExecPath(getExecPath());
        newGame.setReleaseDate(getReleaseDate());
        newGame.setDevelopers(getAttributeList(developerList));
        newGame.setPublishers(getAttributeList(publisherList));
        newGame.setPlatforms(getAttributeList(platformList));
        newGame.setUserTags(getAttributeList(usertagsList));
        newGame.setStatus(getStatus());
        newGame.setIconName(gameIconName);
        m_gameLibrary->addGame(newGame);
    }
    QDialog::accept();
}

Game::Status GameEditDialog::getStatus() const { return GameHelper::stringToStatus(statusBox->currentText()); }

QString GameEditDialog::getName() const { return nameLineEdit->text(); }

QString GameEditDialog::getDesc() const { return descTextEdit->toPlainText(); }

QDate GameEditDialog::getReleaseDate() const
{
    return releaseDateEdit->date();
}

QStringList GameEditDialog::getAttributeList(QListWidget* targetList) const
{
    QStringList attributes;

    for (int i = 0; i < targetList->count(); ++i) {
        QListWidgetItem* item = targetList->item(i);
        RemovableItemWidget* itemWidget = dynamic_cast<RemovableItemWidget*>(targetList->itemWidget(item));
        if (itemWidget) {
            attributes.append(itemWidget->getText());
        }
    }

    return attributes;
}

QString GameEditDialog::getExecPath() const{
    return execPathEdit->text();
}

int GameEditDialog::exec()
{
    editingGame = false;
    setWindowTitle(tr("Add New Game"));

    delete m_selectedIconFile;
    m_selectedIconFile = new QFile();
    nameLineEdit->clear();
    descTextEdit->clear();
    execPathEdit->clear();
    releaseDateEdit->clear();
    genreList->clearSelection();
    statusBox->setCurrentIndex(0);

    return QDialog::exec();
}

void GameEditDialog::setGameToEdit(const Game& game)
{
    editedGame = game;
    m_selectedIconFile->setFileName(GameIconController::getIconDirectory().path() + "/" + game.iconName());

    nameLineEdit->setText(game.name());
    descTextEdit->setText(game.desc());
    execPathEdit->setText(game.execPath());

    releaseDateEdit->setDate(game.releaseDate());

    QStringList genres = game.genres();
    for (QString genre : genres) {
        new RemovableListWidgetItem(genre, genreList);
    }
    QStringList developers = game.developers();
    for (QString developer : developers) {
        new RemovableListWidgetItem(developer, developerList);
    }
    QStringList publishers = game.publishers();
    for (QString publisher : publishers) {
        new RemovableListWidgetItem(publisher, publisherList);
    }
    QStringList platforms = game.platforms();
    for (QString platform : platforms) {
        new RemovableListWidgetItem(platform, platformList);
    }
    QStringList usertags = game.userTags();
    for (QString usertag : usertags) {
        new RemovableListWidgetItem(usertag, usertagsList);
    }
}

int GameEditDialog::exec(int gameId)
{
    editingGame = true;

    setWindowTitle(tr("Editing Game"));
    auto game = GameLibrary::instance().getGameById(gameId);

    setGameToEdit(game);

    return QDialog::exec();
}

void GameEditDialog::openIconFileDialog()
{
    iconFileDialog->setFileMode(QFileDialog::ExistingFile);
    iconFileDialog->setNameFilter("Image Files (*.png *.jpg *.jpeg)");

    if (iconFileDialog->exec()) {
        m_selectedIconFile->setFileName(iconFileDialog->selectedFiles()[0]);
    }
}

void GameEditDialog::openExecFileDialog(){
    iconFileDialog->setFileMode(QFileDialog::ExistingFile);
    if(execPathDialog->exec()){
        execPathEdit->setText(execPathDialog->selectedFiles()[0]);
    }
}

void GameEditDialog::apiButtonClicked(){
    if(nameLineEdit->text().isEmpty()){
        return;
    }
    m_api->startLookupGame(nameLineEdit->text());

}

void GameEditDialog::setFieldsFromAPI(QList<QMap<QString,QString>> gameDetailsList){
    QList<QString> gameTitles;
    QMap<QString,QString> gameDetails;

    for(auto game : gameDetailsList){
        gameTitles.append(game["name"]);
    }

    bool ok;
    QString selectedTitle = QInputDialog::getItem(this, "Select Game", "Select a game to import:", gameTitles, 0, false, &ok);

    if(ok && !selectedTitle.isEmpty()){
    for(auto game : gameDetailsList){
        if(game["name"] == selectedTitle){
            gameDetails = game;
        }
    }

    qDebug() << gameDetails;

    nameLineEdit->setText(gameDetails["name"]);

    descTextEdit->setText(gameDetails["description"]);

    QDate date = QDate::fromString(gameDetails["releaseDate"], "yyyy-MM-dd");
    releaseDateEdit->setDate(date);

    QStringList genres = gameDetails["genres"].split(", ");
    genreList->clear();
    for(QString genre : genres){
        new RemovableListWidgetItem(genre, genreList);
    }

    QStringList developers = gameDetails["developers"].split(", ");
    developerList->clear();
    for(QString developer : developers){
        new RemovableListWidgetItem(developer, developerList);
    }

    QStringList publishers = gameDetails["publishers"].split(", ");
    publisherList->clear();
    for(QString publisher : publishers){
        new RemovableListWidgetItem(publisher, publisherList);
    }

    QStringList platforms = gameDetails["platforms"].split(", ");
    platformList->clear();
    for(QString platform : platforms){
        new RemovableListWidgetItem(platform, platformList);
    }

    m_iconURL = gameDetails["iconURL"];
    }
}
