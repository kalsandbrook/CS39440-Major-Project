#pragma once

#include "gamepileapiworker.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QProcess>
#include <QThread>

/**
 * @brief A class representing the GamePile API.
 * Used to run API operations.
*/
class GamePileAPI : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructs a new GamePileAPI object.
     * @param parent The parent of the object.
    */
    explicit GamePileAPI(QObject* parent = nullptr);
    ~GamePileAPI();

    /**
     * @brief Starts the lookup game operation.
     * @param gameName The name of the game to look up.
    */
    void startLookupGame(const QString& gameName);

signals:
    /**
     * @brief The signal emitted to execute the lookup game operation.
     * @param gameName The name of the game to look up.
     * @see executeLookupGame
    */
    void executeLookupGame(const QString& gameName);

    /**
     * @brief The signal emitted when the lookup game operation is finished.
     * @param result The result of the operation.
     * @see handleLookupGameFinished
    */
    void lookupGameResult(const QList<QMap<QString, QString>>& result);

private slots:
    /**
     * @brief Handles when the lookup game operation finishes.
     * @param result The result of the operation.
    */
    void handleLookupGameFinished(const QList<QMap<QString, QString>>& result);

private:
    /**
     * @brief The worker thread for the API operations.
    */
    QThread* m_workerThread;

    /**
     * @brief The worker object for the API operations.
    */
    GamePileApiWorker* m_worker;
};
