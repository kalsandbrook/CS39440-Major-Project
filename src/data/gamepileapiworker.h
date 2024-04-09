#pragma once
#include <QObject>
#include <QDebug>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class GamePileApiWorker : public QObject {
    Q_OBJECT
public:
    explicit GamePileApiWorker(QObject* parent = nullptr);

public slots:
    void lookupGame(const QString& gameName);

signals:
    void lookupGameFinished(const QMap<QString, QString>& result);
};
