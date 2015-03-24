#ifndef CALIBRI_ALGORITHMS_UPPER_HPP
#define CALIBRI_ALGORITHMS_UPPER_HPP

// Std includes
#include <type_traits>

// Calibri-Library includes
#include "tools/bytearray.hpp"

namespace Calibri {

namespace Algorithms {

namespace Internal {

// ToUpper class
class ToUpper
{
public:
    template<typename DataType>
    auto operator ()(DataType data) const noexcept -> DataType;

private:
    std::locale m_locale {};
};

// ToUpper inline methods
template<typename DataType>
inline auto ToUpper::operator ()(DataType data) const noexcept -> DataType
{
    return std::toupper(data, m_locale);
}

} // end namespace Internal

template<typename DataType,
         typename std::enable_if<(std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)>::type * = nullptr>
inline auto upper(DataType &data) noexcept -> void
{
    std::transform(std::begin(data), std::end(data), std::begin(data), Internal::ToUpper());
}

} // end namespace Algorithms

using Algorithms::upper;

} // end namespace Calibri

#endif // CALIBRI_ALGORITHMS_UPPER_HPP
