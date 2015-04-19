#ifndef CALIBRI_TIMERS_ELAPSEDTIMER_HPP
#define CALIBRI_TIMERS_ELAPSEDTIMER_HPP

// Calibri-Library includes
#include "timermetric.hpp"

namespace Calibri {

namespace Timers {

// ElapsedTimer class
class ElapsedTimer
{
public:
    // Controls
    auto start() noexcept -> void;
    auto reset() noexcept -> void;

    template<TimerMetric Metric = TimerMetric::Milliseconds>
    auto restart() noexcept -> uint64;

    template<TimerMetric Metric = TimerMetric::Milliseconds>
    auto elapsed() const noexcept -> uint64;

    template<TimerMetric Metric = TimerMetric::Milliseconds>
    auto hasExpired(uint64 timeout) const noexcept -> bool;

private:    
    std::chrono::steady_clock::time_point m_startPoint {};
};

// ElapsedTimer inline methods
inline auto ElapsedTimer::start() noexcept -> void
{
    m_startPoint = std::chrono::steady_clock::now();
}

inline auto ElapsedTimer::reset() noexcept -> void
{
    m_startPoint = std::chrono::steady_clock::time_point();
}

template<TimerMetric Metric>
inline auto ElapsedTimer::restart() noexcept -> uint64
{
    auto finishPoint = std::chrono::steady_clock::now();
    auto duration = Internal::timeDifference<Metric>(m_startPoint, finishPoint);

    m_startPoint = finishPoint;

    return duration;
}

template<TimerMetric Metric>
inline auto ElapsedTimer::elapsed() const noexcept -> uint64
{
    return Internal::timeDifference<Metric>(m_startPoint, std::chrono::steady_clock::now());
}

template<TimerMetric Metric>
inline auto ElapsedTimer::hasExpired(uint64 timeout) const noexcept -> bool
{
    return timeout < elapsed<Metric>();
}

} // end namespace Timers

using Timers::ElapsedTimer;

} // end namespace Calibri

#endif // CALIBRI_TIMERS_ELAPSEDTIMER_HPP
