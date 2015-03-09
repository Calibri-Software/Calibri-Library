#ifndef CALIBRI_SIGNALS_ISCALLABLE_HPP
#define CALIBRI_SIGNALS_ISCALLABLE_HPP

//! Std includes
#include <type_traits>

namespace Calibri {

namespace Signals {

namespace Internal {

/*!
 *  FunctionPointerOrFunctionObjectCase class
 */
class FunctionOrFunctionObjectCase
{
};

/*!
 *  MemberFunctionPointerCase class
 */
class MemberFunctionCase
{
};

template<typename CallableType,
         typename ReturnType,
         typename ...ArgumentsType,
         typename std::enable_if<std::is_convertible<typename std::result_of<CallableType(ArgumentsType ...)>::type, ReturnType>::value>::type ...Enabler>
constexpr auto isCallable(FunctionOrFunctionObjectCase) noexcept -> std::true_type;

template<typename CallableType,
         typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType,
         typename std::enable_if<std::is_convertible<typename std::result_of<CallableType(ClassType, ArgumentsType ...)>::type, ReturnType>::value>::type ...Enabler>
constexpr auto isCallable(MemberFunctionCase) noexcept -> std::true_type;

template<typename ...>
constexpr auto isCallable(...) noexcept -> std::false_type;

} // end namespace Internal

} // end namespace Signals

} // end namespace Calibri

#endif // CALIBRI_SIGNALS_ISCALLABLE_HPP
