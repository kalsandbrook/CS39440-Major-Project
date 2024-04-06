//
// Created by Kal on 24/02/2024.
//

#include <QMessageBox>
#include <QStringList>
#include <QCompleter>
#include <qnamespace.h>

#include "../data/game.h"
#include "../data/gamelibrary.h"
#include "gameeditdialog.h"
#include "../data/gamehelper.h"
#include "removableitemwidget.h"
#include "removablelistwidgetitem.h"

GameEditDialog::GameEditDialog(QWidget* parent)
    : QDialog(parent)
    , editingGame(false)
    , m_selectedIconFile(new QFile())
    , fileDialog(new QFileDialog(this, "Choose Icon"))
{
    pickIconLabel = new QLabel(tr("Icon:"));
    pickIconButton = new QPushButton(QIcon::fromTheme("document-open"),tr("Choose file..."),this);

    nameLabel = new QLabel(tr("Name:"));
    nameLineEdit = new QLineEdit(this);

    gameIcon = new QIcon();

    descLabel = new QLabel(tr("Description:"));
    descTextEdit = new QTextEdit(this);

    QStringList allGenres = GameLibrary::instance().getAllGenres();
    QCompleter* genreCompleter = new QCompleter(allGenres, this);
    genreCompleter->setCompletionMode(QCompleter::InlineCompletion);

    genreLabel = new QLabel(tr("Genres:"));
    genreLineEdit = new QLineEdit(this);
    genreLineEdit->setCompleter(genreCompleter);

    QAction* addGenreAction = new QAction(QIcon::fromTheme("list-add"),"Add Genre", this);
    genreLineEdit->addAction(addGenreAction, QLineEdit::ActionPosition::TrailingPosition);
    genreList = new QListWidget(this);
    connect(addGenreAction, &QAction::triggered, this, &GameEditDialog::addGenre);

    statusLabel = new QLabel(tr("Status:"));
    statusBox = new QComboBox(this);
    statusBox->addItems({ "NONE", "BACKLOG", "PLAYING", "COMPLETED", "ABANDONED" });
    statusBox->setCurrentIndex(0); // Default to NONE

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &GameEditDialog::verify);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &GameEditDialog::reject);

    layout = new QGridLayout();


    layout->addWidget(pickIconLabel, 0, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(pickIconButton, 0, 1, 1, 2);

    layout->addWidget(nameLabel, 1, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(nameLineEdit, 1, 1, 1, 2);

    layout->addWidget(descLabel, 2, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(descTextEdit, 2, 1, 1, 2);

    layout->addWidget(genreLabel, 3, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(genreLineEdit, 3, 1, 1, 2);

    layout->addWidget(genreList, 4, 1, 1, 2);

    layout->addWidget(statusLabel, 5, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(statusBox, 5, 1, 1, 2);

    layout->addWidget(buttonBox, 6, 1, 1, 2);

    layout->setColumnStretch(1, 20);

    resize({400,640});
    setLayout(layout);

    connect(pickIconButton, &QPushButton::clicked, this, &GameEditDialog::openFileDialog);
}

void GameEditDialog::verify()
{
    if (!nameLineEdit->text().isEmpty() && !descTextEdit->toPlainText().isEmpty()) {
        accept();
    } else {
        QMessageBox::information(this, tr("Error"),
            tr("Please fill in all fields."));
    }
}

void GameEditDialog::accept()
{
    GameLibrary& gameLibrary = GameLibrary::instance();
    GameIconController* iconController = gameLibrary.iconController;

    QString gameIconName = "";

    // TODO: This functionality should be moved to a helper class.

    if(m_selectedIconFile->exists()){
        QFileInfo iconFileInfo(m_selectedIconFile->fileName());
        QString saveDir = iconController->getIconDirectory().path() + "/" + iconFileInfo.fileName();
        m_selectedIconFile->copy(saveDir) ? qDebug() << "Writing file" << m_selectedIconFile->fileName() << "to icons folder." : qDebug() << m_selectedIconFile->fileName() << "already exists.";

        gameIconName = iconFileInfo.fileName();
    }

    if (editingGame) {
        editedGame.setName(getName());
        editedGame.setDesc(getDesc());
        editedGame.setGenres(getGenres());
        editedGame.setStatus(getStatus());
        editedGame.setIconName(gameIconName);
        gameLibrary.updateGame(editedGame);
    } else {
        Game newGame(0, getName(), getDesc(), getGenres());
        newGame.setStatus(getStatus());
        newGame.setIconName(gameIconName);
        gameLibrary.addGame(newGame);
    }
    QDialog::accept();
}

Game::Status GameEditDialog::getStatus() const { return GameHelper::stringToStatus(statusBox->currentText()); }

QString GameEditDialog::getName() const { return nameLineEdit->text(); }

QString GameEditDialog::getDesc() const { return descTextEdit->toPlainText(); }

QStringList GameEditDialog::getGenres() const
{
    QStringList genres;

    for (int i = 0; i < genreList->count(); ++i) {
            QListWidgetItem *item = genreList->item(i);
            RemovableItemWidget *itemWidget = dynamic_cast<RemovableItemWidget*>(genreList->itemWidget(item));
            if (itemWidget) {
                genres.append(itemWidget->getText());
            }
    }

    return genres;
}

void GameEditDialog::addGenre(){
    QString newGenreName = genreLineEdit->text();
    // QListWidgetItem* newGenre = new QListWidgetItem();
    // genreList->addItem(newGenre);
    // genreList->setItemWidget(newGenre, new RemovableItemWidget(newGenreName, genreList));
    RemovableListWidgetItem* newGenre = new RemovableListWidgetItem(newGenreName, genreList);
    genreLineEdit->clear();
}

int GameEditDialog::exec()
{
    editingGame = false;
    setWindowTitle(tr("Add New Game"));

    delete m_selectedIconFile;
    m_selectedIconFile = new QFile();
    nameLineEdit->clear();
    descTextEdit->clear();
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

    QStringList genres = game.genres();
    for(QString genre : genres){
        RemovableListWidgetItem* newGenre = new RemovableListWidgetItem(genre, genreList);
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

void GameEditDialog::openFileDialog() {
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setNameFilter("Image Files (*.png *.jpg *.jpeg)");

    if(fileDialog->exec()){
        m_selectedIconFile->setFileName(fileDialog->selectedFiles()[0]);
    }
}
