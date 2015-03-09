#ifndef CALIBRI_CRYPTO_CIPHER_HPP
#define CALIBRI_CRYPTO_CIPHER_HPP

//! Std includes
#include <type_traits>

//! OpenSSL includes
#include <openssl/evp.h>

//! Calibri-Library includes
#include "global/compilerdetection.hpp"
#include "tools/bytearray.hpp"

namespace Calibri {

namespace Crypto {

//! Enumerations
enum class CipherAlgorithm : uint8 {
    DESecb,
    DEScbc,
    DEScfb,
    DESofb,
    DES2ecb,
    DES2cbc,
    DES2cfb,
    DES2ofb,
    DES3ecb,
    DES3cbc,
    DES3cfb,
    DES3ofb,
    DESXcbc,
    RC4,
    IDEAecb,
    IDEAcbc,
    IDEAcfb,
    IDEAofb,
    RC2ecb,
    RC2cbc,
    RC2cfb,
    RC2ofb,
    BFecb,
    BFcbc,
    BFcfb,
    BFofb,
    CAST5ecb,
    CAST5cbc,
    CAST5cfb,
    CAST5ofb,
    RC5ecb,
    RC5cbc,
    RC5cfb,
    RC5ofb,
    AES128ecb,
    AES128cbc,
    AES128cfb,
    AES128ofb,
    AES128ctr,
    AES192ecb,
    AES192cbc,
    AES192cfb,
    AES192ofb,
    AES192ctr,
    AES256ecb,
    AES256cbc,
    AES256cfb,
    AES256ofb,
    AES256ctr,
    CAMELLIA128ecb,
    CAMELLIA128cbc,
    CAMELLIA128cfb,
    CAMELLIA128ofb,
    CAMELLIA192ecb,
    CAMELLIA192cbc,
    CAMELLIA192cfb,
    CAMELLIA192ofb,
    CAMELLIA256ecb,
    CAMELLIA256cbc,
    CAMELLIA256cfb,
    CAMELLIA256ofb,
    SEEDecb,
    SEEDcbc,
    SEEDcfb,
    SEEDofb
};

enum class CipherMode : uint8 {
    Encrypt,
    Decrypt
};

namespace Internal {

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DESecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_DES)
    return EVP_des_ecb();
#else
    std::cerr << "OpenSSL DESecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DEScbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_DES)
    return EVP_des_cbc();
#else
    std::cerr << "OpenSSL DEScbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DEScfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_DES)
    return EVP_des_cfb();
#else
    std::cerr << "OpenSSL DEScfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DESofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_DES)
    return EVP_des_ofb();
#else
    std::cerr << "OpenSSL DESofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DES2ecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_DES)
    return EVP_des_ede_ecb();
#else
    std::cerr << "OpenSSL DoubleDESecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DES2cbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_DES)
    return EVP_des_ede_cbc();
#else
    std::cerr << "OpenSSL DoubleDEScbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DES2cfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_DES)
    return EVP_des_ede_cfb();
#else
    std::cerr << "OpenSSL DoubleDEScfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DES2ofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_DES)
    return EVP_des_ede_ofb();
#else
    std::cerr << "OpenSSL DoubleDESofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DES3ecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_DES)
    return EVP_des_ede3_ecb();
#else
    std::cerr << "OpenSSL TripleDESecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DES3cbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_DES)
    return EVP_des_ede3_cbc();
#else
    std::cerr << "OpenSSL TripleDEScbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DES3cfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_DES)
    return EVP_des_ede3_cfb();
#else
    std::cerr << "OpenSSL TripleDEScfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DES3ofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_DES)
    return EVP_des_ede3_ofb();
#else
    std::cerr << "OpenSSL TripleDESofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DESXcbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_DES)
    return EVP_desx_cbc();
#else
    std::cerr << "OpenSSL DESXcbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC4>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_RC4)
    return EVP_rc4();
#else
    std::cerr << "OpenSSL RC4 algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::IDEAecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_IDEA)
    return EVP_idea_ecb();
#else
    std::cerr << "OpenSSL IDEAecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::IDEAcbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_IDEA)
    return EVP_idea_cbc();
#else
    std::cerr << "OpenSSL IDEAcbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::IDEAcfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_IDEA)
    return EVP_idea_cfb();
#else
    std::cerr << "OpenSSL IDEAcfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::IDEAofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_IDEA)
    return EVP_idea_ofb();
#else
    std::cerr << "OpenSSL IDEAofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC2ecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_RC2)
    return EVP_rc2_ecb();
#else
    std::cerr << "OpenSSL RC2ecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC2cbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_RC2)
    return EVP_rc2_cbc();
#else
    std::cerr << "OpenSSL RC2cbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC2cfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_RC2)
    return EVP_rc2_cfb();
#else
    std::cerr << "OpenSSL RC2cfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC2ofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_RC2)
    return EVP_rc2_ofb();
#else
    std::cerr << "OpenSSL RC2ofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::BFecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_BF)
    return EVP_bf_ecb();
#else
    std::cerr << "OpenSSL BFecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::BFcbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_BF)
    return EVP_bf_cbc();
#else
    std::cerr << "OpenSSL BFcbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::BFcfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_BF)
    return EVP_bf_cfb();
#else
    std::cerr << "OpenSSL BFcfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::BFofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_BF)
    return EVP_bf_ofb();
#else
    std::cerr << "OpenSSL BFofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAST5ecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAST)
    return EVP_cast5_ecb();
#else
    std::cerr << "OpenSSL CAST5ecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAST5cbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAST)
    return EVP_cast5_cbc();
#else
    std::cerr << "OpenSSL CAST5cbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAST5cfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAST)
    return EVP_cast5_cfb();
#else
    std::cerr << "OpenSSL CAST5cfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAST5ofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAST)
    return EVP_cast5_ofb();
#else
    std::cerr << "OpenSSL CAST5ofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC5ecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_RC5)
    return EVP_rc5_32_12_16_ecb();
#else
    std::cerr << "OpenSSL RC5ecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC5cbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_RC5)
    return EVP_rc5_32_12_16_cbc();
#else
    std::cerr << "OpenSSL RC5cbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC5cfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_RC5)
    return EVP_rc5_32_12_16_cfb();
#else
    std::cerr << "OpenSSL RC5cfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC5ofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_RC5)
    return EVP_rc5_32_12_16_ofb();
#else
    std::cerr << "OpenSSL RC5ofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES128ecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_128_ecb();
#else
    std::cerr << "OpenSSL AES128ecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES128cbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_128_cbc();
#else
    std::cerr << "OpenSSL AES128cbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES128cfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_128_cfb();
#else
    std::cerr << "OpenSSL AES128cfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES128ofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_128_ofb();
#else
    std::cerr << "OpenSSL AES128ofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES128ctr>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_128_ctr();
#else
    std::cerr << "OpenSSL AES128ctr algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES192ecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_192_ecb();
#else
    std::cerr << "OpenSSL AES192ecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES192cbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_192_cbc();
#else
    std::cerr << "OpenSSL AES192cbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES192cfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_192_cfb();
#else
    std::cerr << "OpenSSL AES192cfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES192ofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_192_ofb();
#else
    std::cerr << "OpenSSL AES192ofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES192ctr>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_192_ctr();
#else
    std::cerr << "OpenSSL AES192ctr algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES256ecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_256_ecb();
#else
    std::cerr << "OpenSSL AES256ecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES256cbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_256_cbc();
#else
    std::cerr << "OpenSSL AES256cbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES256cfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_256_cfb();
#else
    std::cerr << "OpenSSL AES256cfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES256ofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_256_ofb();
#else
    std::cerr << "OpenSSL AES256ofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES256ctr>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_AES)
    return EVP_aes_256_ctr();
#else
    std::cerr << "OpenSSL AES256ctr algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA128ecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAMELLIA)
    return EVP_camellia_128_ecb();
#else
    std::cerr << "OpenSSL CAMELLIA128ecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA128cbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAMELLIA)
    return EVP_camellia_128_cbc();
#else
    std::cerr << "OpenSSL CAMELLIA128cbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA128cfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAMELLIA)
    return EVP_camellia_128_cfb();
#else
    std::cerr << "OpenSSL CAMELLIA128cfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA128ofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAMELLIA)
    return EVP_camellia_128_ofb();
#else
    std::cerr << "OpenSSL CAMELLIA128ofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA192ecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAMELLIA)
    return EVP_camellia_192_ecb();
#else
    std::cerr << "OpenSSL CAMELLIA192ecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA192cbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAMELLIA)
    return EVP_camellia_192_cbc();
#else
    std::cerr << "OpenSSL CAMELLIA192cbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA192cfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAMELLIA)
    return EVP_camellia_192_cfb();
#else
    std::cerr << "OpenSSL CAMELLIA192cfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA192ofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAMELLIA)
    return EVP_camellia_192_ofb();
#else
    std::cerr << "OpenSSL CAMELLIA192ofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA256ecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAMELLIA)
    return EVP_camellia_256_ecb();
#else
    std::cerr << "OpenSSL CAMELLIA256ecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA256cbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAMELLIA)
    return EVP_camellia_256_cbc();
#else
    std::cerr << "OpenSSL CAMELLIA256cbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA256cfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAMELLIA)
    return EVP_camellia_256_cfb();
#else
    std::cerr << "OpenSSL CAMELLIA256cfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA256ofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_CAMELLIA)
    return EVP_camellia_256_ofb();
#else
    std::cerr << "OpenSSL CAMELLIA256ofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::SEEDecb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_SEED)
    return EVP_seed_ecb();
#else
    std::cerr << "OpenSSL SEEDecb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::SEEDcbc>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_SEED)
    return EVP_seed_cbc();
#else
    std::cerr << "OpenSSL SEEDcbc algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::SEEDcfb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_SEED)
    return EVP_seed_cfb();
#else
    std::cerr << "OpenSSL SEEDcfb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::SEEDofb>::type ...Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
#if !defined(OPENSSL_NO_SEED)
    return EVP_seed_ofb();
#else
    std::cerr << "OpenSSL SEEDofb algorithm unavailable" << std::endl;

