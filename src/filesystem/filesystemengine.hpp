#ifndef CALIBRI_FILESYSTEM_FILESYSTEMENGINE_HPP
#define CALIBRI_FILESYSTEM_FILESYSTEMENGINE_HPP

// Calibri-Library includes
#include "systemapi.hpp"
#include "fileinfo.hpp"
#include "directoryiterator.hpp"
#include "tools/metacast.hpp"

// System includes
#if defined(OS_LINUX) || defined(OS_UNIX)
#   include <sys/stat.h>
#   include <unistd.h>
#endif

namespace Calibri {

namespace FileSystem {

inline constexpr auto isCaseSensitive() noexcept -> bool
{
#if defined(OS_WINDOWS)
    return false;
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return true;
#endif
}

inline constexpr auto nativeSeparator() noexcept -> char
{
#if defined(OS_WINDOWS)
    return '\\';
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return '/';
#endif
}

inline auto toNativeSeparator(std::string &path) noexcept -> void
{
#if defined(OS_WINDOWS)
    std::replace(std::begin(path), std::end(path), '/', '\\');
#elif defined(OS_LINUX) || defined(OS_UNIX)
    std::replace(std::begin(path), std::end(path), '\\', '/');
#endif
}

inline auto setCurrentDirectory(const std::string &path) noexcept -> bool
{
#if defined(OS_WINDOWS)
#   if defined(UNICODE)
    return ::SetCurrentDirectory(metaCast<std::wstring>(path).data());
#   else
    return ::SetCurrentDirectory(path.data());
#   endif
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return ::chdir(path.data()) == 0;
#endif
}

auto currentDirectory(bool *ok = nullptr) noexcept -> std::string;

inline auto createDirectory(const std::string &path) noexcept -> bool
{
#if defined(OS_WINDOWS)
#   if defined(UNICODE)
    return ::CreateDirectory(metaCast<std::wstring>(path).data(), nullptr);
#   else
    return ::CreateDirectory(path.data(), nullptr);
#   endif
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return ::mkdir(path.data(), S_IRWXU | S_IRWXG | S_IRWXO) == 0;
#endif
}

auto createDirectories(const std::string &path) noexcept -> bool;

inline auto removeDirectory(const std::string &path) noexcept -> bool
{
#if defined(OS_WINDOWS)
#   if defined(UNICODE)
    return ::RemoveDirectory(metaCast<std::wstring>(path).data());
#   else
    return ::RemoveDirectory(path.data());
#   endif
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return ::rmdir(path.data()) == 0;
#endif
}

inline auto createSymbolicLink(const std::string &link, const std::string &path) noexcept -> bool
{
#if defined(OS_WINDOWS)
    FileInfo fileInfo { path };

    uint32 symbolicLinkFlag {};

    switch (fileInfo.type()) {
    case FileType::FileNotFound:
        return false;

    case FileType::DirectoryFile:
        symbolicLinkFlag = SYMBOLIC_LINK_FLAG_DIRECTORY;

        break;

    default:
        break;
    }

#   if defined(UNICODE)
    return ::CreateSymbolicLink(metaCast<std::wstring>(link).data(), metaCast<std::wstring>(path).data(), symbolicLinkFlag);
#   else
    return ::CreateSymbolicLink(link.data(), path.data(), symbolicLinkFlag);
#   endif
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return ::symlink(path.data(), link.data()) == 0;
#endif
}

auto readSymbolicLink(const std::string &path, bool *ok = nullptr) noexcept -> std::string;

inline auto resizeFile(const std::string &path, sizeinfo size) noexcept -> bool
{
#if defined(OS_WINDOWS)
#   if defined(UNICODE)
    auto handle = ::CreateFile(metaCast<std::wstring>(path).data(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
#   else
    auto handle = ::CreateFile(path.data(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
#   endif

    if (handle == INVALID_HANDLE_VALUE)
        return false;

    auto sizeValue = LARGE_INTEGER();
    sizeValue.QuadPart = size;

    if (!::SetFilePointerEx(handle, sizeValue, nullptr, FILE_BEGIN)) {
        ::CloseHandle(handle);

        return false;
    }

    if (!::SetEndOfFile(handle)) {
        ::CloseHandle(handle);

        return false;
    }

    ::CloseHandle(handle);

    return true;
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return ::truncate(path.data(), size) == 0;
#endif
}

inline auto removeFile(const std::string &path) noexcept -> bool
{
#if defined(OS_WINDOWS)
#   if defined(UNICODE)
    return ::DeleteFile(metaCast<std::wstring>(path).data());
#   else
    return ::DeleteFile(path.data());
#   endif
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return ::unlink(path.data()) == 0;
#endif
}

inline auto remove(const std::string &path) noexcept -> bool
{
    FileInfo fileInfo { path };

    switch (fileInfo.type()) {
    case FileType::FileNotFound:
        return false;

    case FileType::DirectoryFile:
    case FileType::DirectorySymbolicLinkFile:
        return removeDirectory(path);

    default:
        return removeFile(path);
    }
}

auto removeAll(const std::string &path) noexcept -> uint32;

inline auto rename(const std::string &from, const std::string &to) noexcept -> bool
{
#if defined(OS_WINDOWS)
#   if defined(UNICODE)
    return ::MoveFileEx(metaCast<std::wstring>(from).data(), metaCast<std::wstring>(to).data(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED);
#   else
    return ::MoveFileEx(from.data(), to.data(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED);
#   endif
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return ::rename(from.data(), to.data()) == 0;
#endif
}

inline auto copySymbolicLink(const std::string &from, const std::string &to) noexcept -> bool
{
    bool ok {};

    auto path = readSymbolicLink(from, &ok);

    if (!ok)
        return false;

    return createSymbolicLink(to, path);
}

inline auto copyDirectory(const std::string &from, const std::string &to) noexcept -> bool
{
#if defined(OS_WINDOWS)
#   if defined(UNICODE)
    return ::CreateDirectoryEx(metaCast<std::wstring>(from).data(), metaCast<std::wstring>(to).data(), nullptr);
#   else
    return ::CreateDirectoryEx(from.data(), to.data(), nullptr);
#   endif
#elif defined(OS_LINUX) || defined(OS_UNIX)    
    FileInfo fileInfo { from };

    if (!fileInfo.exists())
        return false;

    return ::mkdir(to.data(), fileInfo.nativeAttributes()) == 0;
#endif
}

auto copyFile(const std::string &from, const std::string &to, bool failIfExists = true) noexcept -> bool;

inline auto copy(const std::string &from, const std::string &to) noexcept -> bool
{
    FileInfo fileInfo { from };

    switch (fileInfo.type()) {
    case FileType::SymbolicLinkFile:
        return copySymbolicLink(from, to);

    case FileType::DirectoryFile:
        return copyDirectory(from, to);

    case FileType::RegularFile:
        return copyFile(from, to);

    default:
        return false;
    }
}

} // end namespace FileSystem

using FileSystem::isCaseSensitive;
using FileSystem::nativeSeparator;
using FileSystem::toNativeSeparator;
using FileSystem::setCurrentDirectory;
using FileSystem::currentDirectory;
using FileSystem::createDirectory;
using FileSystem::removeDirectory;
using FileSystem::createDirectories;
using FileSystem::createSymbolicLink;
using FileSystem::readSymbolicLink;
using FileSystem::resizeFile;
using FileSystem::removeFile;
using FileSystem::remove;
using FileSystem::removeAll;
using FileSystem::rename;
using FileSystem::copySymbolicLink;
using FileSystem::copyDirectory;
using FileSystem::copyFile;
using FileSystem::copy;

} // end namespace Calibri

#endif // CALIBRI_FILESYSTEM_FILESYSTEMENGINE_HPP
