#ifndef CALIBRI_SIGNALS_ENABLESIGNAL_HPP
#define CALIBRI_SIGNALS_ENABLESIGNAL_HPP

//! Calibri-Library includes
#include "trackableobject.hpp"

namespace Calibri {

namespace Signals {

namespace Variables {

static thread_local SpinLock threadContext {};

} // end namespace Variables

/*!
 *  EnableSignals class
 */
class EnableSignal : private DisableCopyable, public Internal::TrackableObject
{
public:
    auto context() const noexcept -> SpinLock &;

private:
    SpinLock &m_context { Variables::threadContext };
};

/*!
 *  EnableSignals inline methods
 */
inline auto EnableSignal::context() const noexcept -> SpinLock &
{
    return m_context;
}

} // end namespace Signals

using Signals::EnableSignal;

} // end namespace Calibri

#endif // CALIBRI_SIGNALS_ENABLESIGNAL_HPP
