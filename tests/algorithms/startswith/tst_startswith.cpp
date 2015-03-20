// Qt includes
#include <QtTest/QtTest>

// Calibri-Library includes
#include <algorithms/startswith.hpp>

class tst_StartsWith : public QObject
{
    Q_OBJECT

private slots:
    void testStartsWithString();
    void testStartsWithWString();
    void testStartsWithByteArray();
};

void tst_StartsWith::testStartsWithString()
{
    std::string in = "http://test.com/index.html";
    QVERIFY(Calibri::startsWith(in, std::string("http://")));

    in = std::string();
    QVERIFY(!Calibri::startsWith(in, std::string("test")));
}

void tst_StartsWith::testStartsWithWString()
{
    std::wstring in = L"http://test.com/index.html";
    QVERIFY(Calibri::startsWith(in, std::wstring(L"http://")));

    in = std::wstring();
    QVERIFY(!Calibri::startsWith(in, std::wstring(L"test")));
}

void tst_StartsWith::testStartsWithByteArray()
{
    Calibri::ByteArray in = "http://test.com/index.html";
    QVERIFY(Calibri::startsWith(in, Calibri::ByteArray("http://")));

    in = Calibri::ByteArray();
    QVERIFY(!Calibri::startsWith(in, Calibri::ByteArray("test")));
}

QTEST_MAIN(tst_StartsWith)

#include "tst_startswith.moc"
