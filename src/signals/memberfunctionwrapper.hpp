#ifndef CALIBRI_SIGNALS_MEMBERFUNCTIONWRAPPER_HPP
#define CALIBRI_SIGNALS_MEMBERFUNCTIONWRAPPER_HPP

//! Calibri-Library includes
#include "tools/disableconstructible.hpp"

namespace Calibri {

namespace Signals {

namespace Internal {

//! Aliases
template<typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
using MemberFunction = ReturnType (ClassType::*)(ArgumentsType ...);

template<typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
using ConstMemberFunction = ReturnType (ClassType::*)(ArgumentsType ...) const;

/*!
 *  MemberFunction class
 */
template<typename ...>
class MemberFunctionWrapper : private DisableConstructible
{
};

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
class MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>
{
public:
    constexpr MemberFunctionWrapper(ObjectType *object, MemberFunction<ReturnType, ObjectType, ArgumentsType ...> memberFunction) noexcept;

    auto object() const noexcept -> ObjectType *;
    auto memberFunction() const noexcept -> const MemberFunction<ReturnType, ObjectType, ArgumentsType ...> &;

    auto operator ()(ArgumentsType &&...arguments) const -> ReturnType;
    auto operator ==(const MemberFunctionWrapper &other) const noexcept -> bool;
    auto operator !=(const MemberFunctionWrapper &other) const noexcept -> bool;

private:
    MemberFunction<ReturnType, ObjectType, ArgumentsType ...> m_memberFunction {};

    ObjectType *m_object {};
};

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
class MemberFunctionWrapper<ConstMemberFunction<ReturnType, ObjectType, ArgumentsType ...>>
{
public:
    constexpr MemberFunctionWrapper(ObjectType *object, ConstMemberFunction<ReturnType, ObjectType, ArgumentsType ...> memberFunction) noexcept;

    auto object() const noexcept -> ObjectType *;
    auto memberFunction() const noexcept -> const ConstMemberFunction<ReturnType, ObjectType, ArgumentsType ...> &;

    auto operator ()(ArgumentsType &&...arguments) const -> ReturnType;
    auto operator ==(const MemberFunctionWrapper &other) const noexcept -> bool;
    auto operator !=(const MemberFunctionWrapper &other) const noexcept -> bool;

private:
    ConstMemberFunction<ReturnType, ObjectType, ArgumentsType ...> m_memberFunction {};

    ObjectType *m_object {};
};

/*!
 *  MemberFunction inline methods
 */
template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline constexpr MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::
MemberFunctionWrapper(ObjectType *object, MemberFunction<ReturnType, ObjectType, ArgumentsType ...> memberFunction) noexcept :
    m_memberFunction { memberFunction },
    m_object { object }
{
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::object() const noexcept -> ObjectType *
{
    return m_object;
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::
memberFunction() const noexcept -> const MemberFunction<ReturnType, ObjectType, ArgumentsType ...> &
{
    return m_memberFunction;
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::operator ()(ArgumentsType &&...arguments) const -> ReturnType
{
    return (m_object->*m_memberFunction)(std::forward<ArgumentsType>(arguments) ...);
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::operator ==(const MemberFunctionWrapper &other) const noexcept -> bool
{
    return m_object == other.m_object && m_memberFunction == other.m_memberFunction;
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::operator !=(const MemberFunctionWrapper &other) const noexcept -> bool
{
    return m_object != other.m_object || m_memberFunction != other.m_memberFunction;
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline constexpr MemberFunctionWrapper<ConstMemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::
MemberFunctionWrapper(ObjectType *object, ConstMemberFunction<ReturnType, ObjectType, ArgumentsType ...> memberFunction) noexcept :
    m_memberFunction { memberFunction },
    m_object { object }
{
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<ConstMemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::object() const noexcept -> ObjectType *
{
    return m_object;
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<ConstMemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::
memberFunction() const noexcept -> const ConstMemberFunction<ReturnType, ObjectType, ArgumentsType ...> &
{
    return m_memberFunction;
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<ConstMemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::operator ()(ArgumentsType &&...arguments) const -> ReturnType
{
    return (m_object->*m_memberFunction)(std::forward<ArgumentsType>(arguments) ...);
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<ConstMemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::operator ==(const MemberFunctionWrapper &other) const noexcept -> bool
{
    return m_object == other.m_object && m_memberFunction == other.m_memberFunction;
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<ConstMemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::operator !=(const MemberFunctionWrapper &other) const noexcept -> bool
{
    return m_object != other.m_object || m_memberFunction != other.m_memberFunction;
}

} // end namespace Internal

} // end namespace Signals

} // end namespace Calibri

#endif // CALIBRI_SIGNALS_MEMBERFUNCTIONWRAPPER_HPP
