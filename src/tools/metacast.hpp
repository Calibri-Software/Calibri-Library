#ifndef CALIBRI_TOOLS_METACAST_HPP
#define CALIBRI_TOOLS_METACAST_HPP

// Std includes
#include <string>
#include <cstring>
#include <limits>
#include <vector>

// Calibri-Library includes
#include "global/types.hpp"
#include "global/compilerdetection.hpp"
#include "algorithms/startswith.hpp"

namespace Calibri {

namespace Tools {

namespace Internal {

template<typename DataType,
         typename std::enable_if<std::is_same<DataType, char>::value>::type * = nullptr>
inline constexpr auto minus() noexcept -> DataType
{
    return '-';
}

template<typename DataType,
         typename std::enable_if<std::is_same<DataType, wchar>::value>::type * = nullptr>
inline constexpr auto minus() noexcept -> DataType
{
    return L'-';
}

} // end namespace Internal

// Convert convertible types
template<typename CastType,
         typename DataType,
         typename std::enable_if<std::is_convertible<DataType, CastType>::value>::type * = nullptr>
inline auto metaCast(DataType data) noexcept -> CastType
{
    return static_cast<CastType>(data);
}

// Convert string/wstring to arithmetic types
template<typename CastType,
         uint8 Base = 10,
         typename DataType,
         typename std::enable_if<(std::is_same<CastType, int8>::value
                                 || std::is_same<CastType, int16>::value)
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value)>::type * = nullptr>
inline auto metaCast(const DataType &data, bool *ok = nullptr) noexcept -> CastType
{
    try {
        sizeinfo index {};

        auto castedData = std::stol(data, &index, Base);

        if (index != data.size()) {
            if (ok)
                *ok = false;

            return {};
        }

        if (castedData > std::numeric_limits<CastType>::max() || castedData < std::numeric_limits<CastType>::min()) {
            if (ok)
                *ok = false;

            return {};
        }

        if (ok)
            *ok = true;

        return metaCast<CastType>(castedData);
    } catch (const std::exception &) {
        if (ok)
            *ok = false;

        return {};
    }
}

template<typename CastType,
         uint8 Base = 10,
         typename DataType,
         typename std::enable_if<std::is_same<CastType, int32>::value
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value)>::type * = nullptr>
inline auto metaCast(const DataType &data, bool *ok = nullptr) noexcept -> CastType
{
    try {
        sizeinfo index {};

        auto castedData = std::stol(data, &index, Base);

        if (index != data.size()) {
            if (ok)
                *ok = false;

            return {};
        }

        if (ok)
            *ok = true;

        return castedData;
    } catch (const std::exception &) {
        if (ok)
            *ok = false;

        return {};
    }
}

template<typename CastType,
         uint8 Base = 10,
         typename DataType,
         typename std::enable_if<std::is_same<CastType, int64>::value
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value)>::type * = nullptr>
inline auto metaCast(const DataType &data, bool *ok = nullptr) noexcept -> CastType
{
    try {
        sizeinfo index {};

        auto castedData = std::stoll(data, &index, Base);

        if (index != data.size()) {
            if (ok)
                *ok = false;

            return {};
        }

        if (ok)
            *ok = true;

        return castedData;
    } catch (const std::exception &) {
        if (ok)
            *ok = false;

        return {};
    }
}

template<typename CastType,
         uint8 Base = 10,
         typename DataType,
         typename std::enable_if<(std::is_same<CastType, uint8>::value
                                 || std::is_same<CastType, uint16>::value)
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value)>::type * = nullptr>
inline auto metaCast(const DataType &data, bool *ok = nullptr) noexcept -> CastType
{
    try {
        sizeinfo index {};

        auto castedData = std::stoul(data, &index, Base);

        if (index != data.size()) {
            if (ok)
                *ok = false;

            return {};
        }

        if (castedData > std::numeric_limits<CastType>::max()) {
            if (ok)
                *ok = false;

            return {};
        }

        if (ok)
            *ok = true;

        return metaCast<CastType>(castedData);
    } catch (const std::exception &) {
        if (ok)
            *ok = false;

        return {};
    }
}

template<typename CastType,
         uint8 Base = 10,
         typename DataType,
         typename ValueType = typename DataType::value_type,
         typename std::enable_if<std::is_same<CastType, uint32>::value
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value)>::type * = nullptr>
inline auto metaCast(const DataType &data, bool *ok = nullptr) noexcept -> CastType
{
    try {
        if (startsWith(data, DataType(1, Internal::minus<ValueType>()))) {
            if (ok)
                *ok = false;

            return {};
        }

        sizeinfo index {};

        auto castedData = std::stoul(data, &index, Base);

        if (index != data.size()) {
            if (ok)
                *ok = false;

            return {};
        }

        if (ok)
            *ok = true;

        return castedData;
    } catch (const std::exception &) {
        if (ok)
            *ok = false;

        return {};
    }
}

