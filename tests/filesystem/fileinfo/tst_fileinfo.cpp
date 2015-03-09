//! Qt includes
#include <QtTest/QtTest>
#include <QDir>

//! Calibri-Library includes
#include <filesystem/filesystemengine.hpp>

class tst_FileInfo : public QObject
{
    Q_OBJECT
    
private slots:
    void testAbsoluteFilePath();
    void testAbsolutePath();
    void testFileName();
    void testFileNotFound();
    void testDirectoryFile();
    void testDirectorySymbolicLinkFile();
    void testSymbolicLinkFile();
    void testRegularFile();
    void testSize();
    void testRefresh();
    void cleanupTestCase();
};

void tst_FileInfo::testAbsoluteFilePath()
{
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    QCOMPARE(Calibri::FileInfo("TestFile").absoluteFilePath(), QDir::toNativeSeparators(QFileInfo("TestFile").absoluteFilePath()).toStdString());

    QVERIFY(Calibri::remove("TestFile"));

    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QCOMPARE(Calibri::FileInfo("TestDirectory").absoluteFilePath(), QDir::toNativeSeparators(QFileInfo("TestDirectory").absoluteFilePath()).toStdString());

    QVERIFY(Calibri::remove("TestDirectory"));
}

void tst_FileInfo::testAbsolutePath()
{
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    QCOMPARE(Calibri::FileInfo("TestFile").absolutePath(), QDir::toNativeSeparators(QFileInfo("TestFile").absolutePath()).toStdString());

    QVERIFY(Calibri::remove("TestFile"));

    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QCOMPARE(Calibri::FileInfo("TestDirectory").absolutePath(), QDir::toNativeSeparators(QFileInfo("TestDirectory").absolutePath()).toStdString());

    QVERIFY(Calibri::remove("TestDirectory"));
}

void tst_FileInfo::testFileName()
{
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    QCOMPARE(Calibri::FileInfo("TestFile").fileName(), QDir::toNativeSeparators(QFileInfo("TestFile").fileName()).toStdString());

    QVERIFY(Calibri::remove("TestFile"));

    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QCOMPARE(Calibri::FileInfo("TestDirectory").fileName(), QDir::toNativeSeparators(QFileInfo("TestDirectory").fileName()).toStdString());

    QVERIFY(Calibri::remove("TestDirectory"));
}

void tst_FileInfo::testFileNotFound()
{
    Calibri::FileInfo fileInfo { "TestFile" };
    QVERIFY(!fileInfo.exists());

    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    fileInfo = Calibri::FileInfo("TestFile");
    QVERIFY(fileInfo.exists());

    QVERIFY(Calibri::remove("TestFile"));
}

void tst_FileInfo::testDirectoryFile()
{
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    Calibri::FileInfo fileInfo { "TestFile" };
    QVERIFY(!fileInfo.isDirectory());

    QVERIFY(Calibri::remove("TestFile"));

    QVERIFY(Calibri::createDirectory("TestDirectory"));
    fileInfo = Calibri::FileInfo("TestDirectory");
    QVERIFY(fileInfo.isDirectory());

    QVERIFY(Calibri::remove("TestDirectory"));
}

void tst_FileInfo::testDirectorySymbolicLinkFile()
{
#if !defined(OS_WINDOWS)
    QSKIP("This test requires Windows platform", SkipAll);
#else
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    Calibri::FileInfo fileInfo { "TestFile" };
    QVERIFY(!fileInfo.isDirectorySymbolicLink());

    QVERIFY(Calibri::remove("TestFile"));

    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QVERIFY(Calibri::createSymbolicLink("TestSymbolicLink", "TestDirectory"));
    fileInfo = Calibri::FileInfo("TestSymbolicLink");
    QVERIFY(fileInfo.isDirectorySymbolicLink());

    QVERIFY(Calibri::remove("TestSymbolicLink"));
    QVERIFY(Calibri::remove("TestDirectory"));
#endif
}

void tst_FileInfo::testSymbolicLinkFile()
{
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    Calibri::FileInfo fileInfo { "TestFile" };
    QVERIFY(!fileInfo.isSymbolicLink());

    QVERIFY(Calibri::createSymbolicLink("TestSymbolicLink", "TestFile"));
    fileInfo = Calibri::FileInfo("TestSymbolicLink");
    QVERIFY(fileInfo.isSymbolicLink());

    QVERIFY(Calibri::remove("TestSymbolicLink"));
    QVERIFY(Calibri::remove("TestFile"));
}

void tst_FileInfo::testRegularFile()
{
    QVERIFY(Calibri::createDirectory("TestDirectory"));
    Calibri::FileInfo fileInfo { "TestDirectory" };
    QVERIFY(!fileInfo.isRegularFile());

    QVERIFY(Calibri::remove("TestDirectory"));

    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    fileInfo = Calibri::FileInfo("TestFile");
    QVERIFY(fileInfo.isRegularFile());

    QVERIFY(Calibri::remove("TestFile"));
}

void tst_FileInfo::testSize()
{
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    Calibri::FileInfo fileInfo { "TestFile" };
    QCOMPARE(fileInfo.size(), Calibri::metaCast<sizeinfo>(0));

    QVERIFY(file.resize(1024));

    fileInfo.refresh();
    QCOMPARE(fileInfo.size(), Calibri::metaCast<sizeinfo>(1024));

    QVERIFY(Calibri::createSymbolicLink("TestSymbolicLink", "TestFile"));
    fileInfo = Calibri::FileInfo("TestSymbolicLink");
    QCOMPARE(fileInfo.size(), Calibri::metaCast<sizeinfo>(0));

    QVERIFY(Calibri::remove("TestSymbolicLink"));
    QVERIFY(Calibri::remove("TestFile"));

    QVERIFY(Calibri::createDirectory("TestDirectory"));
    fileInfo = Calibri::FileInfo("TestDirectory");
    QCOMPARE(fileInfo.size(), Calibri::metaCast<sizeinfo>(0));

    QVERIFY(Calibri::remove("TestDirectory"));
}

void tst_FileInfo::testRefresh()
{
    bool ok {};

    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    Calibri::FileInfo fileInfo { "TestFile" };
    QCOMPARE(fileInfo.size(), Calibri::metaCast<sizeinfo>(0));

    QVERIFY(file.resize(1024));

    auto currentDirectory = Calibri::currentDirectory(&ok);
    QVERIFY(ok);
    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QVERIFY(Calibri::setCurrentDirectory("TestDirectory"));

    fileInfo.refresh();
    QCOMPARE(fileInfo.size(), Calibri::metaCast<sizeinfo>(1024));

    QVERIFY(Calibri::setCurrentDirectory(currentDirectory));
    QVERIFY(Calibri::remove("TestFile"));
    QVERIFY(Calibri::remove("TestDirectory"));
}

void tst_FileInfo::cleanupTestCase()
{
    if (QFile::exists("TestSymbolicLink"))
        QFile::remove("TestSymbolicLink");

    auto testDirectory = QDir("TestDirectory");

    if (testDirectory.exists())
        testDirectory.removeRecursively();

    if (QFile::exists("TestFile"))
        QFile::remove("TestFile");
}

QTEST_MAIN(tst_FileInfo)

#include "tst_fileinfo.moc"
