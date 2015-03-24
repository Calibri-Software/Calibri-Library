#ifndef CALIBRI_ALGORITHMS_JOIN_HPP
#define CALIBRI_ALGORITHMS_JOIN_HPP

// Std includes
#include <deque>
#include <forward_list>
#include <list>

// Calibri-Library includes
#include "tools/bytearray.hpp"

namespace Calibri {

namespace Algorithms {

template<typename ContainerType,
         typename DataType,
         typename PredicateType,
         typename std::enable_if<((std::is_same<ContainerType, std::vector<DataType>>::value
                                 || std::is_same<ContainerType, std::deque<DataType>>::value
                                 || std::is_same<ContainerType, std::forward_list<DataType>>::value
                                 || std::is_same<ContainerType, std::list<DataType>>::value)
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)
                                 && std::is_convertible<typename std::result_of<PredicateType(DataType)>::type, bool>::value)>::type * = nullptr>
inline auto join(DataType &data, const ContainerType &container, const DataType &separator, PredicateType predicate) noexcept -> void
{
    data.clear();

    auto it = std::begin(container);

    if (it == std::end(container))
        return;

    while (!predicate(*it))
        ++it;

    data.append(*(it++));

    for (auto end = std::end(container); it != end; ++it) {
        if (predicate(*it))
            data.append(separator + *it);
    }
}

template<typename ContainerType,
         typename DataType,
         typename std::enable_if<((std::is_same<ContainerType, std::vector<DataType>>::value
                                 || std::is_same<ContainerType, std::deque<DataType>>::value
                                 || std::is_same<ContainerType, std::forward_list<DataType>>::value
                                 || std::is_same<ContainerType, std::list<DataType>>::value)
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value))>::type * = nullptr>
inline auto join(DataType &data, const ContainerType &container, const DataType &separator) noexcept -> void
{
    data.clear();

    auto it = std::begin(container);

    if (it == std::end(container))
        return;

    data.append(*(it++));

    for (auto end = std::end(container); it != end; ++it)
        data.append(separator + *it);
}

} // end namespace Algorithms

using Algorithms::join;

} // end namespace Calibri

#endif // CALIBRI_ALGORITHMS_JOIN_HPP
