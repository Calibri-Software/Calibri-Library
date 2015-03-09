#ifndef CALIBRI_TOOLS_DISABLECONSTRUCTIBLE_HPP
#define CALIBRI_TOOLS_DISABLECONSTRUCTIBLE_HPP

//! Calibri-Library Includes
#include "disablecopyable.hpp"

namespace Calibri {

namespace Tools {

/*!
 *  DisableCopyable class
 */
class DisableConstructible : private DisableCopyable
{
private:
    DisableConstructible() = delete;
};

} // end namespace Tools

using Tools::DisableConstructible;

} // end namespace Calibri

#endif // CALIBRI_TOOLS_DISABLECONSTRUCTIBLE_HPP
