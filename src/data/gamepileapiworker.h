#pragma once
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QProcess>

class GamePileApiWorker : public QObject {
    Q_OBJECT
public:
    explicit GamePileApiWorker(QObject* parent = nullptr);

public slots:
    void lookupGame(const QString& gameName);

signals:
    void lookupGameFinished(const QMap<QString, QString>& result);
};
