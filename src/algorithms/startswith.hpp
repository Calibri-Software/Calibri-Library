#ifndef CALIBRI_ALGORITHMS_STARTSWITH_HPP
#define CALIBRI_ALGORITHMS_STARTSWITH_HPP

// Std includes
#include <type_traits>

// Calibri-Library includes
#include "tools/bytearray.hpp"

namespace Calibri {

namespace Algorithms {

template<typename DataType,
         typename std::enable_if<(std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)>::type ...Enabler>
inline auto startsWith(const DataType &data, const DataType &sector) noexcept -> bool
{
    if (sector.size() > data.size())
        return false;

    return std::equal(std::begin(data), std::next(std::begin(data), sector.size()), std::begin(sector));
}

} // end namespace Algorithms

using Algorithms::startsWith;

} // end namespace Calibri

#endif // CALIBRI_ALGORITHMS_STARTSWITH_HPP