    return EVP_enc_null();
#endif
}

} // end namespace Internal

template<CipherAlgorithm Type,
         CipherMode Mode,
         typename std::enable_if<Mode == CipherMode::Encrypt>::type ...Enabler>
auto cipher(const ByteArray &data, const ByteArray &key, const ByteArray &iv, bool *ok = nullptr) noexcept -> ByteArray
{
    int32 processedBytes {};
    int32 encryptedBytes {};

    auto cipherAlgorithm = Internal::cipherAlgorithm<Type>();

    if (cipherAlgorithm == EVP_enc_null()) {
        if (ok)
            *ok = false;

        return {};
    }

    auto encryptedData = ByteArray(data.size() + EVP_CIPHER_block_size(cipherAlgorithm) - 1);

    auto cipherContext = EVP_CIPHER_CTX();
    EVP_CIPHER_CTX_init(&cipherContext);

    if (EVP_EncryptInit(&cipherContext, cipherAlgorithm, reinterpret_cast<const uchar *>(key.data()), reinterpret_cast<const uchar *>(iv.data())) != 1) {
        EVP_CIPHER_CTX_cleanup(&cipherContext);

        if (ok)
            *ok = false;

        return {};
    }

    if (EVP_EncryptUpdate(&cipherContext, reinterpret_cast<uchar *>(encryptedData.data()), &processedBytes, reinterpret_cast<const uchar *>(data.data()), data.size()) != 1) {
        EVP_CIPHER_CTX_cleanup(&cipherContext);

        if (ok)
            *ok = false;

        return {};
    }

    encryptedBytes += processedBytes;

    if (EVP_EncryptFinal(&cipherContext, reinterpret_cast<uchar *>(encryptedData.data() + encryptedBytes), &processedBytes) != 1) {
        EVP_CIPHER_CTX_cleanup(&cipherContext);

        if (ok)
            *ok = false;

        return {};
    }

    encryptedBytes += processedBytes;

    EVP_CIPHER_CTX_cleanup(&cipherContext);

    encryptedData.resize(encryptedBytes);

    if (ok)
        *ok = true;

    return encryptedData;
}

