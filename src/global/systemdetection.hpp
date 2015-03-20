#ifndef CALIBRI_GLOBAL_SYSTEMDETECTION_HPP
#define CALIBRI_GLOBAL_SYSTEMDETECTION_HPP

// Defines
#if defined(_WIN32)
#   define OS_WINDOWS
#elif defined(__linux__)
#   define OS_LINUX
#elif defined(__unix__)
#   define OS_UNIX
#else
#   error "Calibri does not support current operation system"
#endif

#endif // CALIBRI_GLOBAL_SYSTEMDETECTION_HPP
