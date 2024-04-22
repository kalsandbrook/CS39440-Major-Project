#include <QTest>
#include <QStandardPaths>
#include <QSet>
#include <QDate>
#include "../src/data/gamelibrary.h"
#include "../src/data/game.h"

class TestGameLibrary: public QObject
{
    Q_OBJECT

private:
    GameLibrary* m_gameLibrary;

    bool attributeListsEqual(QStringList a, QStringList b){
        QSet<QString> set1(a.begin(), a.end());
        QSet<QString> set2(b.begin(), b.end());
        auto diff = set2-set1;

        if(diff.isEmpty()){
            return true;
        } else{
            qDebug() << "Difference between lists is" << diff;
            return false;
        }
    }
private slots:

    void initTestCase()
    {
        m_gameLibrary = &GameLibrary::instance();
    }
    void addFullGameTest(){
        Game* testGame = new Game();

        QString name = "Test Game";
        QString desc = "Test Description";
        QStringList genres = {"Foo","Bar"};
        QStringList devs = {"kas143"};
        QStringList pubs = {"Aber Uni", "DCS"};
        QStringList platforms = {"PS4","Windows"};
        QStringList userTags = {"Favourite"};
        QString iconName = "icon.png";
        QString execPath = "/dev/null";
        QDate releaseDate = QDate(1990,01,01);


        testGame->setName(name);
        testGame->setDesc(desc);
        testGame->setGenres(genres);
        testGame->setDevelopers(devs);
        testGame->setPublishers(pubs);
        testGame->setPlatforms(platforms);
        testGame->setUserTags(userTags);
        testGame->setExecPath(execPath);
        testGame->setReleaseDate(releaseDate);
        testGame->setStatus(Game::Status::PLAYING);

        m_gameLibrary->addGame(*testGame);
        Game retrievedGame = m_gameLibrary->games().first();

        QVERIFY(retrievedGame.name() == name);
        QVERIFY(retrievedGame.desc() == desc);
        QVERIFY(attributeListsEqual(retrievedGame.genres(), genres));
        QVERIFY(attributeListsEqual(retrievedGame.developers(), devs));
        QVERIFY(attributeListsEqual(retrievedGame.publishers(), pubs));
        QVERIFY(attributeListsEqual(retrievedGame.platforms(), platforms));
        QVERIFY(attributeListsEqual(retrievedGame.userTags(), userTags));
        QVERIFY(retrievedGame.execPath() == execPath);
        QVERIFY(retrievedGame.releaseDate() == releaseDate);
        QVERIFY(retrievedGame.status() == Game::Status::PLAYING);

        m_gameLibrary->deleteGame(retrievedGame.id());
    }
    void addPartialGameTest()
    {
        Game* testGame = new Game();

        QString name = "Test Game";
        testGame->setName(name);

        QString desc = "Game Description";
        testGame->setDesc(desc);

        QStringList genres = {"Action","Adventure","Indie"};
        testGame->setGenres(genres);

        m_gameLibrary->addGame(*testGame);

        Game retrievedGame = m_gameLibrary->games().first();

        QVERIFY(retrievedGame.name() == name);
        QVERIFY(retrievedGame.desc() == desc);

        QVERIFY(attributeListsEqual(retrievedGame.genres(), genres));

        // Game status should default to NONE.
        QVERIFY(retrievedGame.status() == Game::Status::NONE);
    }

    void updateGameTest()
    {
        // This could be enhanced by testing the updating of ALL fields.
        Game* testGame = new Game();
        testGame->setName("Unupdated name");

        m_gameLibrary->addGame(*testGame);

        int gameId = m_gameLibrary->games().first().id();

        Game* updatedGame = new Game(gameId, "New name","This game has been updated.");
        m_gameLibrary->updateGame(*updatedGame);

        QVERIFY(m_gameLibrary->getGameById(gameId).name() == "New name");
    }

    void deleteGameTest(){
        Game* badGame = new Game(0,"Name","Desc");
        m_gameLibrary->addGame(*badGame);

        int gameId = m_gameLibrary->games().first().id();

        m_gameLibrary->deleteGame(gameId);

        QVERIFY(m_gameLibrary->games().isEmpty());
    }

    void cleanup(){
        // Deletes all games after every test.
        m_gameLibrary->deleteAllGames();
    }

    void cleanupTestCase()
    {
        QDir dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

        dataDir.removeRecursively() ? qDebug() << "Removed test data directory." : qDebug() << "Couldn't remove test data directory.";
    }
};

QTEST_MAIN(TestGameLibrary)

#include "test_gamelibrary.moc"
