//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <algorithms/anyof.hpp>

class tst_AnyOf : public QObject
{
    Q_OBJECT
    
private slots:
    void testAnyOfString();
    void testAnyOfWString();
    void testAnyOfByteArray();
};

void tst_AnyOf::testAnyOfString()
{
    std::string in { "1 some data" };
    QVERIFY(std::any_of(std::begin(in), std::end(in), Calibri::anyOf(std::string("123"))));
    QVERIFY(Calibri::anyOf(in, std::string("123")));

    in = std::string("some 2 data");
    QVERIFY(std::any_of(std::begin(in), std::end(in), Calibri::anyOf(std::string("123"))));
    QVERIFY(Calibri::anyOf(in, std::string("123")));

    in = std::string("some data 3");
    QVERIFY(std::any_of(std::begin(in), std::end(in), Calibri::anyOf(std::string("123"))));
    QVERIFY(Calibri::anyOf(in, std::string("123")));
}

void tst_AnyOf::testAnyOfWString()
{
    std::wstring in { L"1 some data" };
    QVERIFY(std::any_of(std::begin(in), std::end(in), Calibri::anyOf(std::wstring(L"123"))));
    QVERIFY(Calibri::anyOf(in, std::wstring(L"123")));

    in = std::wstring(L"some 2 data");
    QVERIFY(std::any_of(std::begin(in), std::end(in), Calibri::anyOf(std::wstring(L"123"))));
    QVERIFY(Calibri::anyOf(in, std::wstring(L"123")));

    in = std::wstring(L"some data 3");
    QVERIFY(std::any_of(std::begin(in), std::end(in), Calibri::anyOf(std::wstring(L"123"))));
    QVERIFY(Calibri::anyOf(in, std::wstring(L"123")));
}

void tst_AnyOf::testAnyOfByteArray()
{
    Calibri::ByteArray in { "1 some data" };
    QVERIFY(std::any_of(std::begin(in), std::end(in), Calibri::anyOf(Calibri::ByteArray("123"))));
    QVERIFY(Calibri::anyOf(in, Calibri::ByteArray("123")));

    in = Calibri::ByteArray("some 2 data");
    QVERIFY(std::any_of(std::begin(in), std::end(in), Calibri::anyOf(Calibri::ByteArray("123"))));
    QVERIFY(Calibri::anyOf(in, Calibri::ByteArray("123")));

    in = Calibri::ByteArray("some data 3");
    QVERIFY(std::any_of(std::begin(in), std::end(in), Calibri::anyOf(Calibri::ByteArray("123"))));
    QVERIFY(Calibri::anyOf(in, Calibri::ByteArray("123")));
}

QTEST_MAIN(tst_AnyOf)

#include "tst_anyof.moc"
