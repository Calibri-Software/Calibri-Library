//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <algorithms/trim.hpp>

class tst_Trim : public QObject
{
    Q_OBJECT
    
private slots:
    void testTrimString();
    void testTrimWString();
    void testTrimByteArray();
};

void tst_Trim::testTrimString()
{
    std::string in { " \t\r\nsome data   " };
    Calibri::trim(in);
    QCOMPARE(in, std::string("some data"));

    in = { "\t \n \r\n " };
    Calibri::trim(in);
    QCOMPARE(in, std::string());

    in = { "Some data" };
    Calibri::trim(in);
    QCOMPARE(in, std::string("Some data"));

    in = { "" };
    Calibri::trim(in);
    QCOMPARE(in, std::string());
}

void tst_Trim::testTrimWString()
{
    std::wstring in { L" \t\r\nsome data   " };
    Calibri::trim(in);
    QCOMPARE(in, std::wstring(L"some data"));

    in = { L"\t \n \r\n " };
    Calibri::trim(in);
    QCOMPARE(in, std::wstring());

    in = { L"Some data" };
    Calibri::trim(in);
    QCOMPARE(in, std::wstring(L"Some data"));

    in = { L"" };
    Calibri::trim(in);
    QCOMPARE(in, std::wstring());
}

void tst_Trim::testTrimByteArray()
{
    Calibri::ByteArray in { " \t\r\nsome data   " };
    Calibri::trim(in);
    QCOMPARE(in, Calibri::ByteArray("some data"));

    in = { "\t \n \r\n " };
    Calibri::trim(in);
    QCOMPARE(in, Calibri::ByteArray());

    in = { "Some data" };
    Calibri::trim(in);
    QCOMPARE(in, Calibri::ByteArray("Some data"));

    in = { "" };
    Calibri::trim(in);
    QCOMPARE(in, Calibri::ByteArray());
}

QTEST_MAIN(tst_Trim)

#include "tst_trim.moc"