template<CipherAlgorithm Type,
         CipherMode Mode,
         typename std::enable_if<Mode == CipherMode::Decrypt>::type ...Enabler>
auto cipher(const ByteArray &data, const ByteArray &key, const ByteArray &iv, bool *ok = nullptr) noexcept -> ByteArray
{
    int32 processedBytes {};
    int32 decryptedBytes {};

    auto cipherAlgorithm = Internal::cipherAlgorithm<Type>();

    if (cipherAlgorithm == EVP_enc_null()) {
        if (ok)
            *ok = false;

        return {};
    }

    auto decryptedData = ByteArray(data.size() + EVP_CIPHER_block_size(cipherAlgorithm));

    auto cipherContext = EVP_CIPHER_CTX();
    EVP_CIPHER_CTX_init(&cipherContext);

    if (EVP_DecryptInit(&cipherContext, cipherAlgorithm, reinterpret_cast<const uchar *>(key.data()), reinterpret_cast<const uchar *>(iv.data())) != 1) {
        EVP_CIPHER_CTX_cleanup(&cipherContext);

        if (ok)
            *ok = false;

        return {};
    }

    if (EVP_DecryptUpdate(&cipherContext, reinterpret_cast<uchar *>(decryptedData.data()), &processedBytes, reinterpret_cast<const uchar *>(data.data()), data.size()) != 1) {
        EVP_CIPHER_CTX_cleanup(&cipherContext);

        if (ok)
            *ok = false;

        return {};
    }

    decryptedBytes += processedBytes;

    if (EVP_DecryptFinal(&cipherContext, reinterpret_cast<uchar *>(decryptedData.data() + decryptedBytes), &processedBytes) != 1) {
        EVP_CIPHER_CTX_cleanup(&cipherContext);

        if (ok)
            *ok = false;

        return {};
    }

    decryptedBytes += processedBytes;

    EVP_CIPHER_CTX_cleanup(&cipherContext);

    decryptedData.resize(decryptedBytes);

    if (ok)
        *ok = true;

    return decryptedData;
}

} // end namespace Crypto

using Crypto::CipherAlgorithm;
using Crypto::CipherMode;
using Crypto::cipher;

} // end namespace Calibri

#endif // CALIBRI_CRYPTO_CIPHER_HPP
