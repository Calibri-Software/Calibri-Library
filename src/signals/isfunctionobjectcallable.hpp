#ifndef CALIBRI_SIGNALS_ISFUNCTIONOBJECTCALLABLE_HPP
#define CALIBRI_SIGNALS_ISFUNCTIONOBJECTCALLABLE_HPP

//! Calibri-Library includes
#include "iscallable.hpp"
#include "tools/disableconstructible.hpp"

namespace Calibri {

namespace Signals {

namespace Internal {

/*!
 *  IsFunctionObjectCallable class
 */
template<typename FunctionObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
class IsFunctionObjectCallable : private DisableConstructible
{
public:
    static constexpr auto value = (std::is_same<std::true_type, decltype(isCallable<FunctionObjectType, ReturnType, ArgumentsType ...>(FunctionOrFunctionObjectCase()))>::value
                                   && std::is_class<FunctionObjectType>::value);
};

} // end namespace Internal

} // end namespace Signals

} // end namespace Calibri

#endif // CALIBRI_SIGNALS_ISFUNCTIONOBJECTCALLABLE_HPP
