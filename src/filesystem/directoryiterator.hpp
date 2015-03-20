#ifndef CALIBRI_FILESYSTEM_DIRECTORYITERATOR_HPP
#define CALIBRI_FILESYSTEM_DIRECTORYITERATOR_HPP

// Std includes
#include <string>

// Calibri-Library includes
#include "global/systemdetection.hpp"
#include "tools/disablecopyable.hpp"

// System includes
#if defined(OS_WINDOWS)
#   include <windows.h>
#elif defined(OS_LINUX) || defined(OS_UNIX)
#   include <dirent.h>
#endif

namespace Calibri {

namespace FileSystem {

// DirectoryIterator class
class DirectoryIterator : private DisableCopyable
{
public:
    DirectoryIterator(const std::string &path) noexcept;
    ~DirectoryIterator() noexcept;

    auto hasNext() const noexcept -> bool;

    auto next() noexcept -> std::string;

private:
#if defined(OS_WINDOWS)
    HANDLE m_entry { INVALID_HANDLE_VALUE };
    WIN32_FIND_DATA m_entryData = decltype(m_entryData)();
#elif defined(OS_LINUX) || defined(OS_UNIX)
    DIR *m_entry {};
    dirent m_entryData = decltype(m_entryData)();
#endif
};

// DirectoryIterator inline methods
inline DirectoryIterator::~DirectoryIterator() noexcept
{
#if defined(OS_WINDOWS)
    if (m_entry != INVALID_HANDLE_VALUE)
        ::FindClose(m_entry);
#elif defined(OS_LINUX) || defined(OS_UNIX)
    if (m_entry)
        ::closedir(m_entry);
#endif
}

inline auto DirectoryIterator::hasNext() const noexcept -> bool
{
#if defined(OS_WINDOWS)
    return m_entry != INVALID_HANDLE_VALUE;
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return m_entry != nullptr;
#endif
}

} // end namespace FileSystem

using FileSystem::DirectoryIterator;

} // end namespace Calibri

#endif // CALIBRI_FILESYSTEM_DIRECTORYITERATOR_HPP
