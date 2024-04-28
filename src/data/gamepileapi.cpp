#include "gamepileapi.h"

GamePileAPI::GamePileAPI(QObject* parent) : QObject(parent) {
    m_workerThread = new QThread(this);
    m_worker = new GamePileApiWorker;
    m_worker->moveToThread(m_workerThread);

    connect(m_workerThread, &QThread::finished, m_worker, &QObject::deleteLater);
    connect(this, &GamePileAPI::executeLookupGame, m_worker, &GamePileApiWorker::lookupGame);
    connect(m_worker, &GamePileApiWorker::lookupGameFinished, this, &GamePileAPI::handleLookupGameFinished);

    m_workerThread->start();
}

GamePileAPI::~GamePileAPI() {
    m_workerThread->quit();
    m_workerThread->wait();
}

void GamePileAPI::startLookupGame(const QString& gameName) {
    emit executeLookupGame(gameName);
}

void GamePileAPI::handleLookupGameFinished(const QList<QMap<QString, QString>>& result) {
    emit lookupGameResult(result);
}
