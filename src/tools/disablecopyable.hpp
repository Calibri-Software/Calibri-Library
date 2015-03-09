#ifndef CALIBRI_TOOLS_DISABLECOPYABLE_HPP
#define CALIBRI_TOOLS_DISABLECOPYABLE_HPP

namespace Calibri {

namespace Tools {

/*!
 *  DisableCopyable class
 */
class DisableCopyable
{
public:
    constexpr DisableCopyable() noexcept = default;

private:
    DisableCopyable(const DisableCopyable &) = delete;
    DisableCopyable &operator =(const DisableCopyable &) = delete;
};

} // end namespace Tools

using Tools::DisableCopyable;

} // end namespace Calibri

#endif // CALIBRI_TOOLS_DISABLECOPYABLE_HPP
