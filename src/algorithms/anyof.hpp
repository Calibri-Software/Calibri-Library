#ifndef CALIBRI_ALGORITHMS_ANYOF_HPP
#define CALIBRI_ALGORITHMS_ANYOF_HPP

// Std includes
#include <type_traits>

// Calibri-Library includes
#include "tools/bytearray.hpp"

namespace Calibri {

namespace Algorithms {

namespace Internal {

// IsAnyOf class
template<typename DataType>
class IsAnyOf
{
public:
    IsAnyOf(const DataType &data) noexcept;
    IsAnyOf(DataType &&data) noexcept;

    // Operators
    auto operator ()(typename DataType::value_type character) const noexcept -> bool;

private:
    DataType m_data {};
};

// IsAnyOf inline methods
template<typename DataType>
inline IsAnyOf<DataType>::IsAnyOf(const DataType &data) noexcept :
    m_data { data }
{
}

template<typename DataType>
inline IsAnyOf<DataType>::IsAnyOf(DataType &&data) noexcept :
    m_data { std::move(data) }
{
}

template<typename DataType>
inline auto IsAnyOf<DataType>::operator ()(typename DataType::value_type character) const noexcept -> bool
{    
    return std::any_of(std::begin(m_data), std::end(m_data), [ character ](typename DataType::value_type value) noexcept {
        return character == value;
    });
}

} // end namespace Internal

template<typename DataType,
         typename std::enable_if<(std::is_same<typename std::decay<DataType>::type, std::string>::value
                                 || std::is_same<typename std::decay<DataType>::type, std::wstring>::value
                                 || std::is_same<typename std::decay<DataType>::type, ByteArray>::value)>::type * = nullptr>
inline auto anyOf(DataType &&data) noexcept -> Internal::IsAnyOf<typename std::decay<DataType>::type>
{
    return Internal::IsAnyOf<typename std::decay<DataType>::type>(std::forward<DataType>(data));
}

template<typename DataType,
         typename std::enable_if<(std::is_same<typename std::decay<DataType>::type, std::string>::value
                                 || std::is_same<typename std::decay<DataType>::type, std::wstring>::value
                                 || std::is_same<typename std::decay<DataType>::type, ByteArray>::value)>::type * = nullptr>
inline auto anyOf(const DataType &data, DataType &&characters) noexcept -> bool
{
    return std::any_of(std::begin(data), std::end(data), anyOf(std::forward<DataType>(characters)));
}

} // end namespace Algorithms

using Algorithms::anyOf;

} // end namespace Calibri

#endif // CALIBRI_ALGORITHMS_ANYOF_HPP
