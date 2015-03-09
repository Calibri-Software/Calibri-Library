//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <tools/metacast.hpp>

class tst_MetaCast : public QObject
{
    Q_OBJECT

private slots:
    void testStringToInt8();
    void testStringToUInt8();
    void testStringToInt16();
    void testStringToUInt16();
    void testStringToInt32();
    void testStringToUInt32();
    void testStringToInt64();
    void testStringToUInt64();
    void testStringToFloat();
    void testStringToDouble();
    void testStringToLongDouble();

    void testInt8ToString();
    void testUInt8ToString();
    void testInt16ToString();
    void testUInt16ToString();
    void testInt32ToString();
    void testUInt32ToString();
    void testInt64ToString();
    void testUInt64ToString();
    void testFloatToString();
    void testDoubleToString();
    void testLongDoubleToString();

    void testStringToWString();
    void testWStringToString();
};

void tst_MetaCast::testStringToInt8()
{
    bool ok {};

    auto out = Calibri::metaCast<int8>(std::string("3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::string("-3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(-3));

    out = Calibri::metaCast<decltype(out)>(std::string("33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("-33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(-3));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));
}

void tst_MetaCast::testStringToUInt8()
{
    bool ok {};

    auto out = Calibri::metaCast<uint8>(std::string("3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::string("-3"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));
}

void tst_MetaCast::testStringToInt16()
{
    bool ok {};

    auto out = Calibri::metaCast<int16>(std::string("3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::string("-3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(-3));

    out = Calibri::metaCast<decltype(out)>(std::string("33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("-33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(-3));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));
}

void tst_MetaCast::testStringToUInt16()
{
    bool ok {};

    auto out = Calibri::metaCast<uint16>(std::string("3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::string("-3"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));
}

void tst_MetaCast::testStringToInt32()
{
    bool ok {};

    auto out = Calibri::metaCast<int32>(std::string("3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::string("-3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(-3));

    out = Calibri::metaCast<decltype(out)>(std::string("33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("-33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(-3));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));
}

void tst_MetaCast::testStringToUInt32()
{
    bool ok {};

    auto out = Calibri::metaCast<uint32>(std::string("3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::string("-3"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));
}

void tst_MetaCast::testStringToInt64()
{
    bool ok {};

    auto out = Calibri::metaCast<int64>(std::string("3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::string("-3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(-3));

    out = Calibri::metaCast<decltype(out)>(std::string("33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("-33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(-3));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));
}

void tst_MetaCast::testStringToUInt64()
{
    bool ok {};

    auto out = Calibri::metaCast<uint64>(std::string("3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::string("-3"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::string("Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(3));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"33333333333333333333"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(0));
}

void tst_MetaCast::testStringToFloat()
{
    bool ok {};

    auto out = Calibri::metaCast<float>(std::string("3.03"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, 3.03f);

    out = Calibri::metaCast<decltype(out)>(std::string("-3.03"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, -3.03f);

    out = Calibri::metaCast<decltype(out)>(std::string("3.03e+5000"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0f);

    out = Calibri::metaCast<decltype(out)>(std::string("-3.03e+5000"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0f);

    out = Calibri::metaCast<decltype(out)>(std::string("3.03Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0f);

    out = Calibri::metaCast<decltype(out)>(std::string("Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0f);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3.03"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, 3.03f);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3.03"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, -3.03f);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3.03e+5000"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0f);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3.03e+5000"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0f);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3.03Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0f);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0f);
}

void tst_MetaCast::testStringToDouble()
{
    bool ok {};

    auto out = Calibri::metaCast<double>(std::string("3.03"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, 3.03);

    out = Calibri::metaCast<decltype(out)>(std::string("-3.03"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, -3.03);

    out = Calibri::metaCast<decltype(out)>(std::string("3.03e+5000"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0);

    out = Calibri::metaCast<decltype(out)>(std::string("-3.03e+5000"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0);

    out = Calibri::metaCast<decltype(out)>(std::string("3.03Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0);

    out = Calibri::metaCast<decltype(out)>(std::string("Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3.03"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, 3.03);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3.03"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, -3.03);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3.03e+5000"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3.03e+5000"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3.03Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0);
}

void tst_MetaCast::testStringToLongDouble()
{
    bool ok {};

    auto out = Calibri::metaCast<longdouble>(std::string("3.03"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, 3.03l);

    out = Calibri::metaCast<decltype(out)>(std::string("-3.03"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, -3.03l);

    out = Calibri::metaCast<decltype(out)>(std::string("3.03e+5000"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0l);

    out = Calibri::metaCast<decltype(out)>(std::string("-3.03e+5000"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0l);

    out = Calibri::metaCast<decltype(out)>(std::string("3.03Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0l);

    out = Calibri::metaCast<decltype(out)>(std::string("Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0l);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3.03"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, 3.03l);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3.03"), &ok);
    QVERIFY(ok);
    QCOMPARE(out, -3.03l);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3.03e+5000"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0l);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"-3.03e+5000"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0l);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"3.03Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0l);

    out = Calibri::metaCast<decltype(out)>(std::wstring(L"Some data"), &ok);
    QVERIFY(!ok);
    QCOMPARE(out, 0.0l);
}

void tst_MetaCast::testInt8ToString()
{
    bool ok {};

    int8 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);

    in = -3;

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);
}

void tst_MetaCast::testUInt8ToString()
{
    bool ok {};

    uint8 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);
}

void tst_MetaCast::testInt16ToString()
{
    bool ok {};

    int16 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);

    in = -3;

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);
}

void tst_MetaCast::testUInt16ToString()
{
    bool ok {};

    uint16 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);
}

void tst_MetaCast::testInt32ToString()
{
    bool ok {};

    int32 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);

    in = -3;

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);
}

void tst_MetaCast::testUInt32ToString()
{
    bool ok {};

    uint32 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);
}

void tst_MetaCast::testInt64ToString()
{
    bool ok {};

    int64 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);

    in = -3;

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);
}

void tst_MetaCast::testUInt64ToString()
{
    bool ok {};

    uint64 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);
}

void tst_MetaCast::testFloatToString()
{
    bool ok {};

    float in { 3.03f };

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);

    in = -3.03f;

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);
}

void tst_MetaCast::testDoubleToString()
{
    bool ok {};

    double in { 3.03 };

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);

    in = -3.03;

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);
}

void tst_MetaCast::testLongDoubleToString()
{
    bool ok {};

    longdouble in { 3.03l };

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);

    in = -3.03l;

    QCOMPARE(Calibri::metaCast<std::string>(in, &ok), std::to_string(in));
    QVERIFY(ok);
    QCOMPARE(Calibri::metaCast<std::wstring>(in, &ok), std::to_wstring(in));
    QVERIFY(ok);
}

void tst_MetaCast::testStringToWString()
{
    bool ok {};

    QCOMPARE(Calibri::metaCast<std::wstring>("Some data", &ok), std::wstring(L"Some data"));
    QVERIFY(ok);
}

void tst_MetaCast::testWStringToString()
{
    bool ok {};

    QCOMPARE(Calibri::metaCast<std::string>(L"Some data", &ok), std::string("Some data"));
    QVERIFY(ok);
}

QTEST_MAIN(tst_MetaCast)

#include "tst_metacast.moc"

