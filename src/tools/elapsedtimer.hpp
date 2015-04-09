#ifndef CALIBRI_TOOLS_ELAPSEDTIMER_HPP
#define CALIBRI_TOOLS_ELAPSEDTIMER_HPP

// Std includes
#include <chrono>

// Calibri-Library includes
#include "global/types.hpp"

namespace Calibri {

namespace Tools {

// Enumerations
enum class ElapsedTimerMetric : uint8 {
    Hours,
    Minutes,
    Seconds,
    Milliseconds,
    Microseconds,
    Nanoseconds
};

namespace Internal {

template<ElapsedTimerMetric Metric,
         typename std::enable_if<Metric == ElapsedTimerMetric::Hours>::type * = nullptr>
static inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> std::chrono::hours
{
    return std::chrono::duration_cast<std::chrono::hours>(finish - start);
}

template<ElapsedTimerMetric Metric,
         typename std::enable_if<Metric == ElapsedTimerMetric::Minutes>::type * = nullptr>
static inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> std::chrono::minutes
{
    return std::chrono::duration_cast<std::chrono::minutes>(finish - start);
}

template<ElapsedTimerMetric Metric,
         typename std::enable_if<Metric == ElapsedTimerMetric::Seconds>::type * = nullptr>
static inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> std::chrono::seconds
{
    return std::chrono::duration_cast<std::chrono::seconds>(finish - start);
}

template<ElapsedTimerMetric Metric,
         typename std::enable_if<Metric == ElapsedTimerMetric::Milliseconds>::type * = nullptr>
static inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> std::chrono::milliseconds
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
}

template<ElapsedTimerMetric Metric,
         typename std::enable_if<Metric == ElapsedTimerMetric::Microseconds>::type * = nullptr>
static inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> std::chrono::microseconds
{
    return std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
}

template<ElapsedTimerMetric Metric,
         typename std::enable_if<Metric == ElapsedTimerMetric::Nanoseconds>::type * = nullptr>
static inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> std::chrono::nanoseconds
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);
}

} // end namespace Internal

// ElapsedTimer class
class ElapsedTimer
{
public:
    auto start() noexcept -> void;
    auto reset() noexcept -> void;

    template<ElapsedTimerMetric Metric = ElapsedTimerMetric::Milliseconds>
    auto restart() noexcept -> uint64;

    template<ElapsedTimerMetric Metric = ElapsedTimerMetric::Milliseconds>
    auto elapsed() const noexcept -> uint64;

    template<ElapsedTimerMetric Metric = ElapsedTimerMetric::Milliseconds>
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

template<ElapsedTimerMetric Metric>
inline auto ElapsedTimer::restart() noexcept -> uint64
{
    auto finishPoint = std::chrono::steady_clock::now();
    auto duration = Internal::duration<Metric>(m_startPoint, finishPoint);

    m_startPoint = finishPoint;

    return duration.count();
}

template<ElapsedTimerMetric Metric>
inline auto ElapsedTimer::elapsed() const noexcept -> uint64
{
    return Internal::duration<Metric>(m_startPoint, std::chrono::steady_clock::now()).count();
}

template<ElapsedTimerMetric Metric>
inline auto ElapsedTimer::hasExpired(uint64 timeout) const noexcept -> bool
{
    return timeout < elapsed<Metric>();
}

} // end namespace Tools

using Tools::ElapsedTimerMetric;
using Tools::ElapsedTimer;

} // end namespace Calibri

#endif // CALIBRI_TOOLS_ELAPSEDTIMER_HPP
