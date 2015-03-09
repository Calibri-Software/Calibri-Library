#ifndef CALIBRI_SIGNALS_SIGNAL_HPP
#define CALIBRI_SIGNALS_SIGNAL_HPP

//! Std includes
#include <list>
#include <mutex>

//! Calibri-Library includes
#include "connection.hpp"
#include "lastvalue.hpp"
#include "global/compilerdetection.hpp"

namespace Calibri {

namespace Signals {

//! Enumerations
enum class SignalConnectionMode : uint8 {
    DefaultConnection,
    UniqueConnection
};

/*!
 *  Signal class
 */
template<typename ...>
class Signal : private DisableConstructible
{
};

template<typename ReturnType,
         typename ...ArgumentsType>
class Signal<Internal::Function<ReturnType, ArgumentsType ...>> : private DisableCopyable, public Internal::TrackableObject, public Internal::TrackableObjectObserver
{
    //! Aliases
    using ConnectionType = Internal::Connection<Internal::Function<ReturnType, ArgumentsType ...>>;

public:
    virtual ~Signal() noexcept;

    template<typename MarshallerType,
             typename std::enable_if<(Internal::IsFunctionObjectCallable<typename std::decay<MarshallerType>::type, bool, ReturnType>::value
                                     && std::is_convertible<MarshallerType, ReturnType>::value)>::type ...Enabler>
    auto operator ()(MarshallerType &&marshaller, ArgumentsType &&...arguments) noexcept -> ReturnType;

    template<typename MarshallerType = Internal::LastValue<ReturnType>,
             typename std::enable_if<std::is_convertible<MarshallerType, ReturnType>::value>::type ...Enabler>
    auto operator ()(ArgumentsType &&...arguments) noexcept -> ReturnType;

    template<typename MarshallerType = Internal::LastValue<ReturnType>,
             typename std::enable_if<!std::is_convertible<MarshallerType, ReturnType>::value>::type ...Enabler>
    auto operator ()(ArgumentsType &&...arguments) noexcept -> ReturnType;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename CallableType,
             typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                     && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
    auto connect(CallableType *callable) noexcept -> ConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename CallableType,
             typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                     && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
    auto connect(CallableType *callable) noexcept -> ConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignal, ObjectType>::value
                                     && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
    auto connect(ObjectType *object, CallableType callable) noexcept -> ConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignal, ObjectType>::value
                                     && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
    auto connect(ObjectType *object, CallableType callable) noexcept -> ConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename CallableType,
             typename std::enable_if<(Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                     && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
    auto connect(CallableType callable) noexcept -> ConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename CallableType,
             typename std::enable_if<(Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                     && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
    auto connect(CallableType callable) noexcept -> ConnectionType *;

    template<typename CallableType,
             typename std::enable_if<Internal::IsFunctionObjectCallable<typename std::decay<CallableType>::type, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    auto connect(CallableType &&callable) noexcept -> ConnectionType *;

    template<typename CallableType,
             typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    auto disconnect(CallableType *callable) noexcept -> bool;

    template<typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignal, ObjectType>::value)>::type ...Enabler>
    auto disconnect(ObjectType *object, CallableType callable) noexcept -> bool;

    template<typename CallableType,
             typename std::enable_if<Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    auto disconnect(CallableType callable) noexcept -> bool;

    auto disconnect(ConnectionType *signalConnection) noexcept -> bool;

    auto disconnectAll() noexcept -> void;

    virtual auto destroyed(Internal::TrackableObject *trackableObject) noexcept -> void final;

private:
    std::list<std::pair<ConnectionType, Internal::TrackableObject *>> m_connections {};

    SpinLock m_context {};
};

/*!
 *  Signal inline methods
 */
template<typename ReturnType,
         typename ...ArgumentsType>
inline Signal<Internal::Function<ReturnType, ArgumentsType ...>>::~Signal() noexcept
{
    std::lock_guard<SpinLock> locker { m_context };

    for (const auto &item : m_connections) {
        if (item.second)
            item.second->disconnected(this);
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename MarshallerType,
         typename std::enable_if<(Internal::IsFunctionObjectCallable<typename std::decay<MarshallerType>::type, bool, ReturnType>::value
                                 && std::is_convertible<MarshallerType, ReturnType>::value)>::type ...Enabler>
auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::operator ()(MarshallerType &&marshaller, ArgumentsType &&...arguments) noexcept -> ReturnType
{
    std::lock_guard<SpinLock> locker { m_context };

    for (auto &item : m_connections) {
        if (marshaller((item.first)(std::forward<ArgumentsType>(arguments) ...)))
            break;
    }

    return marshaller;
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename MarshallerType,
         typename std::enable_if<std::is_convertible<MarshallerType, ReturnType>::value>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::operator ()(ArgumentsType &&...arguments) noexcept -> ReturnType
{
    return (*this)(MarshallerType(), std::forward<ArgumentsType>(arguments) ...);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename MarshallerType,
         typename std::enable_if<!std::is_convertible<MarshallerType, ReturnType>::value>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::operator ()(ArgumentsType &&...arguments) noexcept -> ReturnType
{
    std::lock_guard<SpinLock> locker { m_context };

    for (auto &item : m_connections)
        (item.first)(std::forward<ArgumentsType>(arguments) ...);

    return ReturnType();
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename CallableType,
         typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                 && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(CallableType *callable) noexcept -> ConnectionType *
{
    std::lock_guard<SpinLock> locker { m_context };

    auto it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(callable), std::forward_as_tuple(callable));

    callable->connected(this);

    return &((*it).first);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename CallableType,
         typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                 && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(CallableType *callable) noexcept -> ConnectionType *
{
    std::lock_guard<SpinLock> locker { m_context };

    auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ callable ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) noexcept {
        return item.first.isConnectedTo(callable);
    });

    if (it != std::end(m_connections))
        return nullptr;

    it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(callable), std::forward_as_tuple(callable));

    callable->connected(this);

    return &((*it).first);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignal, ObjectType>::value
                                 && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(ObjectType *object, CallableType callable) noexcept -> ConnectionType *
{
    std::lock_guard<SpinLock> locker { m_context };

    auto it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(object, callable), std::forward_as_tuple(object));

    object->connected(this);

    return &((*it).first);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignal, ObjectType>::value
                                 && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(ObjectType *object, CallableType callable) noexcept -> ConnectionType *
{
    std::lock_guard<SpinLock> locker { m_context };

    auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ object, &callable ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) noexcept {
        return item.first.isConnectedTo(object, callable);
    });

    if (it != std::end(m_connections))
        return nullptr;

    it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(object, callable), std::forward_as_tuple(object));

    object->connected(this);

    return &((*it).first);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename CallableType,
         typename std::enable_if<(Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                 && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(CallableType callable) noexcept -> ConnectionType *
{
    std::lock_guard<SpinLock> locker { m_context };

    auto it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(callable), std::forward_as_tuple(nullptr));

    return &((*it).first);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename CallableType,
         typename std::enable_if<(Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                 && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(CallableType callable) noexcept -> ConnectionType *
{
    std::lock_guard<SpinLock> locker { m_context };

    auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ callable ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) noexcept {
        return item.first.isConnectedTo(callable);
    });

    if (it != std::end(m_connections))
        return nullptr;

    it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(callable), std::forward_as_tuple(nullptr));

    return &((*it).first);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsFunctionObjectCallable<typename std::decay<CallableType>::type, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(CallableType &&callable) noexcept -> ConnectionType *
{
    std::lock_guard<SpinLock> locker { m_context };

    auto it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(std::forward<CallableType>(callable)), std::forward_as_tuple(nullptr));

    return &((*it).first);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::disconnect(CallableType *callable) noexcept -> bool
{
    std::lock_guard<SpinLock> locker { m_context };

    auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ callable ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) noexcept {
        return item.first.isConnectedTo(callable);
    });

