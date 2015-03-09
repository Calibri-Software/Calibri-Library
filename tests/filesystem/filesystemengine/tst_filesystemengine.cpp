//! Qt includes
#include <QtTest/QtTest>
#include <QDir>

//! Calibri-Library includes
#include <filesystem/filesystemengine.hpp>
#include <tools/metacast.hpp>

class tst_FileSystemEngine : public QObject
{
    Q_OBJECT
    
private slots:
    void testToNativeSeparator();
    void testSetCurrentDirectory();
    void testCurrentDirectory();
    void testCreateDirectory();
    void testCreateDirectories();
    void testRemoveDirectory();
    void testCreateSymbolicLink();
    void testReadSymbolicLink();
    void testResizeFile();
    void testRemoveFile();
    void testRemove();
    void testRemoveAll();
    void testRename();
    void testCopySymbolicLink();
    void testCopyDirectory();
    void testCopyFile();
    void testCopy();
    void cleanupTestCase();
};

void tst_FileSystemEngine::testToNativeSeparator()
{
#if defined(OS_WINDOWS)
    std::string in { "C:/test/path" };
#elif defined(OS_LINUX) || defined(OS_UNIX)
    std::string in { "\\test\\path" };
#endif

    Calibri::toNativeSeparator(in);
#if defined(OS_WINDOWS)
    QCOMPARE(in, std::string("C:\\test\\path"));
#elif defined(OS_LINUX) || defined(OS_UNIX)
    QCOMPARE(in, std::string("/test/path"));
#endif
}

void tst_FileSystemEngine::testSetCurrentDirectory()
{
    bool ok {};

    auto currentDirectory = Calibri::currentDirectory(&ok);
    QVERIFY(ok);
    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QVERIFY(Calibri::setCurrentDirectory("TestDirectory"));
    QVERIFY(!Calibri::setCurrentDirectory("TestDirectory"));
    QCOMPARE(currentDirectory + Calibri::nativeSeparator() + "TestDirectory", Calibri::currentDirectory());
    QVERIFY(Calibri::setCurrentDirectory(currentDirectory));

    QVERIFY(Calibri::remove("TestDirectory"));
}

