#ifndef CALIBRI_GLOBAL_VERSION_HPP
#define CALIBRI_GLOBAL_VERSION_HPP

//! Defines
#define VERSION_VALUE(major, minor, patch) (major * 100000 + minor * 1000 + patch)
#define VERSION VERSION_VALUE(2, 0, 0)
#define VERSION_CHECK(major, minor, patch) (VERSION >= VERSION_VALUE(major, minor, patch))

#endif // CALIBRI_GLOBAL_VERSION_HPP