    if (it != std::end(m_connections)) {
        ((*it).second)->disconnected(this);

        m_connections.erase(it);

        return true;
    }

    return false;
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignal, ObjectType>::value)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::disconnect(ObjectType *object, CallableType callable) noexcept -> bool
{
    std::lock_guard<SpinLock> locker { m_context };

    auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ object, &callable ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) noexcept {
        return item.first.isConnectedTo(object, callable);
    });

    if (it != std::end(m_connections)) {
        ((*it).second)->disconnected(this);

        m_connections.erase(it);

        return true;
    }

    return false;
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::disconnect(CallableType callable) noexcept -> bool
{
    std::lock_guard<SpinLock> locker { m_context };

    auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ callable ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) noexcept {
        return item.first.isConnectedTo(callable);
    });

    if (it != std::end(m_connections)) {
        m_connections.erase(it);

        return true;
    }

    return false;
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::disconnect(ConnectionType *signalConnection) noexcept -> bool
{
    std::lock_guard<SpinLock> locker { m_context };

    auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ signalConnection ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) noexcept {
        return &item.first == signalConnection;
    });

    if (it != std::end(m_connections)) {
        if ((*it).second)
            ((*it).second)->disconnected(this);

        m_connections.erase(it);

        return true;
    }

    return false;
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::disconnectAll() noexcept -> void
{
    std::lock_guard<SpinLock> locker { m_context };

    for (auto it = std::begin(m_connections); it != std::end(m_connections);) {
        if ((*it).second)
            (*it).second->disconnected(this);

        it = m_connections.erase(it);
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::destroyed(Internal::TrackableObject *trackableObject) noexcept -> void
{
    std::lock_guard<SpinLock> locker { m_context };

    m_connections.remove_if([ trackableObject ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) noexcept {
        return item.second == trackableObject;
    });
}

} // end namespace Signals

using Signals::SignalConnectionMode;
using Signals::Signal;

} // end namespace Calibri

#endif // CALIBRI_SIGNALS_SIGNAL_HPP
