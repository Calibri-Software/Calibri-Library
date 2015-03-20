#ifndef CALIBRI_ALGORITHMS_SIMPLIFY_HPP
#define CALIBRI_ALGORITHMS_SIMPLIFY_HPP

// Calibri-Library includes
#include "trim.hpp"
#include "tools/bytearray.hpp"

namespace Calibri {

namespace Algorithms {

namespace Internal {

template<typename DataType,
         typename std::enable_if<std::is_same<DataType, char>::value>::type ...Enabler>
inline constexpr auto space() noexcept -> DataType
{
    return ' ';
}

template<typename DataType,
         typename std::enable_if<std::is_same<DataType, wchar>::value>::type ...Enabler>
inline constexpr auto space() noexcept -> DataType
{
    return L' ';
}

} // end namespace Internal

template<typename DataType,
         typename std::enable_if<(std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)>::type ...Enabler>
inline auto simplify(DataType &data) noexcept -> void
{
    using CharacterType = typename DataType::value_type;

    auto it = std::find_if_not(data.rbegin(), data.rend(), Internal::IsSpace()).base();

    if (it == std::begin(data)) {
        data.clear();

        return;
    }

    data.erase(it, std::end(data));

    it = std::find_if_not(std::begin(data), std::end(data), Internal::IsSpace());

    data.erase(std::begin(data), it);

    auto from = std::find_if(std::begin(data), std::end(data), Internal::IsSpace());

    if (from == std::end(data))
        return;

    auto to = std::find_if_not(from, std::end(data), Internal::IsSpace());

    it = std::next(data.insert(data.erase(from, to), Internal::space<CharacterType>()));

    do {
        from = std::find_if(it, std::end(data), Internal::IsSpace());

        if (from == std::end(data))
            break;

        to = std::find_if_not(from, std::end(data), Internal::IsSpace());

        it = std::next(data.insert(data.erase(from, to), Internal::space<CharacterType>()));
    } while (true);
}

} // end namespace Algorithms

using Algorithms::simplify;

} // end namespace Calibri

#endif // CALIBRI_ALGORITHMS_SIMPLIFY_HPP
