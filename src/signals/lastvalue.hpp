#ifndef CALIBRI_SIGNALS_LASTVALUE_HPP
#define CALIBRI_SIGNALS_LASTVALUE_HPP

//! Std includes
#include <utility>

namespace Calibri {

namespace Signals {

namespace Internal {

/*!
 *  LastValue class
 */
template<typename ValueType>
class LastValue
{
public:
    auto operator ()(ValueType &&value) noexcept -> bool;
    operator ValueType() const noexcept;

private:
    ValueType m_value {};
};

/*!
 *  LastValue inline methods
 */
template<typename ValueType>
inline auto LastValue<ValueType>::operator ()(ValueType &&value) noexcept -> bool
{
    m_value = std::forward<ValueType>(value);

    return false;
}

template<typename ValueType>
inline LastValue<ValueType>::operator ValueType() const noexcept
{
    return m_value;
}

} // end namespace Internal

} // end namespace Signals

} // end namespace Calibri

#endif // CALIBRI_SIGNALS_LASTVALUE_HPP
