#ifndef CALIBRI_CRYPTO_DIGEST_HPP
#define CALIBRI_CRYPTO_DIGEST_HPP

// Std includes
#include <type_traits>

// OpenSSL includes
#include <openssl/evp.h>

// Calibri-Library includes
#include "tools/bytearray.hpp"
#include "tools/metacast.hpp"

namespace Calibri {

namespace Crypto {

// Enumerations
enum class DigestAlgorithm : uint8 {
    MD2,
    MD4,
    MD5,
    SHA,
    SHA1,
    DSS,
    DSS1,
    ECDSA,
    SHA224,
    SHA256,
    SHA384,
    SHA512,
    MDC2,
    RipeMD160,
    Whirlpool
};

namespace Internal {

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::MD2>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_MD2)
    return EVP_md2();
#else
    std::cerr << "OpenSSL MD2 algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::MD4>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_MD4)
    return EVP_md4();
#else
    std::cerr << "OpenSSL MD4 algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::MD5>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_MD5)
    return EVP_md5();
#else
    std::cerr << "OpenSSL MD5 algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::SHA>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_SHA)
    return EVP_sha();
#else
    std::cerr << "OpenSSL SHA algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::SHA1>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_SHA)
    return EVP_sha1();
#else
    std::cerr << "OpenSSL SHA1 algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::DSS>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_SHA)
    return EVP_dss();
#else
    std::cerr << "OpenSSL DSS algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::DSS1>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_SHA)
    return EVP_dss1();
#else
    std::cerr << "OpenSSL DSS1 algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::ECDSA>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_SHA)
    return EVP_ecdsa();
#else
    std::cerr << "OpenSSL ECDSA algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::SHA224>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_SHA256)
    return EVP_sha224();
#else
    std::cerr << "OpenSSL SHA224 algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::SHA256>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_SHA256)
    return EVP_sha256();
#else
    std::cerr << "OpenSSL SHA256 algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::SHA384>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_SHA512)
    return EVP_sha384();
#else
    std::cerr << "OpenSSL SHA384 algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::SHA512>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_SHA512)
    return EVP_sha512();
#else
    std::cerr << "OpenSSL SHA512 algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::MDC2>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_MDC2)
    return EVP_mdc2();
#else
    std::cerr << "OpenSSL MDC2 algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::RipeMD160>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_RIPEMD)
    return EVP_ripemd160();
#else
    std::cerr << "OpenSSL RipeMD160 algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::Whirlpool>::type ...Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
#if !defined(OPENSSL_NO_WHIRLPOOL)
    return EVP_whirlpool();
#else
    std::cerr << "OpenSSL Whirlpool algorithm unavailable" << std::endl;

    return EVP_md_null();
#endif
}

} // end namespace Internal

template<DigestAlgorithm Type>
auto digest(const ByteArray &data, bool *ok = nullptr) noexcept -> ByteArray
{
    auto digestAlgorithm = Internal::digestAlgorithm<Type>();

    if (digestAlgorithm == EVP_md_null()) {
        if (ok)
            *ok = false;

        return {};
    }

    auto digestData = ByteArray(metaCast<sizeinfo>(EVP_MD_size(digestAlgorithm)));

    auto digestContext = EVP_MD_CTX();
    EVP_MD_CTX_init(&digestContext);

    if (EVP_DigestInit(&digestContext, digestAlgorithm) != 1) {
        EVP_MD_CTX_cleanup(&digestContext);

        if (ok)
            *ok = false;

        return {};
    }

    if (EVP_DigestUpdate(&digestContext, reinterpret_cast<const uchar *>(data.data()), data.size()) != 1) {
        EVP_MD_CTX_cleanup(&digestContext);

        if (ok)
            *ok = false;

        return {};
    }

    if (EVP_DigestFinal(&digestContext, reinterpret_cast<uchar *>(digestData.data()), nullptr) != 1) {
        EVP_MD_CTX_cleanup(&digestContext);

        if (ok)
            *ok = false;

        return {};
    }

    EVP_MD_CTX_cleanup(&digestContext);

    if (ok)
        *ok = true;

    return digestData;
}

} // end namespace Crypto

using Crypto::DigestAlgorithm;
using Crypto::digest;

} // end namespace Calibri

#endif // CALIBRI_CRYPTO_DIGEST_HPP
