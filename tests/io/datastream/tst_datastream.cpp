//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <io/datastream.hpp>

class tst_DataStream : public QObject
{
    Q_OBJECT
    
private slots:
    void testInt8();
    void testUInt8();
    void testInt16();
    void testUInt16();
    void testInt32();
    void testUInt32();
    void testInt64();
    void testUInt64();
    void testFloat();
    void testDouble();
    void testLongDouble();
    void testCString();
    void testString();
    void testSeek();
    void testVector();
    void testDeque();
    void testForwardList();
    void testList();
    void testSet();
    void testMultiSet();
    void testMap();
    void testMultiMap();
    void testUnorderedSet();
    void testUnorderedMultiSet();
    void testUnorderedMap();
    void testUnorderedMultiMap();
};

void tst_DataStream::testInt8()
{
    int8 in { 64 };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QCOMPARE(out, Calibri::metaCast<decltype(in)>(0));
}

void tst_DataStream::testUInt8()
{
    uint8 in { 64 };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QCOMPARE(out, Calibri::metaCast<decltype(in)>(0));
}

void tst_DataStream::testInt16()
{
    int16 in { 64 };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QCOMPARE(out, Calibri::metaCast<decltype(in)>(0));
}

void tst_DataStream::testUInt16()
{
    uint16 in { 64 };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QCOMPARE(out, Calibri::metaCast<decltype(in)>(0));
}

void tst_DataStream::testInt32()
{
    int32 in { 64 };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QCOMPARE(out, Calibri::metaCast<decltype(in)>(0));
}

void tst_DataStream::testUInt32()
{
    uint32 in { 64 };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QCOMPARE(out, Calibri::metaCast<decltype(in)>(0));
}

void tst_DataStream::testInt64()
{
    int64 in { 64 };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QCOMPARE(out, Calibri::metaCast<decltype(in)>(0));
}

void tst_DataStream::testUInt64()
{
    uint64 in { 64 };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QCOMPARE(out, Calibri::metaCast<decltype(in)>(0));
}

void tst_DataStream::testFloat()
{
    float in { 64.0064f };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QCOMPARE(out, Calibri::metaCast<decltype(in)>(0));
}

void tst_DataStream::testDouble()
{
    double in { 64.0064 };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QCOMPARE(out, Calibri::metaCast<decltype(in)>(0));
}

void tst_DataStream::testLongDouble()
{
    longdouble in { 64.0064l };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QCOMPARE(out, Calibri::metaCast<decltype(in)>(0));
}

void tst_DataStream::testCString()
{
    const char *in { "cstring data" };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    char *out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QVERIFY(out);
    QCOMPARE(out, in);

    delete[] out;

    uint32 badSize { 256 };
    data.reset();
    writeStream << badSize;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);
    data.reset();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(!out);
}

void tst_DataStream::testString()
{
    std::string in { "string data" };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(out, in);

    uint32 badSize { 256 };
    data.reset();
    writeStream << badSize;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);
    data.reset();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(out.empty());
}

void tst_DataStream::testSeek()
{
    std::string in { "string data" };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << 0;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);
    writeStream.device()->seek(0);
    writeStream << Calibri::metaCast<uint32>(in.size());
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    uint32 size {};
    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> size;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(Calibri::metaCast<sizeinfo>(size), in.size());
    QCOMPARE(out, in);
}

void tst_DataStream::testVector()
{
    std::vector<std::string> in { 2, "string data" };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(out.empty());
}

void tst_DataStream::testDeque()
{
    std::deque<std::string> in { 2, "string data" };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(out.empty());
}

void tst_DataStream::testForwardList()
{
    std::forward_list<std::string> in { 2, "string data" };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(out.empty());
}

void tst_DataStream::testList()
{
    std::list<std::string> in { 2, "string data" };

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(out.empty());
}

void tst_DataStream::testSet()
{
    std::set<std::string> in {};
    in.emplace("string data");

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(out.empty());
}

void tst_DataStream::testMultiSet()
{
    std::multiset<std::string> in {};
    in.emplace("string data");
    in.emplace("string data");

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(out.empty());
}

void tst_DataStream::testMap()
{
    std::map<std::string, std::string> in {};
    in.emplace("key one", "value one");
    in.emplace("key two", "value two");

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(out.empty());
}

void tst_DataStream::testMultiMap()
{
    std::multimap<std::string, std::string> in {};
    in.emplace("key one", "value one");
    in.emplace("key one", "value two");

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(out.empty());
}

void tst_DataStream::testUnorderedSet()
{
    std::unordered_set<std::string> in {};
    in.emplace("string data");

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(out.empty());
}

void tst_DataStream::testUnorderedMultiSet()
{
    std::unordered_multiset<std::string> in {};
    in.emplace("string data");
    in.emplace("string data");

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(out.empty());
}

void tst_DataStream::testUnorderedMap()
{
    std::unordered_map<std::string, std::string> in {};
    in.emplace("key one", "value one");
    in.emplace("key two", "value two");

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(out.empty());
}

void tst_DataStream::testUnorderedMultiMap()
{
    std::unordered_multimap<std::string, std::string> in {};
    in.emplace("key one", "value one");
    in.emplace("key one", "value two");

    Calibri::Buffer data {};
    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;
    QCOMPARE(writeStream.status(), Calibri::DataStreamStatus::Ok);

    data.reset();

    decltype(in) out {};
    decltype(writeStream) readStream(&data);
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::Ok);
    QCOMPARE(out, in);

    data = Calibri::Buffer();
    readStream >> out;
    QCOMPARE(readStream.status(), Calibri::DataStreamStatus::ReadError);
    QVERIFY(out.empty());
}

QTEST_MAIN(tst_DataStream)

#include "tst_datastream.moc"
