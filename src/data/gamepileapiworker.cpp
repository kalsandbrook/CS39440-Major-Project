#include "gamepileapiworker.h"

GamePileApiWorker::GamePileApiWorker(QObject* parent) : QObject(parent) {}

void GamePileApiWorker::lookupGame(const QString& gameName) {
    QProcess process;
    process.start("GamePile-API", QStringList() << gameName);
    process.waitForFinished();

    QMap<QString, QString> result;

    if (process.error() != QProcess::UnknownError) {
        qDebug() << "An error occurred with GamePile-API:" << process.errorString();
        emit lookupGameFinished(result);
        return;
    }

    QByteArray output = process.readAllStandardOutput();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(output);
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        QJsonObject jsonObject = jsonDoc.object();
        for (auto it = jsonObject.constBegin(); it != jsonObject.constEnd(); ++it) {
            if (it.value().isString()) {
                result[it.key()] = it.value().toString();
            } else if (it.value().isArray()) {
                QJsonArray array = it.value().toArray();
                QStringList values;
                for (const auto& value : array) {
                    if (value.isString()) {
                        values.append(value.toString());
                    }
                }
                result[it.key()] = values.join(", ");
            }
        }
    } else {
        qDebug() << "API received malformed JSON.";
    }

    emit lookupGameFinished(result);
}
