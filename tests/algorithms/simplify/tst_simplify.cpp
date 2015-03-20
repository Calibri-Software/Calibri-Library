// Qt includes
#include <QtTest/QtTest>

// Calibri-Library includes
#include <algorithms/simplify.hpp>

class tst_Simplify : public QObject
{
    Q_OBJECT

private slots:
    void testSimplifyString();
    void testSimplifyWString();
    void testSimplifyByteArray();
};

void tst_Simplify::testSimplifyString()
{
    std::string in { " \t\r\nsome data, some \r\ndata\n2\t  " };
    Calibri::simplify(in);
    QCOMPARE(in, std::string("some data, some data 2"));

    in = { "\t \n \r\n " };
    Calibri::simplify(in);
    QCOMPARE(in, std::string());

    in = { "Some data" };
    Calibri::simplify(in);
    QCOMPARE(in, std::string("Some data"));

    in = { "" };
    Calibri::simplify(in);
    QCOMPARE(in, std::string());
}

void tst_Simplify::testSimplifyWString()
{
    std::wstring in { L" \t\r\nsome data, some \r\ndata\n2\t  " };
    Calibri::simplify(in);
    QCOMPARE(in, std::wstring(L"some data, some data 2"));

    in = { L"\t \n \r\n " };
    Calibri::simplify(in);
    QCOMPARE(in, std::wstring());

    in = { L"Some data" };
    Calibri::simplify(in);
    QCOMPARE(in, std::wstring(L"Some data"));

    in = { L"" };
    Calibri::simplify(in);
    QCOMPARE(in, std::wstring());
}

void tst_Simplify::testSimplifyByteArray()
{
    Calibri::ByteArray in { " \t\r\nsome data, some \r\ndata\n2\t  " };
    Calibri::simplify(in);
    QCOMPARE(in, Calibri::ByteArray("some data, some data 2"));

    in = { "\t \n \r\n " };
    Calibri::simplify(in);
    QCOMPARE(in, Calibri::ByteArray());

    in = { "Some data" };
    Calibri::simplify(in);
    QCOMPARE(in, Calibri::ByteArray("Some data"));

    in = { "" };
    Calibri::simplify(in);
    QCOMPARE(in, Calibri::ByteArray());
}

QTEST_MAIN(tst_Simplify)

#include "tst_simplify.moc"
