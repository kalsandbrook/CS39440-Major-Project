//
// Created by Kal on 24/02/2024.
//

#ifndef ADDGAMEDIALOG_H
#define ADDGAMEDIALOG_H

#include "../data/game.h"
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QTextEdit>

/**
 * @brief A dialog for adding a game to the library.
 *
 * This will also provide a way to edit games in the library, in future.
 */
class GameEditDialog : public QDialog {
    Q_OBJECT
public:
    /**
     * @brief Constructs a new GameEditDialog object.
     *
     * This constructor creates the dialog, sets up the input fields and buttons, and connects the signals to the relevant slots.
     *
     * A QGridLayout is used to arrange the widgets of the dialog in a grid.
     *
     * @param parent The parent widget of the dialog.
     */
    explicit GameEditDialog(QWidget* parent = nullptr);

public slots:
    /**
     * @brief Executes the dialog.
     *
     * This clears the dialog and then shows it.
     */
    int exec() override;

    int exec(int gameId);

    /**
     * @brief Validates the input fields of the dialog.
     *
     * Verifies the input fields of the dialog (for example, if required fields are not empty.) and then calls accept() if the input is valid.
     */
    void verify();

    /**
     * Accepts the input and adds the game to the library by signaling the GameLibrary object.
     * @see GameLibrary::addGame()
     */
    void accept() override;

public:
    /**
     * @brief Returns the name of the game.
     *
     * @return The name of the game.
     */
    QString getName() const;

    /**
     * @brief Returns the description of the game.
     *
     * @return The description of the game.
     */
    QString getDesc() const;

    /**
     * @brief Returns the genres of the game.
     *
     * @return The genres of the game.
     */
    QStringList getGenre() const;

    Game::Status getStatus() const;

private:
    static void populateGenreList(QListWidget* genreList);
    bool editingGame;

    Game editedGame;
    QLabel* nameLabel;

    QLineEdit* nameLineEdit;
    QLabel* descLabel;

    QTextEdit* descTextEdit;
    QLabel* genreLabel;

    QListWidget* genreList;
    QLabel* statusLabel;

    QComboBox* statusBox;

    QDialogButtonBox* buttonBox;

    void setGameToEdit(const Game& game);
};

#endif // ADDGAMEDIALOG_H
