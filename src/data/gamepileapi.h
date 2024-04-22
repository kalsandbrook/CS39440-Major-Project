#pragma once

#include "gamepileapiworker.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QProcess>
#include <QThread>

class GamePileAPI : public QObject {
    Q_OBJECT
public:
    explicit GamePileAPI(QObject* parent = nullptr);
    ~GamePileAPI();

    void startLookupGame(const QString& gameName);

signals:
    void executeLookupGame(const QString& gameName);
    void lookupGameResult(const QMap<QString, QString>& result);

private slots:
    void handleLookupGameFinished(const QMap<QString, QString>& result);

private:
    QThread* m_workerThread;
    GamePileApiWorker* m_worker;
};
