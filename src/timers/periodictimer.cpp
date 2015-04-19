// Self includes
#include "periodictimer.hpp"

// Std includes
#include <set>
#include <condition_variable>

namespace Calibri {

namespace Timers {

namespace Variables {

// Aliases
using TaskData = std::reference_wrapper<Internal::PeriodicTimerData>;
using TaskTimePointComparator = bool (*)(const TaskData &, const TaskData &);

static SpinLock contex {};
static std::condition_variable_any contextCondition {};
static std::set<TaskData, TaskTimePointComparator> tasks {
    [](const TaskData &left, const TaskData &right) noexcept {
        return left.get() < right.get();
    }
};

} // end namespace Variables

namespace Internal {

static inline auto scheduler() noexcept -> void
{
    std::unique_lock<SpinLock> locker(Variables::contex);

    do {
        if (Variables::tasks.empty()) {
            Variables::contextCondition.wait(locker);

            continue;
        }

        // TODO: scheduler logic
    } while (true);
}

static inline auto startScheduler() noexcept -> void
{
    static std::once_flag schedulerFlag {};

    std::call_once(schedulerFlag, []() {
        std::thread(scheduler).detach();
    });
}

} // end namespace Internal

auto PeriodicTimer::start(uint64 timeout) noexcept -> void
{
    Internal::startScheduler();

    if (isActive())
        return;
}

auto PeriodicTimer::restart(uint64 timeout) noexcept -> void
{
    Internal::startScheduler();

    stop();
    start(timeout);
}

auto PeriodicTimer::stop() noexcept -> void
{
    if (!isActive())
        return;
}

} // end namespace Timers

} // end namespace Calibri
