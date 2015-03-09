//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <algorithms/split.hpp>

class tst_Split : public QObject
{
    Q_OBJECT
    
private slots:
    void testSplitToStringVector();
    void testSplitToWStringVector();
    void testSplitToByteArrayVector();
    void testSplitToStringDeque();
    void testSplitToWStringDeque();
    void testSplitToByteArrayDeque();
    void testSplitToStringForwardList();
    void testSplitToWStringForwardList();
    void testSplitToByteArrayForwardList();
    void testSplitToStringList();
    void testSplitToWStringList();
    void testSplitToByteArrayList();
};

void tst_Split::testSplitToStringVector()
{
    std::vector<std::string> out;
    decltype(out) check { "Some", "data" };

    Calibri::split(out, std::string(";Some;;data;"), [](char character) noexcept { return character == ';'; });
    QCOMPARE(out, check);

    Calibri::split(out, std::string(";Some;;data;"), ';');
    QCOMPARE(out, check);

    Calibri::split(out, std::string(";;Some;;;;data;;"), std::string(";;"));
    QCOMPARE(out, check);

    check = { "Some data" };
    Calibri::split(out, std::string("Some data"), std::string(";"));
    QCOMPARE(out, check);
}

void tst_Split::testSplitToWStringVector()
{
    std::vector<std::wstring> out;
    decltype(out) check { L"Some", L"data" };

    Calibri::split(out, std::wstring(L";Some;;data;"), [](wchar character) noexcept { return character == L';'; });
    QCOMPARE(out, check);

    Calibri::split(out, std::wstring(L";Some;;data;"), L';');
    QCOMPARE(out, check);

    Calibri::split(out, std::wstring(L";;Some;;;;data;;"), std::wstring(L";;"));
    QCOMPARE(out, check);

    check = { L"Some data" };
    Calibri::split(out, std::wstring(L"Some data"), std::wstring(L";"));
    QCOMPARE(out, check);
}

void tst_Split::testSplitToByteArrayVector()
{
    std::vector<Calibri::ByteArray> out;
    decltype(out) check { "Some", "data" };

    Calibri::split(out, Calibri::ByteArray(";Some;;data;"), [](char character) noexcept { return character == ';'; });
    QCOMPARE(out, check);

    Calibri::split(out, Calibri::ByteArray(";Some;;data;"), ';');
    QCOMPARE(out, check);

    Calibri::split(out, Calibri::ByteArray(";;Some;;;;data;;"), Calibri::ByteArray(";;"));
    QCOMPARE(out, check);

    check = { "Some data" };
    Calibri::split(out, Calibri::ByteArray("Some data"), Calibri::ByteArray(";"));
    QCOMPARE(out, check);
}

void tst_Split::testSplitToStringDeque()
{
    std::deque<std::string> out;
    decltype(out) check { "Some", "data" };

    Calibri::split(out, std::string(";Some;;data;"), [](char character) noexcept { return character == ';'; });
    QCOMPARE(out, check);

    Calibri::split(out, std::string(";Some;;data;"), ';');
    QCOMPARE(out, check);

    Calibri::split(out, std::string(";;Some;;;;data;;"), std::string(";;"));
    QCOMPARE(out, check);

    check = { "Some data" };
    Calibri::split(out, std::string("Some data"), std::string(";"));
    QCOMPARE(out, check);
}

void tst_Split::testSplitToWStringDeque()
{
    std::deque<std::wstring> out;
    decltype(out) check { L"Some", L"data" };

    Calibri::split(out, std::wstring(L";Some;;data;"), [](wchar character) noexcept { return character == L';'; });
    QCOMPARE(out, check);

    Calibri::split(out, std::wstring(L";Some;;data;"), L';');
    QCOMPARE(out, check);

    Calibri::split(out, std::wstring(L";;Some;;;;data;;"), std::wstring(L";;"));
    QCOMPARE(out, check);

    check = { L"Some data" };
    Calibri::split(out, std::wstring(L"Some data"), std::wstring(L";"));
    QCOMPARE(out, check);
}

void tst_Split::testSplitToByteArrayDeque()
{
    std::deque<Calibri::ByteArray> out;
    decltype(out) check { "Some", "data" };

    Calibri::split(out, Calibri::ByteArray(";Some;;data;"), [](char character) noexcept { return character == ';'; });
    QCOMPARE(out, check);

    Calibri::split(out, Calibri::ByteArray(";Some;;data;"), ';');
    QCOMPARE(out, check);

    Calibri::split(out, Calibri::ByteArray(";;Some;;;;data;;"), Calibri::ByteArray(";;"));
    QCOMPARE(out, check);

    check = { "Some data" };
    Calibri::split(out, Calibri::ByteArray("Some data"), Calibri::ByteArray(";"));
    QCOMPARE(out, check);
}

