#ifndef CALIBRI_SIGNALS_CONNECTION_HPP
#define CALIBRI_SIGNALS_CONNECTION_HPP

//! Std includes
#include <mutex>

//! Calibri-Library includes
#include "enablesignal.hpp"
#include "memberfunctionwrapper.hpp"
#include "issignalcallable.hpp"
#include "isfunctioncallable.hpp"
#include "isfunctionobjectcallable.hpp"
#include "ismemberfunctioncallable.hpp"
#include "tools/disableconstructible.hpp"
#include "thread/spinlock.hpp"

namespace Calibri {

namespace Signals {

namespace Variables {

static SpinLock globalContext {};

} // end namespace Variables

namespace Internal {

//! Aliases
template<typename ReturnType,
         typename ...ArgumentsType>
using Function = ReturnType (ArgumentsType ...);

/*!
 *  Connection class
 */
template<typename ...>
class Connection : private DisableConstructible
{
};

template<typename ReturnType,
         typename ...ArgumentsType>
class Connection<Function<ReturnType, ArgumentsType ...>> : private DisableCopyable
{
    using Invoker = ReturnType (*)(void *, ArgumentsType &&...) noexcept;
    using Deleter = void (*)(void *) noexcept;
    using Comparator = bool (*)(void *, void *) noexcept;

public:
    template<typename CallableType,
             typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    Connection(CallableType *callable) noexcept;

    template<typename CallableType,
             typename std::enable_if<Internal::IsFunctionObjectCallable<typename std::decay<CallableType>::type, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    Connection(CallableType &&callable) noexcept;

    template<typename CallableType,
             typename std::enable_if<Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    Connection(CallableType callable) noexcept;

    template<typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignal, ObjectType>::value)>::type ...Enabler>
    Connection(ObjectType *object, CallableType callable) noexcept;

    virtual ~Connection() noexcept;

    auto operator !=(const Connection &other) const noexcept -> bool;
    auto operator ==(const Connection &other) const noexcept -> bool;
    auto operator ()(ArgumentsType &&...arguments) const noexcept -> ReturnType;

    template<typename CallableType>
    auto isConnectedTo(CallableType *callable) const noexcept -> bool;

    template<typename ObjectType,
             typename CallableReturnType,
             typename ...CallableArgumentsType>
    auto isConnectedTo(ObjectType *object, MemberFunction<CallableReturnType, ObjectType, CallableArgumentsType ...> memberFunction) const noexcept -> bool;

    template<typename ObjectType,
             typename CallableReturnType,
             typename ...CallableArgumentsType>
    auto isConnectedTo(ObjectType *object, ConstMemberFunction<CallableReturnType, ObjectType, CallableArgumentsType ...> memberFunction) const noexcept -> bool;

private:
    void *m_callable {};

