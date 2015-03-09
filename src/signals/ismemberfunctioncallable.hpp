#ifndef CALIBRI_SIGNALS_ISMEMBERFUNCTIONCALLABLE_HPP
#define CALIBRI_SIGNALS_ISMEMBERFUNCTIONCALLABLE_HPP

//! Calibri-Library includes
#include "iscallable.hpp"
#include "tools/disableconstructible.hpp"

namespace Calibri {

namespace Signals {

namespace Internal {

/*!
 *  IsMemberFunctionCallable class
 */
template<typename MemberFunctionType,
         typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
class IsMemberFunctionCallable : private DisableConstructible
{
public:
    static constexpr auto value = (std::is_same<std::true_type, decltype(isCallable<MemberFunctionType, ReturnType, ClassType, ArgumentsType ...>(MemberFunctionCase()))>::value
                                   && std::is_member_function_pointer<MemberFunctionType>::value);
};

} // end namespace Internal

} // end namespace Signals

} // end namespace Calibri

#endif // CALIBRI_SIGNALS_ISMEMBERFUNCTIONCALLABLE_HPP
