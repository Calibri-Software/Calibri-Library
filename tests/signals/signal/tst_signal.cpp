//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <signals/signal.hpp>

class Trackable : public Calibri::EnableSignal
{
public:
    auto multiplier(int value) noexcept -> int { return value * value; }
    auto constMultiplier(int value) const noexcept -> int { return value * value; }
};

class SumMarshaller
{
public:
    SumMarshaller() = default;

    auto operator ()(int value) noexcept -> bool { m_sum += value; return false; }

    operator int() const noexcept { return m_sum; }

private:
    int m_sum {};
};

inline auto multiplier(int value) noexcept -> int { return value * value; }

class tst_Signal : public QObject, public Calibri::EnableSignal
{
    Q_OBJECT

private slots:
    void testFunction();
    void testFunctionObject();
    void testMemberFunction();
    void testConstMemberFunction();
    void testSignal();
    void testLastValue();
    void testVoidReturnType();
    void testMarshaller();

signals:
    void sig(int);
};

void tst_Signal::testFunction()
{
    Calibri::Signal<int (int)> signal;

    QVERIFY(signal.connect(::multiplier));
    QVERIFY(signal.disconnect(::multiplier));
    QVERIFY(!signal.disconnect(::multiplier));

    QVERIFY(signal.connect(::multiplier));
    QVERIFY(signal.connect(::multiplier));
    QVERIFY(signal.disconnect(::multiplier));
    QVERIFY(signal.disconnect(::multiplier));
    QVERIFY(!signal.disconnect(::multiplier));

    QVERIFY(signal.connect(::multiplier));
    QVERIFY(!signal.connect<Calibri::SignalConnectionMode::UniqueConnection>(::multiplier));
    QVERIFY(signal.disconnect(::multiplier));
    QVERIFY(!signal.disconnect(::multiplier));

    auto connection = signal.connect(::multiplier);
    QVERIFY(connection);
    QVERIFY(signal.disconnect(connection));
    QVERIFY(!signal.disconnect(connection));

    connection = signal.connect(::multiplier);
    QVERIFY(connection);
    QVERIFY(signal.connect(::multiplier));
    QVERIFY(signal.disconnect(connection));
    QVERIFY(!signal.disconnect(connection));
    QVERIFY(signal.disconnect(::multiplier));
    QVERIFY(!signal.disconnect(::multiplier));

    connection = signal.connect(::multiplier);
    QVERIFY(connection);
    QVERIFY(signal.connect(::multiplier));
    signal.disconnectAll();
    QVERIFY(!signal.disconnect(connection));
    QVERIFY(!signal.disconnect(::multiplier));

    QVERIFY(signal.connect(::multiplier));
    QCOMPARE(signal(5), 25);
}

void tst_Signal::testFunctionObject()
{
    Calibri::Signal<int (int)> signal;

    auto connection = signal.connect([](int value) { return value * value; });
    QVERIFY(connection);
    QVERIFY(signal.disconnect(connection));
    QVERIFY(!signal.disconnect(connection));

    auto firstConnection = signal.connect([](int value) { return value * value; });
    QVERIFY(firstConnection);
    auto secondConnection = signal.connect([](int value) { return value * value; });
    QVERIFY(secondConnection);
    QVERIFY(signal.disconnect(firstConnection));
    QVERIFY(!signal.disconnect(firstConnection));
    QVERIFY(signal.disconnect(secondConnection));
    QVERIFY(!signal.disconnect(secondConnection));

    firstConnection = signal.connect([](int value) { return value * value; });
    QVERIFY(firstConnection);
    secondConnection = signal.connect([](int value) { return value * value; });
    QVERIFY(secondConnection);
    signal.disconnectAll();
    QVERIFY(!signal.disconnect(firstConnection));
    QVERIFY(!signal.disconnect(secondConnection));

    QVERIFY(signal.connect([](int value) { return value * value; }));
    QCOMPARE(signal(5), 25);
}

