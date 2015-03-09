#ifndef CALIBRI_FILESYSTEM_SYSTEMAPI_HPP
#define CALIBRI_FILESYSTEM_SYSTEMAPI_HPP

//! Std includes
#include <iostream>

//! Calibri-Library includes
#include "global/types.hpp"

#if defined(OS_WINDOWS)
//! System includes
#include <windows.h>

#   if !defined(REPARSE_DATA_BUFFER_HEADER_SIZE)
typedef struct _REPARSE_DATA_BUFFER {
    ulong  ReparseTag;
    ushort ReparseDataLength;
    ushort Reserved;

    union {
        struct {
            ushort SubstituteNameOffset;
            ushort SubstituteNameLength;
            ushort PrintNameOffset;
            ushort PrintNameLength;
            ulong  Flags;
            wchar  PathBuffer[1];
        } SymbolicLinkReparseBuffer;

        struct {
            ushort SubstituteNameOffset;
            ushort SubstituteNameLength;
            ushort PrintNameOffset;
            ushort PrintNameLength;
            wchar  PathBuffer[1];
        } MountPointReparseBuffer;

        struct {
            uchar DataBuffer[1];
        } GenericReparseBuffer;
    };
} REPARSE_DATA_BUFFER, *PREPARSE_DATA_BUFFER;

#       define REPARSE_DATA_BUFFER_HEADER_SIZE FIELD_OFFSET(REPARSE_DATA_BUFFER, GenericReparseBuffer)
#   endif

#   if !defined(CreateSymbolicLink)
static inline auto CreateSymbolicLinkW(const wchar *link, const wchar *path, ulong flags) noexcept -> bool
{
    static thread_local auto createSymbolicLink = reinterpret_cast<bool (*)(const wchar *, const wchar *, ulong)>(
                ::GetProcAddress(
                    ::GetModuleHandle(TEXT("kernel32.dll")), "CreateSymbolicLinkW"));

    if (!createSymbolicLink) {
        std::cerr << "CreateSymbolicLinkW function unavailable" << std::endl;

        return false;
    }

    return createSymbolicLink(link, path, flags);
}

static inline auto CreateSymbolicLinkW(const char *link, const char *path, ulong flags) noexcept -> bool
{
    static thread_local auto createSymbolicLink = reinterpret_cast<bool (*)(const char *, const char *, ulong)>(
                ::GetProcAddress(
                    ::GetModuleHandle(TEXT("kernel32.dll")), "CreateSymbolicLinkA"));

    if (!createSymbolicLink) {
        std::cerr << "CreateSymbolicLinkA function unavailable" << std::endl;

        return false;
    }

    return createSymbolicLink(link, path, flags);
}

#       if defined(UNICODE)
#           define CreateSymbolicLink CreateSymbolicLinkW
#       else
#           define CreateSymbolicLink CreateSymbolicLinkA
#       endif

#       if !defined(SYMBOLIC_LINK_FLAG_DIRECTORY)
#           define SYMBOLIC_LINK_FLAG_DIRECTORY 0x1
#       endif
#   endif
#endif

#endif // CALIBRI_FILESYSTEM_SYSTEMAPI_HPP