    Invoker m_invoker {};
    Deleter m_deleter {};
    Comparator m_comparator {};
};

/*!
 *  Connection inline methods
 */
template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline Connection<Function<ReturnType, ArgumentsType ...>>::Connection(CallableType *callable) noexcept
{
    using SignalType = CallableType;

    m_callable = reinterpret_cast<decltype(m_callable)>(callable);
    m_invoker = [](void *callable, ArgumentsType &&...arguments) noexcept -> ReturnType {
        return (*reinterpret_cast<SignalType *>(callable))(std::forward<ArgumentsType>(arguments) ...);
    };
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsFunctionObjectCallable<typename std::decay<CallableType>::type, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline Connection<Function<ReturnType, ArgumentsType ...>>::Connection(CallableType &&callable) noexcept
{
    using FunctionObjectType = typename std::decay<CallableType>::type;

    m_callable = new FunctionObjectType(std::forward<CallableType>(callable));
    m_invoker = [](void *callable, ArgumentsType &&...arguments) noexcept -> ReturnType {
        std::lock_guard<SpinLock> locker { Variables::globalContext };

        return (*reinterpret_cast<FunctionObjectType *>(callable))(std::forward<ArgumentsType>(arguments) ...);
    };
    m_deleter = [](void *callable) noexcept {
        delete reinterpret_cast<FunctionObjectType *>(callable);
    };
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline Connection<Function<ReturnType, ArgumentsType ...>>::Connection(CallableType callable) noexcept
{
    using FunctionType = CallableType;

    m_callable = reinterpret_cast<decltype(m_callable)>(callable);
    m_invoker = [](void *callable, ArgumentsType &&...arguments) noexcept -> ReturnType {
        std::lock_guard<SpinLock> locker { Variables::globalContext };

        return reinterpret_cast<FunctionType>(callable)(std::forward<ArgumentsType>(arguments) ...);
    };
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignal, ObjectType>::value)>::type ...Enabler>
inline Connection<Function<ReturnType, ArgumentsType ...>>::Connection(ObjectType *object, CallableType callable) noexcept
{
    using MemberFunctionType = Internal::MemberFunctionWrapper<CallableType>;

    m_callable = new MemberFunctionType(object, callable);
    m_invoker = [](void *callable, ArgumentsType &&...arguments) noexcept -> ReturnType {
        std::lock_guard<SpinLock> locker { reinterpret_cast<MemberFunctionType *>(callable)->object()->context() };

        return (*reinterpret_cast<MemberFunctionType *>(callable))(std::forward<ArgumentsType>(arguments) ...);
    };
    m_deleter = [](void *callable) noexcept {
        delete reinterpret_cast<MemberFunctionType *>(callable);
    };
    m_comparator = [](void *thisCallable, void *otherCallable) noexcept -> bool {
        return (*reinterpret_cast<MemberFunctionType *>(thisCallable)) == (*reinterpret_cast<MemberFunctionType *>(otherCallable));
    };
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline Connection<Function<ReturnType, ArgumentsType ...>>::~Connection() noexcept
{
    if (m_deleter)
        m_deleter(m_callable);
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto Connection<Function<ReturnType, ArgumentsType ...>>::operator !=(const Connection &other) const noexcept -> bool
{
    if (m_comparator)
        return !m_comparator(m_callable, other.m_callable);

    return m_callable != other.m_callable;
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto Connection<Function<ReturnType, ArgumentsType ...>>::operator ==(const Connection &other) const noexcept -> bool
{
    if (m_comparator)
        return m_comparator(m_callable, other.m_callable);

    return m_callable == other.m_callable;
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto Connection<Function<ReturnType, ArgumentsType ...>>::operator ()(ArgumentsType &&...arguments) const noexcept -> ReturnType
{
    return m_invoker(m_callable, std::forward<ArgumentsType>(arguments) ...);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType>
inline auto Connection<Function<ReturnType, ArgumentsType ...>>::isConnectedTo(CallableType *callable) const noexcept -> bool
{
    return m_callable == callable;
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename ObjectType,
         typename CallableReturnType,
         typename ...CallableArgumentsType>
inline auto Connection<Function<ReturnType, ArgumentsType ...>>::
isConnectedTo(ObjectType *object, MemberFunction<CallableReturnType, ObjectType, CallableArgumentsType ...> memberFunction) const noexcept -> bool
{
    if (m_comparator) {
        auto memberFunctionWrapper = Internal::MemberFunctionWrapper<decltype(memberFunction)>(object, memberFunction);

        return m_comparator(m_callable, reinterpret_cast<decltype(m_callable)>(&memberFunctionWrapper));
    }

    return false;
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename ObjectType,
         typename CallableReturnType,
         typename ...CallableArgumentsType>
inline auto Connection<Function<ReturnType, ArgumentsType ...>>::
isConnectedTo(ObjectType *object, ConstMemberFunction<CallableReturnType, ObjectType, CallableArgumentsType ...> memberFunction) const noexcept -> bool
{
    if (m_comparator) {
        auto memberFunctionWrapper = Internal::MemberFunctionWrapper<decltype(memberFunction)>(object, memberFunction);

        return m_comparator(m_callable, reinterpret_cast<decltype(m_callable)>(&memberFunctionWrapper));
    }

    return false;
}

} // end namespace Internal

} // end namespace Signals

} // end namespace Calibri

#endif // CALIBRI_SIGNALS_CONNECTION_HPP
