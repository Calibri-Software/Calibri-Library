#ifndef CALIBRI_ALGORITHMS_LOWER_HPP
#define CALIBRI_ALGORITHMS_LOWER_HPP

// Std includes
#include <type_traits>

// Calibri-Library includes
#include "tools/bytearray.hpp"

namespace Calibri {

namespace Algorithms {

namespace Internal {

// ToLower class
class ToLower
{
public:
    // Operators
    template<typename DataType>
    auto operator ()(DataType data) const noexcept -> DataType;

private:
    std::locale m_locale {};
};

// ToLower inline methods
template<typename DataType>
inline auto ToLower::operator ()(DataType data) const noexcept -> DataType
{
    return std::tolower(data, m_locale);
}

} // end namespace Internal

template<typename DataType,
         typename std::enable_if<(std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)>::type * = nullptr>
inline auto lower(DataType &data) noexcept -> void
{
    std::transform(std::begin(data), std::end(data), std::begin(data), Internal::ToLower());
}

} // end namespace Algorithms

using Algorithms::lower;

} // end namespace Calibri

#endif // CALIBRI_ALGORITHMS_LOWER_HPP