void tst_FileSystemEngine::testCurrentDirectory()
{
    bool ok {};

    auto out = Calibri::currentDirectory(&ok);
    auto check = QDir::currentPath().toStdString();
    Calibri::toNativeSeparator(check);
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_FileSystemEngine::testCreateDirectory()
{
    QVERIFY(Calibri::createDirectory(Calibri::currentDirectory() + Calibri::nativeSeparator() + "TestDirectory"));
    QVERIFY(!Calibri::createDirectory(Calibri::currentDirectory() + Calibri::nativeSeparator() + "TestDirectory"));

    QVERIFY(Calibri::remove("TestDirectory"));

    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QVERIFY(!Calibri::createDirectory("TestDirectory"));

    QVERIFY(Calibri::remove("TestDirectory"));
}

void tst_FileSystemEngine::testCreateDirectories()
{
    QVERIFY(Calibri::createDirectories("TestDirectory/TestDirectory2/TestDirectory3"));
    QVERIFY(Calibri::createDirectories("TestDirectory/TestDirectory2/TestDirectory3"));

    QCOMPARE(Calibri::removeAll("TestDirectory"), Calibri::metaCast<uint32>(3));
}

void tst_FileSystemEngine::testRemoveDirectory()
{
    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QVERIFY(Calibri::removeDirectory(Calibri::currentDirectory() + Calibri::nativeSeparator() + "TestDirectory"));
    QVERIFY(!Calibri::removeDirectory(Calibri::currentDirectory() + Calibri::nativeSeparator() + "TestDirectory"));

    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QVERIFY(Calibri::removeDirectory("TestDirectory"));
    QVERIFY(!Calibri::removeDirectory("TestDirectory"));
}

void tst_FileSystemEngine::testCreateSymbolicLink()
{
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    QVERIFY(Calibri::createSymbolicLink("TestSymbolicLink", file.fileName().toStdString()));
    QVERIFY(!Calibri::createSymbolicLink("TestSymbolicLink", file.fileName().toStdString()));
    Calibri::FileInfo fileInfo { "TestSymbolicLink" };
    QVERIFY(fileInfo.isSymbolicLink());

    QVERIFY(Calibri::remove("TestSymbolicLink"));
    QVERIFY(Calibri::remove("TestFile"));

    Calibri::createDirectory("TestDirectory");
    QVERIFY(Calibri::createSymbolicLink("TestSymbolicLink", "TestDirectory"));
    fileInfo = Calibri::FileInfo("TestSymbolicLink");
#if defined(OS_WINDOWS)
    QVERIFY(fileInfo.isDirectorySymbolicLink());
#elif defined(OS_LINUX) || defined(OS_UNIX)
    QVERIFY(fileInfo.isSymbolicLink());
#endif

    QVERIFY(Calibri::remove("TestSymbolicLink"));
    QVERIFY(Calibri::remove("TestDirectory"));
}

void tst_FileSystemEngine::testReadSymbolicLink()
{
    bool ok {};

    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    QVERIFY(Calibri::createSymbolicLink("TestSymbolicLink", file.fileName().toStdString()));
    auto out = Calibri::readSymbolicLink("TestSymbolicLink", &ok);
    QVERIFY(ok);
    QCOMPARE(out, QFileInfo(QFile::symLinkTarget("TestSymbolicLink")).fileName().toStdString());

    QVERIFY(Calibri::remove("TestSymbolicLink"));
    QVERIFY(Calibri::remove("TestFile"));

    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QVERIFY(Calibri::createSymbolicLink("TestSymbolicLink", "TestDirectory"));
    out = Calibri::readSymbolicLink("TestSymbolicLink", &ok);
    QVERIFY(ok);
    QCOMPARE(out, QFileInfo(QFile::symLinkTarget("TestSymbolicLink")).fileName().toStdString());

    QVERIFY(Calibri::remove("TestSymbolicLink"));
    QVERIFY(Calibri::remove("TestDirectory"));
}

void tst_FileSystemEngine::testResizeFile()
{
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    QVERIFY(Calibri::resizeFile("TestFile", 1024));
    QCOMPARE(Calibri::FileInfo("TestFile").size(), Calibri::metaCast<sizeinfo>(1024));

    QVERIFY(Calibri::resizeFile("TestFile", 0));
    QCOMPARE(Calibri::FileInfo("TestFile").size(), Calibri::metaCast<sizeinfo>(0));

    QVERIFY(Calibri::remove("TestFile"));
}

void tst_FileSystemEngine::testRemoveFile()
{
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    QVERIFY(Calibri::removeFile(file.fileName().toStdString()));
    QVERIFY(!Calibri::removeFile(file.fileName().toStdString()));
}

void tst_FileSystemEngine::testRemove()
{
    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QVERIFY(Calibri::remove("TestDirectory"));
    QVERIFY(!Calibri::remove("TestDirectory"));

    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    QVERIFY(Calibri::remove("TestFile"));
    QVERIFY(!Calibri::remove("TestFile"));
}

void tst_FileSystemEngine::testRemoveAll()
{
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    QVERIFY(Calibri::createDirectories("TestDirectory/TestDirectory2"));
    QVERIFY(Calibri::createDirectories("TestDirectory/TestDirectory3"));
    QVERIFY(Calibri::createSymbolicLink("TestDirectory/TestSymbolicLink", "TestFile"));
    QVERIFY(Calibri::createSymbolicLink("TestDirectory/TestDirectory2/TestSymbolicLink", "TestFile"));
    QVERIFY(Calibri::createSymbolicLink("TestDirectory/TestDirectory3/TestSymbolicLink", "TestFile"));
    QCOMPARE(Calibri::removeAll("TestDirectory"), Calibri::metaCast<uint32>(6));
    QCOMPARE(Calibri::removeAll("TestFile"), Calibri::metaCast<uint32>(1));
}

void tst_FileSystemEngine::testRename()
{
    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QVERIFY(Calibri::rename("TestDirectory", "TestDirectoryNew"));
    QVERIFY(!Calibri::rename("TestDirectory", "TestDirectoryNew"));

    QVERIFY(!Calibri::remove("TestDirectory"));
    QVERIFY(Calibri::remove("TestDirectoryNew"));

    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    QVERIFY(Calibri::rename("TestFile", "TestFileNew"));
    QVERIFY(!Calibri::rename("TestFile", "TestFileNew"));

    QVERIFY(!Calibri::remove("TestFile"));
    QVERIFY(Calibri::remove("TestFileNew"));
}

void tst_FileSystemEngine::testCopySymbolicLink()
{
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    QVERIFY(Calibri::createSymbolicLink("TestSymbolicLink", "TestFile"));
    QVERIFY(Calibri::copySymbolicLink("TestSymbolicLink", "TestSymbolicLinkNew"));
    QCOMPARE(Calibri::readSymbolicLink("TestSymbolicLink"), Calibri::readSymbolicLink("TestSymbolicLinkNew"));
    QCOMPARE(Calibri::readSymbolicLink("TestSymbolicLinkNew"), std::string("TestFile"));

    QVERIFY(Calibri::remove("TestSymbolicLinkNew"));
    QVERIFY(Calibri::remove("TestSymbolicLink"));
    QVERIFY(Calibri::remove("TestFile"));
}

void tst_FileSystemEngine::testCopyDirectory()
{
    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QVERIFY(Calibri::copyDirectory("TestDirectory", "TestDirectoryNew"));

    QVERIFY(Calibri::remove("TestDirectoryNew"));
    QVERIFY(Calibri::remove("TestDirectory"));
}

void tst_FileSystemEngine::testCopyFile()
{
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    for (auto i = 0; i < 30000; ++i)
        file.write(QByteArray("Some data!"));
    file.flush();
    file.close();
    QVERIFY(Calibri::copyFile("TestFile", "TestFileNew"));
    QCOMPARE(Calibri::FileInfo("TestFile").size(), Calibri::FileInfo("TestFileNew").size());
    QVERIFY(!Calibri::copyFile("TestFile", "TestFileNew"));
    QVERIFY(Calibri::copyFile("TestFile", "TestFileNew", false));

    QVERIFY(Calibri::remove("TestFile"));
    QVERIFY(Calibri::remove("TestFileNew"));
}

void tst_FileSystemEngine::testCopy()
{
    QFile file("TestFile");
    QVERIFY(file.open(QIODevice::ReadWrite));
    file.close();
    QVERIFY(Calibri::createSymbolicLink("TestSymbolicLink", "TestFile"));
    QVERIFY(Calibri::copy("TestSymbolicLink", "TestSymbolicLinkNew"));
    QCOMPARE(Calibri::readSymbolicLink("TestSymbolicLink"), Calibri::readSymbolicLink("TestSymbolicLinkNew"));
    QCOMPARE(Calibri::readSymbolicLink("TestSymbolicLinkNew"), std::string("TestFile"));

    QVERIFY(Calibri::remove("TestSymbolicLinkNew"));
    QVERIFY(Calibri::remove("TestSymbolicLink"));
    QVERIFY(Calibri::remove("TestFile"));

    QVERIFY(Calibri::createDirectory("TestDirectory"));
    QVERIFY(Calibri::copyDirectory("TestDirectory", "TestDirectoryNew"));

    QVERIFY(Calibri::remove("TestDirectoryNew"));
    QVERIFY(Calibri::remove("TestDirectory"));

    QVERIFY(file.open(QIODevice::ReadWrite));
    for (auto i = 0; i < 30000; ++i)
        file.write(QByteArray("Some data!"));
    file.flush();
    file.close();
    QVERIFY(Calibri::copyFile("TestFile", "TestFileNew"));
    QCOMPARE(Calibri::FileInfo("TestFile").size(), Calibri::FileInfo("TestFileNew").size());
    QVERIFY(!Calibri::copyFile("TestFile", "TestFileNew"));
    QVERIFY(Calibri::copyFile("TestFile", "TestFileNew", false));

    QVERIFY(Calibri::remove("TestFile"));
    QVERIFY(Calibri::remove("TestFileNew"));
}

void tst_FileSystemEngine::cleanupTestCase()
{
    if (QFile::exists("TestSymbolicLink"))
        QFile::remove("TestSymbolicLink");

    if (QFile::exists("TestSymbolicLinkNew"))
        QFile::remove("TestSymbolicLinkNew");

    auto testDirectory = QDir("TestDirectory");

    if (testDirectory.exists())
        testDirectory.removeRecursively();

    auto testDirectoryNew = QDir("TestDirectoryNew");

    if (testDirectoryNew.exists())
        testDirectoryNew.removeRecursively();

    if (QFile::exists("TestFile"))
        QFile::remove("TestFile");

    if (QFile::exists("TestFileNew"))
        QFile::remove("TestFileNew");
}

QTEST_MAIN(tst_FileSystemEngine)

#include "tst_filesystemengine.moc"
