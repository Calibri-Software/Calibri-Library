#ifndef CALIBRI_TIMERS_TIMERMETRIC_HPP
#define CALIBRI_TIMERS_TIMERMETRIC_HPP

// Std includes
#include <chrono>

// Calibri-Library includes
#include "global/types.hpp"

namespace Calibri {

namespace Timers {

// Enumerations
enum class TimerMetric : uint8 {
    Hours,
    Minutes,
    Seconds,
    Milliseconds,
    Microseconds,
    Nanoseconds
};

namespace Internal {

template<TimerMetric Metric,
         typename std::enable_if<Metric == TimerMetric::Hours>::type * = nullptr>
static inline auto timeDifference(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::hours>(finish - start).count();
}

template<TimerMetric Metric,
         typename std::enable_if<Metric == TimerMetric::Minutes>::type * = nullptr>
static inline auto timeDifference(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::minutes>(finish - start).count();
}

template<TimerMetric Metric,
         typename std::enable_if<Metric == TimerMetric::Seconds>::type * = nullptr>
static inline auto timeDifference(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::seconds>(finish - start).count();
}

template<TimerMetric Metric,
         typename std::enable_if<Metric == TimerMetric::Milliseconds>::type * = nullptr>
static inline auto timeDifference(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
}

template<TimerMetric Metric,
         typename std::enable_if<Metric == TimerMetric::Microseconds>::type * = nullptr>
static inline auto timeDifference(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

template<TimerMetric Metric,
         typename std::enable_if<Metric == TimerMetric::Nanoseconds>::type * = nullptr>
static inline auto timeDifference(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

} // end namespace Internal

} // end namespace Timers

using Timers::TimerMetric;

} // end namespace Calibri

#endif // CALIBRI_TIMERS_TIMERMETRIC_HPP
