//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <tools/bytearray.hpp>

class tst_ByteArray : public QObject
{
    Q_OBJECT

private slots:
    void testHex();
    void testBase64();
    void testAppend();
    void testConcatenateOperator();
};

void tst_ByteArray::testHex()
{
    bool ok {};

    auto out = Calibri::ByteArray("Some date").toHex();
    out = Calibri::ByteArray::fromHex(out, &ok);
    QVERIFY(ok);

    QCOMPARE(out, Calibri::ByteArray("Some date"));
}

void tst_ByteArray::testBase64()
{
    bool ok {};

    auto out = Calibri::ByteArray("Some date").toBase64();
    out = Calibri::ByteArray::fromBase64(out, &ok);
    QVERIFY(ok);

    QCOMPARE(out, Calibri::ByteArray("Some date"));
}

void tst_ByteArray::testAppend()
{
    QCOMPARE(Calibri::ByteArray("Some").append(Calibri::ByteArray(" data")), Calibri::ByteArray("Some data"));
    QCOMPARE(Calibri::ByteArray("Some").append(" data", 5), Calibri::ByteArray("Some data"));
    QCOMPARE(Calibri::ByteArray("Some").append(" data"), Calibri::ByteArray("Some data"));
    QCOMPARE(Calibri::ByteArray("Some dat").append('a'), Calibri::ByteArray("Some data"));
    QCOMPARE(Calibri::ByteArray("Some").append({ ' ', 'd', 'a', 't', 'a' }), Calibri::ByteArray("Some data"));
}

void tst_ByteArray::testConcatenateOperator()
{
    Calibri::ByteArray some { "Some" };
    Calibri::ByteArray data { " data" };
    Calibri::ByteArray someDat { "Some dat" };
    Calibri::ByteArray omeData { "ome data" };

    QCOMPARE(some + data, Calibri::ByteArray("Some data"));
    QCOMPARE(Calibri::ByteArray("Some") + Calibri::ByteArray(" data"), Calibri::ByteArray("Some data"));
    QCOMPARE(Calibri::ByteArray("Some") + data, Calibri::ByteArray("Some data"));
    QCOMPARE(some + Calibri::ByteArray(" data"), Calibri::ByteArray("Some data"));

    QCOMPARE(some + " data", Calibri::ByteArray("Some data"));
    QCOMPARE(Calibri::ByteArray("Some") + " data", Calibri::ByteArray("Some data"));
    QCOMPARE("Some" + data, Calibri::ByteArray("Some data"));
    QCOMPARE("Some" + Calibri::ByteArray(" data"), Calibri::ByteArray("Some data"));

    QCOMPARE(someDat + 'a', Calibri::ByteArray("Some data"));
    QCOMPARE(Calibri::ByteArray("Some dat") + 'a', Calibri::ByteArray("Some data"));
    QCOMPARE('S' + omeData, Calibri::ByteArray("Some data"));
    QCOMPARE('S' + Calibri::ByteArray("ome data"), Calibri::ByteArray("Some data"));
}

QTEST_MAIN(tst_ByteArray)

#include "tst_bytearray.moc"