template<typename CastType,
         uint8 Base = 10,
         typename DataType,
         typename ValueType = typename DataType::value_type,
         typename std::enable_if<std::is_same<CastType, uint64>::value
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value)>::type * = nullptr>
inline auto metaCast(const DataType &data, bool *ok = nullptr) noexcept -> CastType
{
    try {
        if (startsWith(data, DataType(1, Internal::minus<ValueType>()))) {
            if (ok)
                *ok = false;

            return {};
        }

        sizeinfo index {};

        auto castedData = std::stoull(data, &index, Base);

        if (index != data.size()) {
            if (ok)
                *ok = false;

            return {};
        }

        if (ok)
            *ok = true;

        return castedData;
    } catch (const std::exception &) {
        if (ok)
            *ok = false;

        return {};
    }
}

template<typename CastType,
         typename DataType,
         typename std::enable_if<std::is_same<CastType, float>::value
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value)>::type * = nullptr>
inline auto metaCast(const DataType &data, bool *ok = nullptr) noexcept -> CastType
{
    try {
        sizeinfo index {};

        auto castedData = std::stof(data, &index);

        if (index != data.size()) {
            if (ok)
                *ok = false;

            return {};
        }

        if (ok)
            *ok = true;

        return castedData;
    } catch (const std::exception &) {
        if (ok)
            *ok = false;

        return {};
    }
}

template<typename CastType,
         typename DataType,
         typename std::enable_if<std::is_same<CastType, double>::value
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value)>::type * = nullptr>
inline auto metaCast(const DataType &data, bool *ok = nullptr) noexcept -> CastType
{
    try {
        sizeinfo index {};

        auto castedData = std::stod(data, &index);

        if (index != data.size()) {
            if (ok)
                *ok = false;

            return {};
        }

        if (ok)
            *ok = true;

        return castedData;
    } catch (const std::exception &) {
        if (ok)
            *ok = false;

        return {};
    }
}

template<typename CastType,
         typename DataType,
         typename std::enable_if<std::is_same<CastType, longdouble>::value
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value)>::type * = nullptr>
inline auto metaCast(const DataType &data, bool *ok = nullptr) noexcept -> CastType
{
    try {
        sizeinfo index {};

        auto castedData = std::stold(data, &index);

        if (index != data.size()) {
            if (ok)
                *ok = false;

            return {};
        }

        if (ok)
            *ok = true;

        return castedData;
    } catch (const std::exception &) {
        if (ok)
            *ok = false;

        return {};
    }
}

// Convert arithmetic types to string
template<typename CastType,
         typename DataType,
         typename std::enable_if<(std::is_same<CastType, std::string>::value
                                 && std::is_arithmetic<DataType>::value)>::type * = nullptr>
inline auto metaCast(DataType data, bool *ok = nullptr) noexcept -> CastType
{
    try {
        auto castedData = std::to_string(data);

        if (ok)
            *ok = true;

        return castedData;
    } catch (const std::exception &) {
        if (ok)
            *ok = false;

        return {};
    }
}

// Convert arithmetic types to wstring
template<typename CastType,
         typename DataType,
         typename std::enable_if<(std::is_same<CastType, std::wstring>::value
                                 && std::is_arithmetic<DataType>::value)>::type * = nullptr>
inline auto metaCast(DataType data, bool *ok = nullptr) noexcept -> CastType
{
    try {
        auto castedData = std::to_wstring(data);

        if (ok)
            *ok = true;

        return castedData;
    } catch (const std::exception &) {
        if (ok)
            *ok = false;

        return {};
    }
}

// Convert byte string to wstring
template<typename CastType,
         typename std::enable_if<std::is_same<CastType, std::wstring>::value>::type * = nullptr>
inline auto metaCast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    errno = 0;

    auto buffer = std::vector<wchar>(std::char_traits<char>::length(data));

    auto state = std::mbstate_t();

    auto size = std::mbsrtowcs(buffer.data(), &data, buffer.size(), &state);

    switch (errno) {
    case EILSEQ:
        if (ok)
            *ok = false;

        return {};

    default:
        break;
    }

    if (ok)
        *ok = true;

    return { buffer.data(), size };
}

// Convert wide string to string
template<typename CastType,
         typename std::enable_if<std::is_same<CastType, std::string>::value>::type * = nullptr>
inline auto metaCast(const wchar *data, bool *ok = nullptr) noexcept -> CastType
{
    errno = 0;

    auto buffer = std::vector<char>(std::char_traits<wchar>::length(data) * MB_CUR_MAX);

    auto state = std::mbstate_t();

    auto size = std::wcsrtombs(buffer.data(), &data, buffer.size(), &state);

    switch (errno) {
    case EILSEQ:
        if (ok)
            *ok = false;

        return {};

    default:
        break;
    }

    if (ok)
        *ok = true;

    return { buffer.data(), size };
}

// Convert string to wstring
template<typename CastType,
         typename std::enable_if<std::is_same<CastType, std::wstring>::value>::type * = nullptr>
inline auto metaCast(const std::string &data, bool *ok = nullptr) noexcept -> CastType
{
    return metaCast<CastType>(data.data(), ok);
}

// Convert wstring to string
template<typename CastType,
         typename std::enable_if<std::is_same<CastType, std::string>::value>::type * = nullptr>
inline auto metaCast(const std::wstring &data, bool *ok = nullptr) noexcept -> CastType
{
    return metaCast<CastType>(data.data(), ok);
}

} // end namespace Tools

using Tools::metaCast;

} // end namespace Calibri

#endif // CALIBRI_TOOLS_METACAST_HPP
