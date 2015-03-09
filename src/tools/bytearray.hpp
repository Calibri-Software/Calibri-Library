#ifndef CALIBRI_TOOLS_BYTEARRAY_HPP
#define CALIBRI_TOOLS_BYTEARRAY_HPP

//! Std includes
#include <vector>
#include <iostream>
#include <algorithm>

//! Calibri-Library includes
#include "global/types.hpp"

namespace Calibri {

namespace Tools {

/*!
 *  ByteArray class
 */
class ByteArray : public std::vector<char>
{
public:
    using std::vector<char>::vector;
    ByteArray() = default;
    ByteArray(const char *data, sizeinfo size);
    ByteArray(const char *data);

    operator const char *() const noexcept;
    operator char *() noexcept;

    auto operator +=(const ByteArray &data) noexcept -> ByteArray &;
    auto operator +=(const char *data) noexcept -> ByteArray &;
    auto operator +=(char character) noexcept -> ByteArray &;
    auto operator +=(std::initializer_list<char> data) noexcept -> ByteArray &;

    auto append(const ByteArray &data) noexcept -> ByteArray &;
    auto append(const char *data, sizeinfo size) noexcept -> ByteArray &;
    auto append(const char *data) noexcept -> ByteArray &;
    auto append(char character) noexcept -> ByteArray &;
    auto append(std::initializer_list<char> data) noexcept -> ByteArray &;

    auto toHex() const noexcept -> ByteArray;
    auto toBase64() const noexcept -> ByteArray;

    static auto fromHex(const ByteArray &data, bool *ok = nullptr) noexcept -> ByteArray;
    static auto fromBase64(const ByteArray &data, bool *ok = nullptr) noexcept -> ByteArray;
};

/*!
 *  ByteArray inline methods
 */
inline ByteArray::ByteArray(const char *data, sizeinfo size) :
    std::vector<char>(data, std::next(data, size))
{
}

inline ByteArray::ByteArray(const char *data) :
    ByteArray(data, std::char_traits<char>::length(data))
{
}

inline ByteArray::operator const char *() const noexcept
{
    return data();
}

inline ByteArray::operator char *() noexcept
{
    return data();
}

inline auto ByteArray::operator +=(const ByteArray &data) noexcept -> ByteArray &
{
    return append(data);
}

inline auto ByteArray::operator +=(const char *data) noexcept -> ByteArray &
{
    return append(data);
}

inline auto ByteArray::operator +=(char character) noexcept -> ByteArray &
{
    return append(character);
}

inline auto ByteArray::operator +=(std::initializer_list<char> data) noexcept -> ByteArray &
{
    return append(data);
}

inline auto ByteArray::append(const ByteArray &data) noexcept -> ByteArray &
{
    insert(std::end(*this), std::begin(data), std::end(data));

    return *this;
}

inline auto ByteArray::append(const char *data, sizeinfo size) noexcept -> ByteArray &
{
    insert(std::end(*this), data, std::next(data, size));

    return *this;
}

inline auto ByteArray::append(const char *data) noexcept -> ByteArray &
{
    return append(data, std::char_traits<char>::length(data));
}

inline auto ByteArray::append(char character) noexcept -> ByteArray &
{
    emplace_back(character);

    return *this;
}

inline auto ByteArray::append(std::initializer_list<char> data) noexcept -> ByteArray &
{
    insert(std::end(*this), std::begin(data), std::end(data));

    return *this;
}

/*!
 *  Non-member operators
 */
inline auto operator +(const ByteArray &left, const ByteArray &right) noexcept -> ByteArray
{
    ByteArray data { left };
    data += right;

    return data;
}


inline auto operator +(ByteArray &&left, ByteArray &&right) noexcept -> ByteArray
{
    ByteArray data { std::move(left) };
    data += right;

    return data;
}

inline auto operator +(ByteArray &&left, const ByteArray &right) noexcept -> ByteArray
{
    ByteArray data { std::move(left) };
    data += right;

    return data;
}

inline auto operator +(const ByteArray &left, ByteArray &&right) noexcept -> ByteArray
{
    ByteArray data { std::move(right) };
    data.insert(std::begin(data), std::begin(left), std::end(left));

    return data;
}

inline auto operator +(const ByteArray &left, const char *right) noexcept -> ByteArray
{
    ByteArray data { left };
    data += right;

    return data;
}

inline auto operator +(ByteArray &&left, const char *right) noexcept -> ByteArray
{
    ByteArray data { std::move(left) };
    data += right;

    return data;
}

inline auto operator +(const char *left, const ByteArray &right) noexcept -> ByteArray
{
    ByteArray data { left };
    data += right;

    return data;
}

inline auto operator +(const char *left, ByteArray &&right) noexcept -> ByteArray
{
    ByteArray data { std::move(right) };
    data.insert(std::begin(data), left, std::next(left, std::char_traits<char>::length(left)));

    return data;
}

inline auto operator +(const ByteArray &left, char right) noexcept -> ByteArray
{
    ByteArray data { left };
    data += right;

    return data;
}

inline auto operator +(ByteArray &&left, char right) noexcept -> ByteArray
{
    ByteArray data { std::move(left) };
    data += right;

    return data;
}

inline auto operator +(char left, const ByteArray &right) noexcept -> ByteArray
{
    ByteArray data { right };
    data.insert(std::begin(data), left);

    return data;
}

inline auto operator +(char left, ByteArray &&right) noexcept -> ByteArray
{
    ByteArray data { std::move(right) };
    data.insert(std::begin(data), left);

    return data;
}

inline auto operator <<(std::ostream &stream, const ByteArray &data) noexcept -> std::ostream &
{
    std::copy(std::begin(data), std::end(data), std::ostreambuf_iterator<char>(stream));

    return stream;
}

} // end namespace Tools

using Tools::ByteArray;

} // end namespace Calibri

#endif // CALIBRI_TOOLS_BYTEARRAY_HPP
