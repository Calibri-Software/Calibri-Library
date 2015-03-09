//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <crypto/digest.hpp>

class tst_Digest : public QObject
{
    Q_OBJECT
    
private slots:
    void testMD2();
    void testMD4();
    void testMD5();
    void testSHA1();
    void testSHA224();
    void testSHA256();
    void testSHA384();
    void testSHA512();
    void testRipeMD160();
    void testWhirlpool();
};

void tst_Digest::testMD2()
{
    bool ok {};

    auto out = Calibri::digest<Calibri::DigestAlgorithm::MD2>("Some data", &ok);
#if !defined(OPENSSL_NO_MD2)
    QVERIFY(ok);
    QCOMPARE(out.toHex(), Calibri::ByteArray("37eaced2cd7b11fbc7aacd381d793886"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Digest::testMD4()
{
    bool ok {};

    auto out = Calibri::digest<Calibri::DigestAlgorithm::MD4>("Some data", &ok);
#if !defined(OPENSSL_NO_MD4)
    QVERIFY(ok);
    QCOMPARE(out.toHex(), Calibri::ByteArray("f6c71a543d6cad6f99dbc9ccfcdf0dd5"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Digest::testMD5()
{
    bool ok {};

    auto out = Calibri::digest<Calibri::DigestAlgorithm::MD5>("Some data", &ok);
#if !defined(OPENSSL_NO_MD5)
    QVERIFY(ok);
    QCOMPARE(out.toHex(), Calibri::ByteArray("5b82f8bf4df2bfb0e66ccaa7306fd024"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Digest::testSHA1()
{
    bool ok {};

    auto out = Calibri::digest<Calibri::DigestAlgorithm::SHA1>("Some data", &ok);
#if !defined(OPENSSL_NO_SHA)
    QVERIFY(ok);
    QCOMPARE(out.toHex(), Calibri::ByteArray("8d72453f10079af3dfc7fcfc4109b1ed55e1839f"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Digest::testSHA224()
{
    bool ok {};

    auto out = Calibri::digest<Calibri::DigestAlgorithm::SHA224>("Some data", &ok);
#if !defined(OPENSSL_NO_SHA256)
    QVERIFY(ok);
    QCOMPARE(out.toHex(), Calibri::ByteArray("d84618b3a7d8c34e6424a7fc093937671eb96ec6bdf337de3f7ba955"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Digest::testSHA256()
{
    bool ok {};

    auto out = Calibri::digest<Calibri::DigestAlgorithm::SHA256>("Some data", &ok);
#if !defined(OPENSSL_NO_SHA256)
    QVERIFY(ok);
    QCOMPARE(out.toHex(), Calibri::ByteArray("1fe638b478f8f0b2c2aab3dbfd3f05d6dfe2191cd7b4482241fe58567e37aef6"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Digest::testSHA384()
{
    bool ok {};

    auto out = Calibri::digest<Calibri::DigestAlgorithm::SHA384>("Some data", &ok);
#if !defined(OPENSSL_NO_SHA512)
    QVERIFY(ok);
    QCOMPARE(out.toHex(), Calibri::ByteArray("eda5fa67268805ce0ffd8b7e9f955400b48d035096215104645d0f127353f5cb9334c2ddcba11e40bd7dada5df895ab6"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Digest::testSHA512()
{
    bool ok {};

    auto out = Calibri::digest<Calibri::DigestAlgorithm::SHA512>("Some data", &ok);
#if !defined(OPENSSL_NO_SHA512)
    QVERIFY(ok);
    QCOMPARE(out.toHex(), Calibri::ByteArray("d45e05966e70133821e4e5b7d43932cfbe9bca4c1d6bacb12d63e6f56f20b4e52cdb2e523a26266a412182553d980c661a98b5e974793d1c221a162f2014ec47"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Digest::testRipeMD160()
{
    bool ok {};

    auto out = Calibri::digest<Calibri::DigestAlgorithm::RipeMD160>("Some data", &ok);
#if !defined(OPENSSL_NO_RIPEMD)
    QVERIFY(ok);
    QCOMPARE(out.toHex(), Calibri::ByteArray("ab2d57a66e7f4aa3e3c7bee2d716d6d1307badfe"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Digest::testWhirlpool()
{
    bool ok {};

    auto out = Calibri::digest<Calibri::DigestAlgorithm::Whirlpool>("Some data", &ok);
#if !defined(OPENSSL_NO_WHIRLPOOL)
    QVERIFY(ok);
    QCOMPARE(out.toHex(), Calibri::ByteArray("a245df6d375e5b8392d5d115d0377df14b61832fe0e4a0ba9d5012250dcb11ca954c72ae8faa693c19c9b4dbd7d48d3476488300dec41e3ee707beb153872e7d"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

QTEST_MAIN(tst_Digest)

#include "tst_digest.moc"
