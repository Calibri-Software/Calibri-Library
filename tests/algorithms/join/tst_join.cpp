// Qt includes
#include <QtTest/QtTest>

// Calibri-Library includes
#include <algorithms/join.hpp>

class tst_Join : public QObject
{
    Q_OBJECT

private slots:
    void testJoinVectorToString();
    void testJoinVectorToWString();
    void testJoinVectorToByteArray();
    void testJoinDequeToString();
    void testJoinDequeToWString();
    void testJoinDequeToByteArray();
    void testJoinForwardListToString();
    void testJoinForwardListToWString();
    void testJoinForwardListToByteArray();
    void testJoinListToString();
    void testJoinListToWString();
    void testJoinListToByteArray();
};

void tst_Join::testJoinVectorToString()
{
    std::string out {};
    decltype(out) check { "Some data" };

    std::vector<std::string> in { std::string("Some"), std::string("dummy"), std::string("data") };
    Calibri::join(out, in, std::string(" "), [](const std::string &data) noexcept { return data != std::string("dummy"); });
    QCOMPARE(out, check);

    in = { std::string("Some"), std::string("data") };
    Calibri::join(out, in, std::string(" "));
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    Calibri::join(out, in, std::string(" "));
    QCOMPARE(out, check);
}

void tst_Join::testJoinVectorToWString()
{
    std::wstring out {};
    decltype(out) check { L"Some data" };

    std::vector<std::wstring> in { std::wstring(L"Some"), std::wstring(L"dummy"), std::wstring(L"data") };
    Calibri::join(out, in, std::wstring(L" "), [](const std::wstring &data) noexcept { return data != std::wstring(L"dummy"); });
    QCOMPARE(out, check);

    in = { std::wstring(L"Some"), std::wstring(L"data") };
    Calibri::join(out, in, std::wstring(L" "));
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    Calibri::join(out, in, std::wstring(L" "));
    QCOMPARE(out, check);
}

void tst_Join::testJoinVectorToByteArray()
{
    Calibri::ByteArray out {};
    decltype(out) check { "Some data" };

    std::vector<Calibri::ByteArray> in { Calibri::ByteArray("Some"), Calibri::ByteArray("dummy"), Calibri::ByteArray("data") };
    Calibri::join(out, in, Calibri::ByteArray(" "), [](const Calibri::ByteArray &data) noexcept { return data != Calibri::ByteArray("dummy"); });
    QCOMPARE(out, check);

    in = { "Some", "data" };
    Calibri::join(out, in, Calibri::ByteArray(" "));
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    Calibri::join(out, in, Calibri::ByteArray(" "));
    QCOMPARE(out, check);
}

void tst_Join::testJoinDequeToString()
{
    std::string out {};
    decltype(out) check { "Some data" };

    std::deque<std::string> in { std::string("Some"), std::string("dummy"), std::string("data") };
    Calibri::join(out, in, std::string(" "), [](const std::string &data) noexcept { return data != std::string("dummy"); });
    QCOMPARE(out, check);

    in = { std::string("Some"), std::string("data") };
    Calibri::join(out, in, std::string(" "));
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    Calibri::join(out, in, std::string(" "));
    QCOMPARE(out, check);
}

void tst_Join::testJoinDequeToWString()
{
    std::wstring out {};
    decltype(out) check { L"Some data" };

    std::deque<std::wstring> in { std::wstring(L"Some"), std::wstring(L"dummy"), std::wstring(L"data") };
    Calibri::join(out, in, std::wstring(L" "), [](const std::wstring &data) noexcept { return data != std::wstring(L"dummy"); });
    QCOMPARE(out, check);

    in = { std::wstring(L"Some"), std::wstring(L"data") };
    Calibri::join(out, in, std::wstring(L" "));
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    Calibri::join(out, in, std::wstring(L" "));
    QCOMPARE(out, check);
}

void tst_Join::testJoinDequeToByteArray()
{
    Calibri::ByteArray out {};
    decltype(out) check { "Some data" };

    std::deque<Calibri::ByteArray> in { Calibri::ByteArray("Some"), Calibri::ByteArray("dummy"), Calibri::ByteArray("data") };
    Calibri::join(out, in, Calibri::ByteArray(" "), [](const Calibri::ByteArray &data) noexcept { return data != Calibri::ByteArray("dummy"); });
    QCOMPARE(out, check);

    in = { "Some", "data" };
    Calibri::join(out, in, Calibri::ByteArray(" "));
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    Calibri::join(out, in, Calibri::ByteArray(" "));
    QCOMPARE(out, check);
}

