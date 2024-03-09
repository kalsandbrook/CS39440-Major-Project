//
// Created by Kal on 24/02/2024.
//

#include <QGridLayout>
#include <QMessageBox>
#include <QStringList>

#include "gameeditdialog.h"
#include "../data/game.h"
#include "../data/gamelibrary.h"

GameEditDialog::GameEditDialog(QWidget* parent)
        : QDialog(parent)
        , editingGame(false)
{
    nameLabel = new QLabel(tr("Name:"));
    nameLineEdit = new QLineEdit(this);

    descLabel = new QLabel(tr("Description:"));
    descTextEdit = new QTextEdit(this);

    genreLabel = new QLabel(tr("Genres:"));
    genreList = new QListWidget(this);

    statusLabel = new QLabel(tr("Status:"));
    statusBox = new QComboBox(this);
    statusBox->addItems({"NONE","BACKLOG","PLAYING","COMPLETED","ABANDONED"});
    statusBox->setCurrentIndex(0); // Default to NONE

    populateGenreList(genreList);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &GameEditDialog::verify);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &GameEditDialog::reject);

    QSpacerItem* spacer = new QSpacerItem(20,20);
    auto* mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameLineEdit, 0, 1);
    mainLayout->addWidget(descLabel, 1, 0);
    mainLayout->addWidget(descTextEdit, 1, 1);
    mainLayout->addWidget(genreLabel, 2, 0);
    mainLayout->addWidget(genreList, 2, 1, 3, 2);
    mainLayout->addWidget(statusLabel,5,0);
    mainLayout->addWidget(statusBox,5,1);
    mainLayout->addItem(spacer,6,0);
    mainLayout->addWidget(buttonBox, 7, 1, 1, 2);

    resize(400, 300);

    setLayout(mainLayout);
}

void GameEditDialog::populateGenreList(QListWidget* genreList)
{
    QStringList genres {};
    genres << tr("Action") << tr("Adventure") << tr("Arcade") << tr("Board")
           << tr("Card") << tr("Casino") << tr("Educational") << tr("Family")
           << tr("Fighting") << tr("Music") << tr("Platform") << tr("Puzzle")
           << tr("Racing") << tr("Role-Playing") << tr("Shooter")
           << tr("Simulation") << tr("Sports") << tr("Strategy") << tr("Trivia")
           << tr("Word");
    genreList->addItems(genres);
}

void GameEditDialog::verify()
{
    if (!nameLineEdit->text().isEmpty() && !descTextEdit->toPlainText().isEmpty()) {
        if (!genreList->selectedItems().empty()) {
            accept();
        }
    } else {
        QMessageBox::information(this, tr("Error"),
                                 tr("Please fill in all fields."));
    }
}

void GameEditDialog::accept()
{
    GameLibrary& gameLibrary = GameLibrary::instance();

    if(editingGame){
        editedGame.setName(getName());
        editedGame.setDesc(getDesc());
        editedGame.setGenres(getGenre());
        editedGame.setStatus(getStatus());
        gameLibrary.updateGame(editedGame);
    } else {
        Game newGame(0, getName(), getDesc(), getGenre());
        newGame.setStatus(getStatus());
        gameLibrary.addGame(newGame);
    }
    QDialog::accept();
}

Game::Status GameEditDialog::getStatus() const { return GameHelper::stringToStatus(statusBox->currentText()); }

QString GameEditDialog::getName() const { return nameLineEdit->text(); }

QString GameEditDialog::getDesc() const { return descTextEdit->toPlainText(); }

QStringList GameEditDialog::getGenre() const
{
    QStringList genres;
    QList<QListWidgetItem*> items = genreList->selectedItems();
    for (QListWidgetItem* item : items) {
        genres << item->text();
    }
    return genres;
}

int GameEditDialog::exec()
{
    editingGame = false;
    setWindowTitle(tr("Add New Game"));

    nameLineEdit->clear();
    descTextEdit->clear();
    genreList->clearSelection();
    statusBox->setCurrentIndex(0);

    return QDialog::exec();
}

void GameEditDialog::setGameToEdit(const Game &game){
    editedGame = game;
    nameLineEdit->setText(game.name());
    descTextEdit->setText(game.desc());

    QStringList genres = game.genres();
    for (int i = 0; i < genreList->count();++i) {
        QListWidgetItem *item = genreList->item(i);
        item->setSelected(genres.contains(item->text()));
    }
}


int GameEditDialog::exec(int gameId) {
    editingGame = true;

    setWindowTitle(tr("Editing Game"));

    auto game = GameLibrary::instance().getGameById(gameId);

    setGameToEdit(game);

    return QDialog::exec();
}
