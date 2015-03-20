// Qt includes
#include <QtTest/QtTest>

// Calibri-Library includes
#include <algorithms/upper.hpp>

class tst_Upper : public QObject
{
    Q_OBJECT
    
private slots:
    void testToUpperString();
    void testToUpperWString();
    void testToUpperByteArray();
};

void tst_Upper::testToUpperString()
{
    std::string in { "some data" };
    Calibri::upper(in);
    QCOMPARE(in, std::string("SOME DATA"));
}

void tst_Upper::testToUpperWString()
{
    std::wstring in { L"some data" };
    Calibri::upper(in);
    QCOMPARE(in, std::wstring(L"SOME DATA"));
}

void tst_Upper::testToUpperByteArray()
{
    Calibri::ByteArray in { "some data" };
    Calibri::upper(in);
    QCOMPARE(in, Calibri::ByteArray("SOME DATA"));
}

QTEST_MAIN(tst_Upper)

#include "tst_upper.moc"
