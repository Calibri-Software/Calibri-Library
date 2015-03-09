#ifndef CALIBRI_ALGORITHMS_TRIM_HPP
#define CALIBRI_ALGORITHMS_TRIM_HPP

//! Calibri-Library includes
#include "tools/bytearray.hpp"

namespace Calibri {

namespace Algorithms {

namespace Internal {

/*!
 *  IsSpace class
 */
class IsSpace
{
public:
    template<typename DataType>
    auto operator ()(DataType data) const noexcept -> bool;

private:
    std::locale m_locale {};
};

/*!
 *  IsSpace inline methods
 */
template<typename DataType>
inline auto IsSpace::operator ()(DataType data) const noexcept -> bool
{
    return std::isspace(data, m_locale);
}

} // end namespace Internal

template<typename DataType,
         typename std::enable_if<(std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)>::type ...Enabler>
inline auto trim(DataType &data) noexcept -> void
{
    auto it = std::find_if_not(std::begin(data), std::end(data), Internal::IsSpace());

    if (it == std::end(data)) {
        data.clear();

        return;
    }

    data.erase(std::begin(data), it);

    it = std::find_if_not(data.rbegin(), data.rend(), Internal::IsSpace()).base();

    data.erase(it, std::end(data));
}

} // end namespace Algorithms

using Algorithms::trim;

} // end namespace Calibri

#endif // CALIBRI_ALGORITHMS_TRIM_HPP
