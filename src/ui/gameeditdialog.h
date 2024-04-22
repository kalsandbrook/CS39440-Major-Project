//
// Created by Kal on 24/02/2024.
//

#ifndef ADDGAMEDIALOG_H
#define ADDGAMEDIALOG_H

#include "../data/game.h"

#include "../data/gamepileapi.h"

#include "../data/gameiconcontroller.h"
#include "../data/gamelibrary.h"

#include <QComboBox>
#include <QCompleter>
#include <QDateEdit>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
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
     * @brief Returns the attribute of the game.
     *
     * @return The attributes of the game.
     */
    QStringList getAttributeList(QListWidget* targetList) const;

    QString getExecPath() const;

    QDate getReleaseDate() const;

    Game::Status getStatus() const;

private slots:
    void openIconFileDialog();
    void openExecFileDialog();
    void apiButtonClicked();

private:
    void setFieldsFromAPI(QMap<QString, QString> gameDetails);
    void createAttributeEdits();
    void setupAttributeEditField(QLineEdit* lineEdit, const QStringList& itemList, QListWidget* listWidget, const QString& label);

    bool editingGame;
    Game editedGame;

    QGridLayout* layout;

    QFileDialog* iconFileDialog;

    GamePileAPI* m_api;

    QIcon* gameIcon;

    QPushButton* apiFetchButton;

    QPushButton* pickIconButton;
    QLabel* pickIconLabel;

    QLabel* nameLabel;
    QLineEdit* nameLineEdit;

    QFileDialog* execPathDialog;
    QLabel* execPathLabel;
    QLineEdit* execPathEdit;
    QPushButton* execPathButton;

    QLabel* descLabel;
    QTextEdit* descTextEdit;

    QLabel* releaseDateLabel;
    QDateEdit* releaseDateEdit;

    QLabel* genreLabel;
    QCompleter* genreCompleter;
    QLineEdit* genreLineEdit;
    QListWidget* genreList;

    QLabel* developerLabel;
    QCompleter* developerCompleter;
    QLineEdit* developerLineEdit;
    QListWidget* developerList;

    QLabel* publisherLabel;
    QCompleter* publisherCompleter;
    QLineEdit* publisherLineEdit;
    QListWidget* publisherList;

    QLabel* platformLabel;
    QCompleter* platformCompleter;
    QLineEdit* platformLineEdit;
    QListWidget* platformList;

    QLabel* usertagsLabel;
    QCompleter* usertagsCompleter;
    QLineEdit* usertagsLineEdit;
    QListWidget* usertagsList;

    QLabel* statusLabel;

    QComboBox* statusBox;

    QDialogButtonBox* buttonBox;

    QFile* m_selectedIconFile;
    QString m_iconURL;

    GameLibrary* m_gameLibrary;
    GameIconController* m_iconController;

    void setGameToEdit(const Game& game);
};

#endif // ADDGAMEDIALOG_H