void tst_Signal::testMemberFunction()
{
    Calibri::Signal<int (int)> signal;

    auto trackable = new Trackable;

    auto connection = signal.connect(trackable, &Trackable::multiplier);
    QVERIFY(connection);
    delete trackable;
    QVERIFY(!signal.disconnect(connection));
    QVERIFY(!signal.disconnect(trackable, &Trackable::multiplier));

    trackable = new Trackable;

    QVERIFY(signal.connect(trackable, &Trackable::multiplier));
    QVERIFY(signal.disconnect(trackable, &Trackable::multiplier));
    QVERIFY(!signal.disconnect(trackable, &Trackable::multiplier));

    QVERIFY(signal.connect(trackable, &Trackable::multiplier));
    QVERIFY(signal.connect(trackable, &Trackable::multiplier));
    QVERIFY(signal.disconnect(trackable, &Trackable::multiplier));
    QVERIFY(signal.disconnect(trackable, &Trackable::multiplier));
    QVERIFY(!signal.disconnect(trackable, &Trackable::multiplier));

    QVERIFY(signal.connect(trackable, &Trackable::multiplier));
    QVERIFY(!signal.connect<Calibri::SignalConnectionMode::UniqueConnection>(trackable, &Trackable::multiplier));
    QVERIFY(signal.disconnect(trackable, &Trackable::multiplier));
    QVERIFY(!signal.disconnect(trackable, &Trackable::multiplier));

    connection = signal.connect(trackable, &Trackable::multiplier);
    QVERIFY(connection);
    QVERIFY(signal.disconnect(connection));
    QVERIFY(!signal.disconnect(connection));

    connection = signal.connect(trackable, &Trackable::multiplier);
    QVERIFY(connection);
    QVERIFY(signal.connect(trackable, &Trackable::multiplier));
    QVERIFY(signal.disconnect(connection));
    QVERIFY(!signal.disconnect(connection));
    QVERIFY(signal.disconnect(trackable, &Trackable::multiplier));
    QVERIFY(!signal.disconnect(trackable, &Trackable::multiplier));

    connection = signal.connect(trackable, &Trackable::multiplier);
    QVERIFY(connection);
    QVERIFY(signal.connect(trackable, &Trackable::multiplier));
    signal.disconnectAll();
    QVERIFY(!signal.disconnect(connection));
    QVERIFY(!signal.disconnect(trackable, &Trackable::multiplier));

    QVERIFY(signal.connect(trackable, &Trackable::multiplier));
    QCOMPARE(signal(5), 25);

    delete trackable;
}

void tst_Signal::testConstMemberFunction()
{
    Calibri::Signal<int (int)> signal;

    auto trackable = new Trackable;

    auto connection = signal.connect(trackable, &Trackable::multiplier);
    QVERIFY(connection);
    delete trackable;
    QVERIFY(!signal.disconnect(connection));
    QVERIFY(!signal.disconnect(trackable, &Trackable::multiplier));

    trackable = new Trackable;

    QVERIFY(signal.connect(trackable, &Trackable::constMultiplier));
    QVERIFY(signal.disconnect(trackable, &Trackable::constMultiplier));
    QVERIFY(!signal.disconnect(trackable, &Trackable::constMultiplier));

    QVERIFY(signal.connect(trackable, &Trackable::constMultiplier));
    QVERIFY(signal.connect(trackable, &Trackable::constMultiplier));
    QVERIFY(signal.disconnect(trackable, &Trackable::constMultiplier));
    QVERIFY(signal.disconnect(trackable, &Trackable::constMultiplier));
    QVERIFY(!signal.disconnect(trackable, &Trackable::constMultiplier));

    QVERIFY(signal.connect(trackable, &Trackable::constMultiplier));
    QVERIFY(!signal.connect<Calibri::SignalConnectionMode::UniqueConnection>(trackable, &Trackable::constMultiplier));
    QVERIFY(signal.disconnect(trackable, &Trackable::constMultiplier));
    QVERIFY(!signal.disconnect(trackable, &Trackable::constMultiplier));

    connection = signal.connect(trackable, &Trackable::constMultiplier);
    QVERIFY(connection);
    QVERIFY(signal.disconnect(connection));
    QVERIFY(!signal.disconnect(connection));

    connection = signal.connect(trackable, &Trackable::constMultiplier);
    QVERIFY(connection);
    QVERIFY(signal.connect(trackable, &Trackable::constMultiplier));
    QVERIFY(signal.disconnect(connection));
    QVERIFY(!signal.disconnect(connection));
    QVERIFY(signal.disconnect(trackable, &Trackable::constMultiplier));
    QVERIFY(!signal.disconnect(trackable, &Trackable::constMultiplier));

    connection = signal.connect(trackable, &Trackable::constMultiplier);
    QVERIFY(connection);
    QVERIFY(signal.connect(trackable, &Trackable::constMultiplier));
    signal.disconnectAll();
    QVERIFY(!signal.disconnect(connection));
    QVERIFY(!signal.disconnect(trackable, &Trackable::constMultiplier));

    QVERIFY(signal.connect(trackable, &Trackable::constMultiplier));
    QCOMPARE(signal(5), 25);

    delete trackable;
}

