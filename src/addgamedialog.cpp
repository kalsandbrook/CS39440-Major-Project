//
// Created by Kal on 24/02/2024.
//

#include <QGridLayout>
#include <QMessageBox>
#include <QStringList>

#include "addgamedialog.h"
#include "data/game.h"
#include "data/gamelibrary.h"

AddGameDialog::AddGameDialog(QWidget* parent)
    : QDialog(parent)
{
    nameLabel = new QLabel(tr("Name:"));
    nameLineEdit = new QLineEdit(this);

    descLabel = new QLabel(tr("Description:"));
    descTextEdit = new QTextEdit(this);

    genreLabel = new QLabel(tr("Genres:"));
    genreList = new QListWidget(this);

    populateGenreList(genreList);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddGameDialog::verify);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AddGameDialog::reject);

    auto* mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameLineEdit, 0, 1);
    mainLayout->addWidget(descLabel, 1, 0);
    mainLayout->addWidget(descTextEdit, 1, 1);
    mainLayout->addWidget(genreLabel, 2, 0);
    mainLayout->addWidget(genreList, 2, 1, 3, 2);
    mainLayout->addWidget(buttonBox, 5, 1, 1, 2);

    resize(400, 300);

    setLayout(mainLayout);
    setWindowTitle(tr("Add New Game"));
}

void AddGameDialog::populateGenreList(QListWidget* genreList)
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

void AddGameDialog::verify()
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

void AddGameDialog::accept()
{
    // TODO: use database
    Game newGame(0, name(), desc(), genre());

    GameLibrary& gameLibrary = GameLibrary::instance();

    gameLibrary.addGame(newGame);

    QDialog::accept();
}

QString AddGameDialog::name() const { return nameLineEdit->text(); }

QString AddGameDialog::desc() const { return descTextEdit->toPlainText(); }

QStringList AddGameDialog::genre() const
{
    QStringList genres;
    QList<QListWidgetItem*> items = genreList->selectedItems();
    for (QListWidgetItem* item : items) {
        genres << item->text();
    }
    return genres;
}

int AddGameDialog::exec()
{
    nameLineEdit->clear();
    descTextEdit->clear();
    genreList->clearSelection();

    return QDialog::exec();
}
