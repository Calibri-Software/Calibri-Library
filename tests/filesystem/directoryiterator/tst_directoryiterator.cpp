// Qt includes
#include <QtTest/QtTest>
#include <QDir>

// Calibri-Library includes
#include <filesystem/filesystemengine.hpp>
#include <filesystem/directoryiterator.hpp>

class tst_DirectoryIterator : public QObject
{
    Q_OBJECT
    
private slots:
    void testHasNext();
    void testNext();
    void cleanupTestCase();
};

void tst_DirectoryIterator::testHasNext()
{
    Calibri::DirectoryIterator it { "" };
    QVERIFY(!it.hasNext());

    Calibri::DirectoryIterator it2 { "TestDirectory" };
    QVERIFY(!it2.hasNext());

    QVERIFY(Calibri::createDirectory("TestDirectory"));
    Calibri::DirectoryIterator it3 { "TestDirectory" };
    QVERIFY(it3.hasNext());
    it3.next();
    QVERIFY(it3.hasNext());
    it3.next();
    QVERIFY(!it3.hasNext());

    QVERIFY(Calibri::createDirectories("TestDirectory/TestDirectory2"));
    Calibri::DirectoryIterator it4 { "TestDirectory" };
    QVERIFY(it4.hasNext());
    it4.next();
    QVERIFY(it4.hasNext());
    it4.next();
    QVERIFY(it4.hasNext());
    it4.next();
    QVERIFY(!it4.hasNext());

    QCOMPARE(Calibri::removeAll("TestDirectory"), Calibri::metaCast<uint32>(2));
}

void tst_DirectoryIterator::testNext()
{
    std::vector<std::string> directories { std::initializer_list<std::string>({ ".", ".." }) };
    std::string out {};

    Calibri::DirectoryIterator it { "" };
    QVERIFY(!it.hasNext());
    QCOMPARE(it.next(), std::string());

    Calibri::DirectoryIterator it2 { "TestDirectory" };
    QVERIFY(!it2.hasNext());
    QCOMPARE(it2.next(), std::string());

    QVERIFY(Calibri::createDirectory("TestDirectory"));
    Calibri::DirectoryIterator it3 { "TestDirectory" };
    QVERIFY(it3.hasNext());
    out = it3.next();
    QVERIFY(std::any_of(std::begin(directories), std::end(directories), [ &out ](const std::string &entry) {
        return out == entry;
    }));
    QVERIFY(it3.hasNext());
    out = it3.next();
    QVERIFY(std::any_of(std::begin(directories), std::end(directories), [ &out ](const std::string &entry) {
        return out == entry;
    }));
    QVERIFY(!it3.hasNext());
    QCOMPARE(it3.next(), std::string());

    directories = std::vector<std::string>(std::initializer_list<std::string>({ ".", "..", "TestDirectory2", "TestDirectory3" }));
    QVERIFY(Calibri::createDirectories("TestDirectory/TestDirectory2"));
    QVERIFY(Calibri::createDirectories("TestDirectory/TestDirectory3"));
    Calibri::DirectoryIterator it4 { "TestDirectory" };
    QVERIFY(it4.hasNext());
    out = it4.next();
    QVERIFY(std::any_of(std::begin(directories), std::end(directories), [ &out ](const std::string &entry) {
        return out == entry;
    }));
    QVERIFY(it4.hasNext());
    out = it4.next();
    QVERIFY(std::any_of(std::begin(directories), std::end(directories), [ &out ](const std::string &entry) {
        return out == entry;
    }));
    QVERIFY(it4.hasNext());
    out = it4.next();
    QVERIFY(std::any_of(std::begin(directories), std::end(directories), [ &out ](const std::string &entry) {
        return out == entry;
    }));
    QVERIFY(it4.hasNext());
    out = it4.next();
    QVERIFY(std::any_of(std::begin(directories), std::end(directories), [ &out ](const std::string &entry) {
        return out == entry;
    }));
    QVERIFY(!it4.hasNext());
    QCOMPARE(it4.next(), std::string());

    QCOMPARE(Calibri::removeAll("TestDirectory"), Calibri::metaCast<uint32>(3));
}

void tst_DirectoryIterator::cleanupTestCase()
{
    auto testDirectory = QDir("TestDirectory");

    if (testDirectory.exists())
        testDirectory.removeRecursively();
}

QTEST_MAIN(tst_DirectoryIterator)

#include "tst_directoryiterator.moc"
