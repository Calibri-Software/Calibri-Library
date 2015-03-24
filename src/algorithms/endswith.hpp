#ifndef CALIBRI_ALGORITHMS_ENDSWITH_HPP
#define CALIBRI_ALGORITHMS_ENDSWITH_HPP

// Std includes
#include <type_traits>

// Calibri-Library includes
#include "tools/bytearray.hpp"

namespace Calibri {

namespace Algorithms {

template<typename DataType,
         typename std::enable_if<(std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)>::type * = nullptr>
inline auto endsWith(const DataType &data, const DataType &sector) noexcept -> bool
{
    if (sector.size() > data.size())
        return false;

    return std::equal(data.crbegin(), std::next(data.crbegin(), sector.size()), sector.crbegin());
}

} // end namespace Algorithms

using Algorithms::endsWith;

} // end namespace Calibri

#endif // CALIBRI_ALGORITHMS_ENDSWITH_HPP
