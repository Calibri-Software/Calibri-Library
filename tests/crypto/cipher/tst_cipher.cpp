//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <crypto/cipher.hpp>

class tst_Cipher : public QObject
{
    Q_OBJECT
    
private slots:
    void testDES();
    void testRC4();
    void testIDEA();
    void testRC2();
    void testBF();
    void testCAST5();
    void testRC5();
    void testAES();
    void testCAMELLIA();
    void testSEED();
};

void tst_Cipher::testDES()
{
    bool ok {};

    //! DES
    auto out = Calibri::cipher<Calibri::CipherAlgorithm::DESecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_DES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::DESecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::DEScbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_DES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::DEScbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::DEScfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_DES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::DEScfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::DESofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_DES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::DESofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    //! DES2
    out = Calibri::cipher<Calibri::CipherAlgorithm::DES2ecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_DES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::DES2ecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::DES2cbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_DES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::DES2cbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::DES2cfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_DES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::DES2cfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::DES2ofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_DES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::DES2ofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    //! DES3
    out = Calibri::cipher<Calibri::CipherAlgorithm::DES3ecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_DES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::DES3ecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::DES3cbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_DES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::DES3cbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::DES3cfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_DES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::DES3cfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::DES3ofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_DES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::DES3ofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    //! DESX
    out = Calibri::cipher<Calibri::CipherAlgorithm::DESXcbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_DES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::DESXcbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Cipher::testRC4()
{
    bool ok {};

    auto out = Calibri::cipher<Calibri::CipherAlgorithm::RC4, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_RC4)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::RC4, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Cipher::testIDEA()
{
    bool ok {};

    auto out = Calibri::cipher<Calibri::CipherAlgorithm::IDEAecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_IDEA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::IDEAecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::IDEAcbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_IDEA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::IDEAcbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::IDEAcfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_IDEA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::IDEAcfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::IDEAofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_IDEA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::IDEAofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Cipher::testRC2()
{
    bool ok {};

    auto out = Calibri::cipher<Calibri::CipherAlgorithm::RC2ecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_RC2)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::RC2ecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::RC2cbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_RC2)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::RC2cbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::RC2cfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_RC2)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::RC2cfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::RC2ofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_RC2)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::RC2ofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Cipher::testBF()
{
    bool ok {};

    auto out = Calibri::cipher<Calibri::CipherAlgorithm::BFecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_BF)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::BFecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::BFcbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_BF)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::BFcbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::BFcfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_BF)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::BFcfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::BFofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_BF)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::BFofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Cipher::testCAST5()
{
    bool ok {};

    auto out = Calibri::cipher<Calibri::CipherAlgorithm::CAST5ecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAST)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAST5ecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::CAST5cbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAST)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAST5cbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::CAST5cfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAST)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAST5cfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::CAST5ofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAST)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAST5ofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Cipher::testRC5()
{
    bool ok {};

    auto out = Calibri::cipher<Calibri::CipherAlgorithm::RC5ecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_RC5)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::RC5ecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::RC5cbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_RC5)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::RC5cbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::RC5cfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_RC5)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::RC5cfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::RC5ofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_RC5)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::RC5ofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Cipher::testAES()
{
    bool ok {};

    //! AES128
    auto out = Calibri::cipher<Calibri::CipherAlgorithm::AES128ecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES128ecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::AES128cbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES128cbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::AES128cfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES128cfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::AES128ofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES128ofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::AES128ctr, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES128ctr, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    //! AES192
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES192ecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES192ecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::AES192cbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES192cbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::AES192cfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES192cfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::AES192ofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES192ofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::AES192ctr, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES192ctr, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    //! AES256
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES256ecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES256ecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::AES256cbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES256cbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::AES256cfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES256cfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::AES256ofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES256ofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::AES256ctr, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_AES)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::AES256ctr, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Cipher::testCAMELLIA()
{
    bool ok {};

    //! CAMELLIA128
    auto out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA128ecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAMELLIA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA128ecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA128cbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAMELLIA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA128cbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA128cfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAMELLIA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA128cfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA128ofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAMELLIA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA128ofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    //! CAMELLIA192
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA192ecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAMELLIA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA192ecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA192cbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAMELLIA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA192cbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA192cfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAMELLIA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA192cfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA192ofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAMELLIA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA192ofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    //! CAMELLIA256
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA256ecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAMELLIA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA256ecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA256cbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAMELLIA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA256cbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA256cfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAMELLIA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA256cfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA256ofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_CAMELLIA)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::CAMELLIA256ofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

void tst_Cipher::testSEED()
{
    bool ok {};

    //! CAMELLIA128
    auto out = Calibri::cipher<Calibri::CipherAlgorithm::SEEDecb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_SEED)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::SEEDecb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::SEEDcbc, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_SEED)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::SEEDcbc, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::SEEDcfb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_SEED)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::SEEDcfb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif

    out = Calibri::cipher<Calibri::CipherAlgorithm::SEEDofb, Calibri::CipherMode::Encrypt>("Some data", "Some key", "Some iv", &ok);
#if !defined(OPENSSL_NO_SEED)
    QVERIFY(ok);
    out = Calibri::cipher<Calibri::CipherAlgorithm::SEEDofb, Calibri::CipherMode::Decrypt>(out, "Some key", "Some iv", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("Some data"));
#else
    QVERIFY(!ok);
    QVERIFY(out.empty());
#endif
}

QTEST_MAIN(tst_Cipher)

#include "tst_cipher.moc"
