#ifndef CALIBRI_ALGORITHMS_SPLIT_HPP
#define CALIBRI_ALGORITHMS_SPLIT_HPP

//! Std includes
#include <deque>
#include <forward_list>
#include <list>

//! Calibri-Library includes
#include "tools/bytearray.hpp"

namespace Calibri {

namespace Algorithms {

template<typename ContainerType,
         typename DataType,
         typename PredicateType,
         typename std::enable_if<((std::is_same<ContainerType, std::vector<DataType>>::value
                                 || std::is_same<ContainerType, std::deque<DataType>>::value
                                 || std::is_same<ContainerType, std::list<DataType>>::value)
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)
                                 && std::is_convertible<typename std::result_of<PredicateType(typename DataType::value_type)>::type, bool>::value)>::type ...Enabler>
inline auto split(ContainerType &container, const DataType &data, PredicateType predicate) noexcept -> void
{
    container.clear();

    auto from = std::find_if_not(std::begin(data), std::end(data), predicate);
    auto to = std::find_if(from, std::end(data), predicate);

    if (to == std::end(data)) {
        container.emplace_back(data);

        return;
    }

    container.emplace_back(from, to);

    do {
        from = std::find_if_not(to, std::end(data), predicate);

        if (from == std::end(data))
            break;

        to = std::find_if(from, std::end(data), predicate);

        container.emplace_back(from, to);

        if (to == std::end(data))
            break;
    } while (true);
}

template<typename ContainerType,
         typename DataType,
         typename PredicateType,
         typename std::enable_if<(std::is_same<ContainerType, std::forward_list<DataType>>::value
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)
                                 && std::is_convertible<typename std::result_of<PredicateType(typename DataType::value_type)>::type, bool>::value)>::type ...Enabler>
inline auto split(ContainerType &container, const DataType &data, PredicateType predicate) noexcept -> void
{
    container.clear();

    auto from = std::find_if_not(std::begin(data), std::end(data), predicate);
    auto to = std::find_if(from, std::end(data), predicate);

    if (to == std::end(data)) {
        container.emplace_after(container.cbefore_begin(), data);

        return;
    }

    auto it = container.emplace_after(container.cbefore_begin(), from, to);

    do {
        from = std::find_if_not(to, std::end(data), predicate);

        if (from == std::end(data))
            break;

        to = std::find_if(from, std::end(data), predicate);

        it = container.emplace_after(it, from, to);

        if (to == std::end(data))
            break;
    } while (true);
}

template<typename ContainerType,
         typename DataType,
         typename SeparatorType,
         typename std::enable_if<((std::is_same<ContainerType, std::vector<DataType>>::value
                                 || std::is_same<ContainerType, std::deque<DataType>>::value
                                 || std::is_same<ContainerType, std::forward_list<DataType>>::value
                                 || std::is_same<ContainerType, std::list<DataType>>::value)
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)
                                 && std::is_same<SeparatorType, typename DataType::value_type>::value)>::type ...Enabler>
inline auto split(ContainerType &container, const DataType &data, SeparatorType separator) noexcept -> void
{
    split(container, data, [ separator ](SeparatorType character) noexcept {
        return character == separator;
    });
}

template<typename ContainerType,
         typename DataType,
         typename std::enable_if<((std::is_same<ContainerType, std::vector<DataType>>::value
                                 || std::is_same<ContainerType, std::deque<DataType>>::value
                                 || std::is_same<ContainerType, std::list<DataType>>::value)
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value))>::type ...Enabler>
inline auto split(ContainerType &container, const DataType &data, const DataType &separator) noexcept -> void
{
    container.clear();

    auto from = std::begin(data);
    auto to = std::search(from, std::end(data), std::begin(separator), std::end(separator));

    if (to == std::end(data)) {
        container.emplace_back(data);

        return;
    }

    if (std::distance(from, to) != 0)
        container.emplace_back(from, to);

    do {
        from = std::next(to, separator.size());

        if (from == std::end(data))
            break;

        to = std::search(from, std::end(data), std::begin(separator), std::end(separator));

        if (std::distance(from, to) != 0)
            container.emplace_back(from, to);

        if (to == std::end(data))
            break;
    } while (true);
}

template<typename ContainerType,
         typename DataType,
         typename std::enable_if<(std::is_same<ContainerType, std::forward_list<DataType>>::value
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value))>::type ...Enabler>
inline auto split(ContainerType &container, const DataType &data, const DataType &separator) noexcept -> void
{
    container.clear();

    auto from = std::begin(data);
    auto to = std::search(from, std::end(data), std::begin(separator), std::end(separator));

    if (to == std::end(data)) {
        container.emplace_after(container.cbefore_begin(), data);

        return;
    }

    auto it = container.cbefore_begin();

    if (std::distance(from, to) != 0)
        it = container.emplace_after(it, from, to);

    do {
        from = std::next(to, separator.size());

        if (from == std::end(data))
            break;

        to = std::search(from, std::end(data), std::begin(separator), std::end(separator));

        if (std::distance(from ,to) != 0)
            it = container.emplace_after(it, from ,to);

        if (to == std::end(data))
            break;
    } while (true);
}

} // end namespace Algorithms

using Algorithms::split;

} // end namespace Calibri

#endif // CALIBRI_ALGORITHMS_SPLIT_HPP