void tst_Join::testJoinForwardListToString()
{
    std::string out {};
    decltype(out) check { "Some data" };

    std::forward_list<std::string> in { std::string("Some"), std::string("dummy"), std::string("data") };
    Calibri::join(out, in, std::string(" "), [](const std::string &data) noexcept { return data != std::string("dummy"); });
    QCOMPARE(out, check);

    in = { std::string("Some"), std::string("data") };
    Calibri::join(out, in, std::string(" "));
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    Calibri::join(out, in, std::string(" "));
    QCOMPARE(out, check);
}

void tst_Join::testJoinForwardListToWString()
{
    std::wstring out {};
    decltype(out) check { L"Some data" };

    std::forward_list<std::wstring> in { std::wstring(L"Some"), std::wstring(L"dummy"), std::wstring(L"data") };
    Calibri::join(out, in, std::wstring(L" "), [](const std::wstring &data) noexcept { return data != std::wstring(L"dummy"); });
    QCOMPARE(out, check);

    in = { std::wstring(L"Some"), std::wstring(L"data") };
    Calibri::join(out, in, std::wstring(L" "));
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    Calibri::join(out, in, std::wstring(L" "));
    QCOMPARE(out, check);
}

void tst_Join::testJoinForwardListToByteArray()
{
    Calibri::ByteArray out {};
    decltype(out) check { "Some data" };

    std::forward_list<Calibri::ByteArray> in { Calibri::ByteArray("Some"), Calibri::ByteArray("dummy"), Calibri::ByteArray("data") };
    Calibri::join(out, in, Calibri::ByteArray(" "), [](const Calibri::ByteArray &data) noexcept { return data != Calibri::ByteArray("dummy"); });
    QCOMPARE(out, check);

    in = { "Some", "data" };
    Calibri::join(out, in, Calibri::ByteArray(" "));
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    Calibri::join(out, in, Calibri::ByteArray(" "));
    QCOMPARE(out, check);
}

void tst_Join::testJoinListToString()
{
    std::string out {};
    decltype(out) check { "Some data" };

    std::list<std::string> in { std::string("Some"), std::string("dummy"), std::string("data") };
    Calibri::join(out, in, std::string(" "), [](const std::string &data) noexcept { return data != std::string("dummy"); });
    QCOMPARE(out, check);

    in = { std::string("Some"), std::string("data") };
    Calibri::join(out, in, std::string(" "));
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    Calibri::join(out, in, std::string(" "));
    QCOMPARE(out, check);
}

void tst_Join::testJoinListToWString()
{
    std::wstring out {};
    decltype(out) check { L"Some data" };

    std::list<std::wstring> in { std::wstring(L"Some"), std::wstring(L"dummy"), std::wstring(L"data") };
    Calibri::join(out, in, std::wstring(L" "), [](const std::wstring &data) noexcept { return data != std::wstring(L"dummy"); });
    QCOMPARE(out, check);

    in = { std::wstring(L"Some"), std::wstring(L"data") };
    Calibri::join(out, in, std::wstring(L" "));
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    Calibri::join(out, in, std::wstring(L" "));
    QCOMPARE(out, check);
}

void tst_Join::testJoinListToByteArray()
{
    Calibri::ByteArray out {};
    decltype(out) check { "Some data" };

    std::list<Calibri::ByteArray> in { Calibri::ByteArray("Some"), Calibri::ByteArray("dummy"), Calibri::ByteArray("data") };
    Calibri::join(out, in, Calibri::ByteArray(" "), [](const Calibri::ByteArray &data) noexcept { return data != Calibri::ByteArray("dummy"); });
    QCOMPARE(out, check);

    in = { "Some", "data" };
    Calibri::join(out, in, Calibri::ByteArray(" "));
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    Calibri::join(out, in, Calibri::ByteArray(" "));
    QCOMPARE(out, check);
}

QTEST_MAIN(tst_Join)

#include "tst_join.moc"
