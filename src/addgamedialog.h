//
// Created by Kal on 24/02/2024.
//

#ifndef ADDGAMEDIALOG_H
#define ADDGAMEDIALOG_H

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
 * @todo Add support for editing games.
 */
class AddGameDialog : public QDialog {
    Q_OBJECT
public:
    /**
     * @brief Constructs a new AddGameDialog object.
     * 
     * This constructor creates the dialog, sets up the input fields and buttons, and connects the signals to the relevant slots.
     * 
     * A QGridLayout is used to arrange the widgets of the dialog in a grid.
     * 
     * @param parent The parent widget of the dialog.
     */
    AddGameDialog(QWidget* parent);

public slots:
    /**
     * @brief Executes the dialog.
     * 
     * This clears the dialog and then shows it.
     */
    int exec() override;

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
    QString name() const;

    /**
     * @brief Returns the description of the game.
     * 
     * @return The description of the game.
     */
    QString desc() const;

    /**
     * @brief Returns the genres of the game.
     * 
     * @return The genres of the game.
     */
    QStringList genre() const;

private:
    static void populateGenreList(QListWidget* genreList);

    QLabel* nameLabel;
    QLineEdit* nameLineEdit;

    QLabel* descLabel;
    QTextEdit* descTextEdit;

    QLabel* genreLabel;
    QListWidget* genreList;

    QDialogButtonBox* buttonBox;
};

#endif // ADDGAMEDIALOG_H
