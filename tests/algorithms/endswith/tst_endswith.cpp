//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <algorithms/endswith.hpp>

class tst_EndsWith : public QObject
{
    Q_OBJECT
    
private slots:
    void testEndsWithString();
    void testEndsWithWString();
    void testEndsWithByteArray();
};

void tst_EndsWith::testEndsWithString()
{
    std::string in = "http://test.com/index.html";
    QVERIFY(Calibri::endsWith(in, std::string(".html")));

    in = std::string();
    QVERIFY(!Calibri::endsWith(in, std::string("test")));
}

void tst_EndsWith::testEndsWithWString()
{
    std::wstring in = L"http://test.com/index.html";
    QVERIFY(Calibri::endsWith(in, std::wstring(L".html")));

    in = std::wstring();
    QVERIFY(!Calibri::endsWith(in, std::wstring(L"test")));
}

void tst_EndsWith::testEndsWithByteArray()
{
    Calibri::ByteArray in = "http://test.com/index.html";
    QVERIFY(Calibri::endsWith(in, Calibri::ByteArray(".html")));

    in = Calibri::ByteArray();
    QVERIFY(!Calibri::endsWith(in, Calibri::ByteArray("test")));
}

QTEST_MAIN(tst_EndsWith)

#include "tst_endswith.moc"