void tst_Signal::testSignal()
{
    Calibri::Signal<int (int)> signal;

    auto callable = new decltype(signal)();
    callable->connect(::multiplier);

    auto connection = signal.connect(callable);
    QVERIFY(connection);
    delete callable;
    QVERIFY(!signal.disconnect(connection));
    QVERIFY(!signal.disconnect(callable));

    callable = new decltype(signal)();
    callable->connect(::multiplier);

    QVERIFY(signal.connect(callable));
    QVERIFY(signal.disconnect(callable));
    QVERIFY(!signal.disconnect(callable));

    QVERIFY(signal.connect(callable));
    QVERIFY(signal.connect(callable));
    QVERIFY(signal.disconnect(callable));
    QVERIFY(signal.disconnect(callable));
    QVERIFY(!signal.disconnect(callable));

    QVERIFY(signal.connect(callable));
    QVERIFY(!signal.connect<Calibri::SignalConnectionMode::UniqueConnection>(callable));
    QVERIFY(signal.disconnect(callable));
    QVERIFY(!signal.disconnect(callable));

    connection = signal.connect(callable);
    QVERIFY(connection);
    QVERIFY(signal.disconnect(connection));
    QVERIFY(!signal.disconnect(connection));

    connection = signal.connect(callable);
    QVERIFY(connection);
    QVERIFY(signal.connect(callable));
    QVERIFY(signal.disconnect(connection));
    QVERIFY(!signal.disconnect(connection));
    QVERIFY(signal.disconnect(callable));
    QVERIFY(!signal.disconnect(callable));

    connection = signal.connect(callable);
    QVERIFY(connection);
    QVERIFY(signal.connect(callable));
    signal.disconnectAll();
    QVERIFY(!signal.disconnect(connection));
    QVERIFY(!signal.disconnect(callable));

    QVERIFY(signal.connect(callable));
    QCOMPARE(signal(5), 25);

    delete callable;
}

void tst_Signal::testLastValue()
{
    Calibri::Signal<int (int)> signal;

    QVERIFY(signal.connect([](int value) { return value * value; }));
    QVERIFY(signal.connect([](int value) { return value * value + value; }));

    QCOMPARE(signal(5), 30);
}

void tst_Signal::testVoidReturnType()
{
    Calibri::Signal<void (int &)> signal;

    QVERIFY(signal.connect([](int &value) { value *= value; }));
    QVERIFY(signal.connect([](int &value) { value += value; }));

    int value = 5;

    signal(value);

    QCOMPARE(value, 50);
}

void tst_Signal::testMarshaller()
{
    Calibri::Signal<int (int )> signal;
    QVERIFY(signal.connect([](int value) { return value + value; }));
    QVERIFY(signal.connect([](int value) { return value + value; }));
    QVERIFY(signal.connect([](int value) { return value + value; }));
    QVERIFY(signal.connect([](int value) { return value + value; }));
    QVERIFY(signal.connect([](int value) { return value + value; }));

    QCOMPARE(signal(SumMarshaller(), 5), 50);
}

QTEST_MAIN(tst_Signal)

#include "tst_signal.moc"