void tst_Split::testSplitToStringForwardList()
{
    std::forward_list<std::string> out;
    decltype(out) check { "Some", "data" };

    Calibri::split(out, std::string(";Some;;data;"), [](char character) noexcept { return character == ';'; });
    QCOMPARE(out, check);

    Calibri::split(out, std::string(";Some;;data;"), ';');
    QCOMPARE(out, check);

    Calibri::split(out, std::string(";;Some;;;;data;;"), std::string(";;"));
    QCOMPARE(out, check);

    check = { "Some data" };
    Calibri::split(out, std::string("Some data"), std::string(";"));
    QCOMPARE(out, check);
}

void tst_Split::testSplitToWStringForwardList()
{
    std::forward_list<std::wstring> out;
    decltype(out) check { L"Some", L"data" };

    Calibri::split(out, std::wstring(L";Some;;data;"), [](wchar character) noexcept { return character == L';'; });
    QCOMPARE(out, check);

    Calibri::split(out, std::wstring(L";Some;;data;"), L';');
    QCOMPARE(out, check);

    Calibri::split(out, std::wstring(L";;Some;;;;data;;"), std::wstring(L";;"));
    QCOMPARE(out, check);

    check = { L"Some data" };
    Calibri::split(out, std::wstring(L"Some data"), std::wstring(L";"));
    QCOMPARE(out, check);
}

void tst_Split::testSplitToByteArrayForwardList()
{
    std::forward_list<Calibri::ByteArray> out;
    decltype(out) check { "Some", "data" };

    Calibri::split(out, Calibri::ByteArray(";Some;;data;"), [](char character) noexcept { return character == ';'; });
    QCOMPARE(out, check);

    Calibri::split(out, Calibri::ByteArray(";Some;;data;"), ';');
    QCOMPARE(out, check);

    Calibri::split(out, Calibri::ByteArray(";;Some;;;;data;;"), Calibri::ByteArray(";;"));
    QCOMPARE(out, check);

    check = { "Some data" };
    Calibri::split(out, Calibri::ByteArray("Some data"), Calibri::ByteArray(";"));
    QCOMPARE(out, check);
}

void tst_Split::testSplitToStringList()
{
    std::list<std::string> out;
    decltype(out) check { "Some", "data" };

    Calibri::split(out, std::string(";Some;;data;"), [](char character) noexcept { return character == ';'; });
    QCOMPARE(out, check);

    Calibri::split(out, std::string(";Some;;data;"), ';');
    QCOMPARE(out, check);

    Calibri::split(out, std::string(";;Some;;;;data;;"), std::string(";;"));
    QCOMPARE(out, check);

    check = { "Some data" };
    Calibri::split(out, std::string("Some data"), std::string(";"));
    QCOMPARE(out, check);
}

void tst_Split::testSplitToWStringList()
{
    std::list<std::wstring> out;
    decltype(out) check { L"Some", L"data" };

    Calibri::split(out, std::wstring(L";Some;;data;"), [](wchar character) noexcept { return character == L';'; });
    QCOMPARE(out, check);

    Calibri::split(out, std::wstring(L";Some;;data;"), L';');
    QCOMPARE(out, check);

    Calibri::split(out, std::wstring(L";;Some;;;;data;;"), std::wstring(L";;"));
    QCOMPARE(out, check);

    check = { L"Some data" };
    Calibri::split(out, std::wstring(L"Some data"), std::wstring(L";"));
    QCOMPARE(out, check);
}

void tst_Split::testSplitToByteArrayList()
{
    std::list<Calibri::ByteArray> out;
    decltype(out) check { "Some", "data" };

    Calibri::split(out, Calibri::ByteArray(";Some;;data;"), [](char character) noexcept { return character == ';'; });
    QCOMPARE(out, check);

    Calibri::split(out, Calibri::ByteArray(";Some;;data;"), ';');
    QCOMPARE(out, check);

    Calibri::split(out, Calibri::ByteArray(";;Some;;;;data;;"), Calibri::ByteArray(";;"));
    QCOMPARE(out, check);

    check = { "Some data" };
    Calibri::split(out, Calibri::ByteArray("Some data"), Calibri::ByteArray(";"));
    QCOMPARE(out, check);
}

QTEST_MAIN(tst_Split)

#include "tst_split.moc"
