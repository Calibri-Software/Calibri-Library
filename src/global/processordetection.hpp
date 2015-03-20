#ifndef CALIBRI_GLOBAL_PROCESSORDETECTION_HPP
#define CALIBRI_GLOBAL_PROCESSORDETECTION_HPP

// Defines
#if defined(__i386__)
#   define CPU_X86
#elif defined(__x86_64__)
#   define CPU_X86_64
#elif defined(__ia64__)
#   define CPU_IA64
#else
#   error "Calibri does not support current processor"
#endif

#endif // CALIBRI_GLOBAL_PROCESSORDETECTION_HPP
