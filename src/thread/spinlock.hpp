#ifndef CALIBRI_THREAD_SPINLOCK_HPP
#define CALIBRI_THREAD_SPINLOCK_HPP

//! Std includes
#include <atomic>
#include <thread>

//! Calibri-Library includes
#include "global/types.hpp"
#include "tools/disablecopyable.hpp"

namespace Calibri {

namespace Thread {

namespace Internal {

inline void yield(uint32 spin) noexcept
{
    if (spin < 4) {
    } else if (spin < 16) {
        __asm__ __volatile__("rep; nop" : : : "memory");
    } else if (spin < 32) {
        std::this_thread::yield();
    } else {
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}

} // end namespace Internal

/*!
 *  SpinLock class
 */
class SpinLock : private DisableCopyable
{
public:
    constexpr SpinLock() noexcept = default;

    auto lock() noexcept -> void;
    auto unlock() noexcept -> void;

    auto tryLock() noexcept -> bool;

private:
    std::atomic_flag m_atomicFlag { ATOMIC_FLAG_INIT };
};

/*!
 *  SpinLock inline methods
 */
inline auto SpinLock::lock() noexcept -> void
{
    for (uint32 spin = 0; !tryLock(); ++spin)
        Internal::yield(spin);
}

inline auto SpinLock::unlock() noexcept -> void
{
    m_atomicFlag.clear(std::memory_order_release);
}

inline auto SpinLock::tryLock() noexcept -> bool
{
    return !m_atomicFlag.test_and_set(std::memory_order_acquire);
}

} // end namespace Thread

using Thread::SpinLock;

} // end namespace Calibri

#endif // CALIBRI_THREAD_SPINLOCK_HPP
