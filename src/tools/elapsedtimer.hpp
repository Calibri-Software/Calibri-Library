#ifndef CALIBRI_TOOLS_ELAPSEDTIMER_HPP
#define CALIBRI_TOOLS_ELAPSEDTIMER_HPP

//! Std includes
#include <chrono>

//! Calibri-Library includes
#include "global/types.hpp"

namespace Calibri {

namespace Tools {

//! Enumerations
enum class ElapsedTimerMetric : uint8 {
    Hours,
    Minutes,
    Seconds,
    Miliseconds,
    Microseconds,
    Nanoseconds
};

namespace Internal {

template<ElapsedTimerMetric Metric,
         typename std::enable_if<Metric == ElapsedTimerMetric::Hours>::type ...Enabler>
inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::hours>(finish - start).count();
}

template<ElapsedTimerMetric Metric,
         typename std::enable_if<Metric == ElapsedTimerMetric::Minutes>::type ...Enabler>
inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::minutes>(finish - start).count();
}

template<ElapsedTimerMetric Metric,
         typename std::enable_if<Metric == ElapsedTimerMetric::Seconds>::type ...Enabler>
inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::seconds>(finish - start).count();
}

template<ElapsedTimerMetric Metric,
         typename std::enable_if<Metric == ElapsedTimerMetric::Miliseconds>::type ...Enabler>
inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
}

template<ElapsedTimerMetric Metric,
         typename std::enable_if<Metric == ElapsedTimerMetric::Microseconds>::type ...Enabler>
inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

template<ElapsedTimerMetric Metric,
         typename std::enable_if<Metric == ElapsedTimerMetric::Nanoseconds>::type ...Enabler>
inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

} // end namespace Internal

/*!
 *  ElapsedTimer class
 */
class ElapsedTimer
{
public:
    constexpr ElapsedTimer() noexcept = default;

    auto start() noexcept -> void;
    auto reset() noexcept -> void;

    template<ElapsedTimerMetric Metric = ElapsedTimerMetric::Miliseconds>
    auto restart() noexcept -> uint64;

    template<ElapsedTimerMetric Metric = ElapsedTimerMetric::Miliseconds>
    auto elapsed() const noexcept -> uint64;

    template<ElapsedTimerMetric Metric = ElapsedTimerMetric::Miliseconds>
    auto hasExpired(uint64 timeout) const noexcept -> bool;

private:    
    std::chrono::steady_clock::time_point m_startPoint {};
};

/*!
 *  ElapsedTimer inline methods
 */
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

    return duration;
}

template<ElapsedTimerMetric Metric>
inline auto ElapsedTimer::elapsed() const noexcept -> uint64
{
    return Internal::duration<Metric>(m_startPoint, std::chrono::steady_clock::now());
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
