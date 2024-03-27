//
// Created by Kal on 23/02/2024.
//

#ifndef GAME_H
#define GAME_H
#include <QList>
#include <QObject>
#include <QString>
#include <QIcon>

/**
 * @brief A class representing a video game.
 *
 * This class represents a video game, and contains information about the game such as its name, description, and genres.
 *
 * This will contain more fields in future, such as the game's release date, developer, and publisher.
 * As it stands (as of 2024-03-03), the class is very simple and only contains the game's name, description, and genres.
 */
class Game {
public:
    /**
     * @brief Constructs a new Game object.
     *
     * This constructor creates a new Game object with the given ID, name, description, and genres.
     * The id is typically overwritten when the game is added to the library.
     * @param id The ID of the game.
     * @param name The name of the game.
     * @param desc The description of the game.
     * @param genres The genres(s) of the game.
     */
    Game(int id, QString name, QString desc, QStringList genres);
    Game() = default;

    enum Status { // Possible expansion of this feature: allow users to set custom status?
        NONE = 0,
        BACKLOG = 1,
        PLAYING = 2,
        COMPLETED = 3,
        ABANDONED = 4
    };

    /**
     * @brief Sets the ID of the game.
     *
     * @param newId
     */
    void setId(int newId);
    /**
     * @brief Sets the Name of the game.
     *
     * @param name
     */
    void setName(QString name);
    /**
     * @brief Sets the Description of the game.
     *
     * @param desc
     */
    void setDesc(QString desc);
    /**
     * @brief Sets the list of genres for the game.
     *
     * @param genres
     */
    void setGenres(QStringList genres);

    void setStatus(Status status);

    void setIconName(QString iconName);

    /**
     * @brief Returns the ID of the game.
     *
     * @return The ID of the game.
     */
    [[nodiscard]] int id() const;

    /**
     * @brief Returns the name of the game.
     *
     * @return The name of the game.
     */
    [[nodiscard]] QString name() const;
    /**
     * @brief Returns the description of the game.
     *
     * @return The description of the game.
     */
    [[nodiscard]] QString desc() const;
    /**
     * @brief Returns the genres of the game.
     *
     * @return The genres of the game.
     */
    [[nodiscard]] QStringList genres() const;

    QString iconName() const;

    Status status() const;

    QString status_str() const;
private:
    int m_id {};
    QString m_iconName;
    QString m_name;
    QString m_desc;
    QStringList m_genres;

    Status m_status;
};

#endif // GAME_H
