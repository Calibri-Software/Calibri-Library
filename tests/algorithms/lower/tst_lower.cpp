//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <algorithms/lower.hpp>

class tst_Lower : public QObject
{
    Q_OBJECT
    
private slots:
    void testToLowerString();
    void testToLowerWString();
    void testToLowerByteArray();
};

void tst_Lower::testToLowerString()
{
    std::string in { "SOME DATA" };
    Calibri::lower(in);
    QCOMPARE(in, std::string("some data"));
}

void tst_Lower::testToLowerWString()
{
    std::wstring in { L"SOME DATA" };
    Calibri::lower(in);
    QCOMPARE(in, std::wstring(L"some data"));
}

void tst_Lower::testToLowerByteArray()
{
    Calibri::ByteArray in { "SOME DATA" };
    Calibri::lower(in);
    QCOMPARE(in, Calibri::ByteArray("some data"));
}

QTEST_MAIN(tst_Lower)

#include "tst_lower.moc"
