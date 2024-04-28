#include "gamepileapiworker.h"

GamePileApiWorker::GamePileApiWorker(QObject* parent) : QObject(parent) {}

void GamePileApiWorker::lookupGame(const QString& gameName) {
    QProcess process;
    process.start("GamePile-API", QStringList() << gameName << "-n 5");
    process.waitForFinished();

    QList<QMap<QString, QString>> result;

    if (process.error() != QProcess::UnknownError) {
        qDebug() << "An error occurred with GamePile-API:" << process.errorString();
        emit lookupGameFinished(result);
        return;
    }

    QByteArray output = process.readAllStandardOutput();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(output);
    qDebug() << jsonDoc;
    if (!jsonDoc.isNull() && jsonDoc.isArray()) {
        QJsonArray jsonArray = jsonDoc.array();
        for(const auto& jsonValue : jsonArray){
            if(jsonValue.isObject()){
                auto jsonObject = jsonValue.toObject();
                QMap<QString,QString> gameJson;
                for (auto it = jsonObject.constBegin(); it != jsonObject.constEnd(); ++it) {
                    if (it.value().isString()) {
                        gameJson[it.key()] = it.value().toString();
                    } else if (it.value().isArray()) {
                        QJsonArray array = it.value().toArray();
                        QStringList values;
                        for (const auto& value : array) {
                            if (value.isString()) {
                                values.append(value.toString());
                            }
                        }
                        gameJson[it.key()] = values.join(", ");
                    }
                }
                result.append(gameJson);
            }
        }
        //QJsonObject jsonObject = jsonDoc.object();

    } else {
        qDebug() << "API received malformed JSON.";
    }

    emit lookupGameFinished(result);
}
