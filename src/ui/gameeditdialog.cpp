//
// Created by Kal on 24/02/2024.
//

#include <QMessageBox>
#include <QStringList>

#include "../data/game.h"
#include "../data/gamelibrary.h"
#include "gameeditdialog.h"

GameEditDialog::GameEditDialog(QWidget* parent)
    : QDialog(parent)
    , editingGame(false)
{

    pickIconLabel = new QLabel(tr("Icon:"));
    pickIconButton = new QPushButton(QIcon::fromTheme("document-open"),tr("Choose file..."),this);

    nameLabel = new QLabel(tr("Name:"));
    nameLineEdit = new QLineEdit(this);

    descLabel = new QLabel(tr("Description:"));
    descTextEdit = new QTextEdit(this);

    genreLabel = new QLabel(tr("Genres:"));
    genreList = new QListWidget(this);

    statusLabel = new QLabel(tr("Status:"));
    statusBox = new QComboBox(this);
    statusBox->addItems({ "NONE", "BACKLOG", "PLAYING", "COMPLETED", "ABANDONED" });
    statusBox->setCurrentIndex(0); // Default to NONE

    populateGenreList(genreList);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &GameEditDialog::verify);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &GameEditDialog::reject);

    layout = new QFormLayout();

    layout->addRow(pickIconLabel, pickIconButton);
    layout->addRow(nameLabel,nameLineEdit);
    layout->addRow(descLabel,descTextEdit);
    layout->addRow(genreLabel,genreList);
    layout->addRow(statusLabel,statusBox);

    layout->addRow(buttonBox);

    resize({400,640});
    setLayout(layout);

    connect(pickIconButton, &QPushButton::clicked, this, &GameEditDialog::openFileDialog);
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
    GameIconController* iconController = gameLibrary.iconController;

    QString gameIconName {};

    // TODO: This functionality should be moved to a helper class.

    if(m_selectedIconFile->exists()){
        QFileInfo iconFileInfo(m_selectedIconFile->fileName());
        QString saveDir = iconController->getIconDirectory().path() + "/" + iconFileInfo.fileName();
        m_selectedIconFile->copy(saveDir) ? qDebug() << "Writing file " << m_selectedIconFile->fileName() << " to icons folder." : qDebug() << m_selectedIconFile->fileName() << " already exists.";

        gameIconName = iconFileInfo.fileName();
    }

    if (editingGame) {
        editedGame.setName(getName());
        editedGame.setDesc(getDesc());
        editedGame.setGenres(getGenre());
        editedGame.setStatus(getStatus());
        editedGame.setIconName(gameIconName);
        gameLibrary.updateGame(editedGame);
    } else {
        Game newGame(0, getName(), getDesc(), getGenre());
        newGame.setStatus(getStatus());
        newGame.setIconName(gameIconName);
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

void GameEditDialog::setGameToEdit(const Game& game)
{
    editedGame = game;
    nameLineEdit->setText(game.name());
    descTextEdit->setText(game.desc());

    QStringList genres = game.genres();
    for (int i = 0; i < genreList->count(); ++i) {
        QListWidgetItem* item = genreList->item(i);
        item->setSelected(genres.contains(item->text()));
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
    fileDialog = new QFileDialog(this, "Choose Icon");
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setNameFilter("Image Files (*.png *.jpg *.jpeg)");

    if(fileDialog->exec()){
        m_selectedIconFile = new QFile(fileDialog->selectedFiles()[0]);
    }
}
