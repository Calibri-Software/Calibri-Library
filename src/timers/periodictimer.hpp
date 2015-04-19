#ifndef CALIBRI_TIMERS_PERIODICTIMER_HPP
#define CALIBRI_TIMERS_PERIODICTIMER_HPP

// Std includes
#include <mutex>

// Calibri-Library includes
#include "timermetric.hpp"
#include "tools/disablecopyable.hpp"
#include "thread/spinlock.hpp"

namespace Calibri {

namespace Timers {

namespace Internal {

// PeriodicTimerData class
class PeriodicTimerData : private DisableCopyable
{
public:
    // Getters
    auto period() noexcept -> uint64;
    auto isActive() noexcept -> bool;

    // Setters
    template<TimerMetric Metric = TimerMetric::Milliseconds>
    auto setPeriod(uint64 period) noexcept -> void;

    auto setActive(bool active) noexcept -> void;

    // Controls
    auto isPeriodic() noexcept -> bool;
    auto nextTimeoutPoint(const std::chrono::steady_clock::time_point &startPoint) noexcept -> void;
    auto nextTimeoutPoint() noexcept -> void;

    template<TimerMetric Metric = TimerMetric::Milliseconds>
    auto remaining() noexcept -> uint64;

    // Operators
    auto operator <(PeriodicTimerData &other) noexcept -> bool;

private:
    SpinLock m_context {};
    std::chrono::steady_clock::time_point m_timeoutPoint {};
    uint64 m_period {};
    bool m_active {};
    TimerMetric m_metric {};
};

// PeriodicTimerData inline methods
inline auto PeriodicTimerData::period() noexcept -> uint64
{
    std::lock_guard<SpinLock> locker { m_context };

    return m_period;
}

inline auto PeriodicTimerData::isActive() noexcept -> bool
{
    std::lock_guard<SpinLock> locker { m_context };

    return m_active;
}

template<TimerMetric Metric>
inline auto PeriodicTimerData::setPeriod(uint64 period) noexcept -> void
{
    std::lock_guard<SpinLock> locker { m_context };

    m_period = period;
    m_metric = Metric;
}

inline auto PeriodicTimerData::setActive(bool active) noexcept -> void
{
    std::lock_guard<SpinLock> locker { m_context };

    m_active = active;
}

inline auto PeriodicTimerData::isPeriodic() noexcept -> bool
{
    std::lock_guard<SpinLock> locker { m_context };

    return m_period > 0;
}

inline auto PeriodicTimerData::nextTimeoutPoint(const std::chrono::steady_clock::time_point &startPoint) noexcept -> void
{
    std::lock_guard<SpinLock> locker { m_context };

    if (m_period > 0) {
        switch (m_metric) {
        case TimerMetric::Hours:
            m_timeoutPoint = startPoint + std::chrono::hours(m_period);

            break;

        case TimerMetric::Minutes:
            m_timeoutPoint = startPoint + std::chrono::minutes(m_period);

            break;

        case TimerMetric::Seconds:
            m_timeoutPoint = startPoint + std::chrono::seconds(m_period);

            break;

        case TimerMetric::Milliseconds:
            m_timeoutPoint = startPoint + std::chrono::milliseconds(m_period);

            break;

        case TimerMetric::Microseconds:
            m_timeoutPoint = startPoint + std::chrono::microseconds(m_period);

            break;

        case TimerMetric::Nanoseconds:
            m_timeoutPoint = startPoint + std::chrono::nanoseconds(m_period);

            break;

        default:
            break;
        }
    }
}

inline auto PeriodicTimerData::nextTimeoutPoint() noexcept -> void
{
    std::lock_guard<SpinLock> locker { m_context };

    if (m_period > 0) {
        switch (m_metric) {
        case TimerMetric::Hours:
            m_timeoutPoint += std::chrono::hours(m_period);

            break;

        case TimerMetric::Minutes:
            m_timeoutPoint += std::chrono::minutes(m_period);

            break;

        case TimerMetric::Seconds:
            m_timeoutPoint += std::chrono::seconds(m_period);

            break;

        case TimerMetric::Milliseconds:
            m_timeoutPoint += std::chrono::milliseconds(m_period);

            break;

        case TimerMetric::Microseconds:
            m_timeoutPoint += std::chrono::microseconds(m_period);

            break;

        case TimerMetric::Nanoseconds:
            m_timeoutPoint += std::chrono::nanoseconds(m_period);

            break;

        default:
            break;
        }
    }
}

template<TimerMetric Metric>
inline auto PeriodicTimerData::remaining() noexcept -> uint64
{
    std::lock_guard<SpinLock> locker { m_context };

    if (!m_active)
        return 0;

    auto now = std::chrono::steady_clock::now();

    if (now < m_timeoutPoint)
        return Internal::timeDifference<Metric>(now, m_timeoutPoint);

    return 0;
}

inline auto PeriodicTimerData::operator <(PeriodicTimerData &other) noexcept -> bool
{
    std::unique_lock<SpinLock> locker (m_context, std::defer_lock);
    std::unique_lock<SpinLock> otherLocker (other.m_context, std::defer_lock);
    std::lock(locker, otherLocker);

    return m_timeoutPoint < other.m_timeoutPoint;
}

} // end namespace Internal

// PeriodicTimer class
class PeriodicTimer : private DisableCopyable
{
public:
    // Getters
    auto period() noexcept -> uint64;
    auto isActive() noexcept -> bool;

    // Setters
    template<TimerMetric Metric = TimerMetric::Milliseconds>
    auto setPeriod(uint64 period) noexcept -> void;

    // Controls
    auto isPeriodic() noexcept -> bool;
    auto start(uint64 timeout) noexcept -> void;
    auto restart(uint64 timeout) noexcept -> void;
    auto stop() noexcept -> void;

    template<TimerMetric Metric = TimerMetric::Milliseconds>
    auto remaining() noexcept -> uint64;

private:
    Internal::PeriodicTimerData m_data {};
};

// PeriodicTimer inline methods
inline auto PeriodicTimer::period() noexcept -> uint64
{
    return m_data.period();
}

inline auto PeriodicTimer::isActive() noexcept -> bool
{
    return m_data.isActive();
}

template<TimerMetric Metric>
inline auto PeriodicTimer::setPeriod(uint64 period) noexcept -> void
{
    m_data.setPeriod<Metric>(period);
}

inline auto PeriodicTimer::isPeriodic() noexcept -> bool
{
    return m_data.isPeriodic();
}

template<TimerMetric Metric>
inline auto PeriodicTimer::remaining() noexcept -> uint64
{
    return m_data.remaining<Metric>();
}

} // end namespace Timers

} // end namespace Calibri

#endif // CALIBRI_TIMERS_PERIODICTIMER_HPP
