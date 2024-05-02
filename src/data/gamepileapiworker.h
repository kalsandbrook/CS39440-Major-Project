#pragma once
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QProcess>

/**
 * @brief A class representing the GamePile API worker.
 * Used to run API operations.
 */
class GamePileApiWorker : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructs a new GamePileApiWorker object.
     * @param parent The parent of the object.
     * @see GamePileAPI
    */
    explicit GamePileApiWorker(QObject* parent = nullptr);

public slots:
    /**
     * @brief Starts the lookup game operation.
     * @param gameName The name of the game to look up.
    */
    void lookupGame(const QString& gameName);

signals:
    /**
     * @brief The signal emitted when the lookup game operation is finished.
     * @param result The result of the operation.
    */
    void lookupGameFinished(const QList<QMap<QString, QString>>& result);
};
