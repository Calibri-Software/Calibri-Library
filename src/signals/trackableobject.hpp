#ifndef CALIBRI_SIGNALS_TRACKABLEOBJECT_HPP
#define CALIBRI_SIGNALS_TRACKABLEOBJECT_HPP

// Std includes
#include <mutex>
#include <vector>
#include <algorithm>

// Calibri-Library includes
#include "thread/spinlock.hpp"

namespace Calibri {

namespace Signals {

namespace Internal {

// Forward declarations
class TrackableObject;

// SignalObserver class
class TrackableObjectObserver
{
public:
    // Controls
    virtual auto destroyed(TrackableObject *trackableObject) noexcept -> void = 0;
};

// SignalTrackableObject class
class TrackableObject
{
public:
    virtual ~TrackableObject() noexcept;

    // Controls
    auto connected(TrackableObjectObserver *observer) noexcept -> void;
    auto disconnected(TrackableObjectObserver *observer) noexcept -> bool;

private:
    std::vector<std::pair<TrackableObjectObserver *, uint32>> m_observers {};
    SpinLock m_context {};
};

// SignalTrackableObject inline methods
inline TrackableObject::~TrackableObject() noexcept
{
    std::lock_guard<SpinLock> locker { m_context };

    for (const auto &item : m_observers)
        (item.first)->destroyed(this);
}

inline auto TrackableObject::connected(TrackableObjectObserver *observer) noexcept -> void
{
    std::lock_guard<SpinLock> locker { m_context };

    auto it = std::find_if(std::begin(m_observers), std::end(m_observers), [ observer ](const std::pair<TrackableObjectObserver *, uint32> &item) noexcept {
        return item.first == observer;
    });

    if (it != std::end(m_observers))
        ++((*it).second);
    else
        m_observers.emplace_back(std::piecewise_construct, std::forward_as_tuple(observer), std::forward_as_tuple(1));
}

inline auto TrackableObject::disconnected(TrackableObjectObserver *observer) noexcept -> bool
{
    std::lock_guard<SpinLock> locker { m_context };

    auto it = std::find_if(std::begin(m_observers), std::end(m_observers), [ observer ](const std::pair<TrackableObjectObserver *, uint32> &item) noexcept {
        return item.first == observer;
    });

    if (it != std::end(m_observers)) {
        if (--((*it).second) == 0)
            m_observers.erase(it);

        return true;
    }

    return false;
}

} // end namespace Internal

} // end namespace Signals

} // end namespace Calibri

#endif // CALIBRI_SIGNALS_TRACKABLEOBJECT_HPP
