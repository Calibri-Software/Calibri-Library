//! Self includes
#include "filesystemengine.hpp"

//! Std includes
#include <array>
#if defined(OS_WINDOWS)
#   include <memory>
#endif

//! Calibri-Library includes
#include "algorithms/split.hpp"
#include "algorithms/anyof.hpp"

//! System includes
#if defined(OS_LINUX) || defined(OS_UNIX)
#   include <sys/sendfile.h>
#   include <fcntl.h>
#endif

namespace Calibri {

namespace FileSystem {

namespace Constants {

static const std::string dotEntry { ".", 1 };
static const std::string dotDotEntry { "..", 2 };

#if defined(OS_LINUX) || defined(OS_UNIX)
static constexpr float scaleFactor { 1.7f };

static constexpr sizeinfo copyBufferSize { 65536 };
#endif

} // end namespace Constants

namespace Variables {

#if defined(OS_WINDOWS)
static thread_local std::unique_ptr<REPARSE_DATA_BUFFER> reparseDataBuffer { reinterpret_cast<REPARSE_DATA_BUFFER *>(::operator new(MAXIMUM_REPARSE_DATA_BUFFER_SIZE)) };

#   if defined(UNICODE)
static thread_local std::array<wchar, 260> pathBuffer { {} };
#   else
static thread_local std::array<char, 260> pathBuffer { {} };
#   endif
#elif defined(OS_LINUX) || defined(OS_UNIX)
static thread_local std::array<char, 260> pathBuffer { {} };
#endif

} // end namespace Variables

auto currentDirectory(bool *ok) noexcept -> std::string
{
#if defined(OS_WINDOWS)
    auto size = ::GetCurrentDirectory(Variables::pathBuffer.size(), Variables::pathBuffer.data());

    if (size == 0) {
        if (ok)
            *ok = false;

        return {};
    }

    if (size > Variables::pathBuffer.size()) {
#   if defined(UNICODE)
        auto buffer = std::vector<wchar>(size);
#   else
        auto buffer = std::vector<char>(size);
#   endif

        if (::GetCurrentDirectory(size, buffer.data()) == 0) {
            if (ok)
                *ok = false;

            return {};
        }

        if (ok)
            *ok = true;

#   if defined(UNICODE)
        return metaCast<std::string>(std::wstring(buffer.data(), size));
#   else
        return { buffer.data(), size };
#   endif
    } else {
        if (ok)
            *ok = true;

#   if defined(UNICODE)
        return metaCast<std::string>(std::wstring(Variables::pathBuffer.data(), size));
#   else
        return { Variables::pathBuffer.data(), size };
#   endif
    }
#elif defined(OS_LINUX) || defined(OS_UNIX)
    if (::getcwd(Variables::pathBuffer.data(), Variables::pathBuffer.size())) {
        if (ok)
            *ok = true;

        return { Variables::pathBuffer.data() };
    }

    if (errno != ERANGE) {
        if (ok)
            *ok = false;

        return {};
    }

    auto buffer = std::vector<char>(Variables::pathBuffer.size() * Constants::scaleFactor);

    do {
        if (::getcwd(buffer.data(), buffer.size())) {
            if (ok)
                *ok = true;

            return { buffer.data() };
        }

        if (errno != ERANGE) {
            if (ok)
                *ok = false;

            return {};
        }

        buffer.resize(buffer.size() * Constants::scaleFactor);
    } while (true);
#endif
}

auto createDirectories(const std::string &path) noexcept -> bool
{
    std::vector<std::string> entries {};

    split(entries, path, anyOf(Constants::separatorPattern));

    std::string currentEntry {};

    for (auto &entry : entries) {
        std::string nextEntry { currentEntry + entry + nativeSeparator() };

        FileInfo fileInfo(nextEntry);

        if (fileInfo.isDirectory()) {
            currentEntry = std::move(nextEntry);

            continue;
        }

        if (!createDirectory(nextEntry))
            return false;

        currentEntry = std::move(nextEntry);
    }

    return true;
}

auto readSymbolicLink(const std::string &path, bool *ok) noexcept -> std::string
{
#if defined(OS_WINDOWS)
#   if defined(UNICODE)
    auto handle = ::CreateFile(metaCast<std::wstring>(path).data(),
                               FILE_READ_EA,
                               FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                               nullptr,
                               OPEN_EXISTING,
                               FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
                               nullptr);
#   else
    auto handle = ::CreateFile(path.data(),
                               FILE_READ_EA,
                               FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                               nullptr,
                               OPEN_EXISTING,
                               FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
                               nullptr);
#   endif

    if (handle == INVALID_HANDLE_VALUE) {
        if (ok)
            *ok = false;

        return {};
    }

    ulong reparseDataBufferSize {};

    if (!::DeviceIoControl(handle, FSCTL_GET_REPARSE_POINT, nullptr, 0, Variables::reparseDataBuffer.get(), MAXIMUM_REPARSE_DATA_BUFFER_SIZE, &reparseDataBufferSize, nullptr)) {
        ::CloseHandle(handle);

        if (ok)
            *ok = false;

        return {};
    }

    ::CloseHandle(handle);

    switch (Variables::reparseDataBuffer->ReparseTag) {
    case IO_REPARSE_TAG_SYMLINK: {
#   if defined(UNICODE)
        auto length = Variables::reparseDataBuffer->SymbolicLinkReparseBuffer.PrintNameLength / sizeof(wchar);
        auto offset = Variables::reparseDataBuffer->SymbolicLinkReparseBuffer.PrintNameOffset / sizeof(wchar);
        auto buffer = &Variables::reparseDataBuffer->SymbolicLinkReparseBuffer.PathBuffer[offset];

        if (ok)
            *ok = true;

        return metaCast<std::string>(std::wstring(buffer, length));
#   else
        auto length = Variables::reparseDataBuffer->SymbolicLinkReparseBuffer.PrintNameLength / sizeof(char);
        auto offset = Variables::reparseDataBuffer->SymbolicLinkReparseBuffer.PrintNameOffset / sizeof(char);
        auto buffer = &Variables::reparseDataBuffer->SymbolicLinkReparseBuffer.PathBuffer[offset];

        if (ok)
            *ok = true;

        return { buffer, length };
#   endif
    }

    case IO_REPARSE_TAG_MOUNT_POINT: {
#   if defined(UNICODE)
        auto length = Variables::reparseDataBuffer->MountPointReparseBuffer.PrintNameLength / sizeof(wchar);
        auto offset = Variables::reparseDataBuffer->MountPointReparseBuffer.PrintNameOffset / sizeof(wchar);
        auto buffer = &Variables::reparseDataBuffer->MountPointReparseBuffer.PathBuffer[offset];

        if (ok)
            *ok = true;

        return metaCast<std::string>(std::wstring(buffer, length));
#   else
        auto length = Variables::reparseDataBuffer->MountPointReparseBuffer.PrintNameLength / sizeof(char);
        auto offset = Variables::reparseDataBuffer->MountPointReparseBuffer.PrintNameOffset / sizeof(char);
        auto buffer = &Variables::reparseDataBuffer->MountPointReparseBuffer.PathBuffer[offset];

        if (ok)
            *ok = true;

        return { buffer, length };
#   endif
    }

    default:
        if (ok)
            *ok = false;

        return {};
    }
#elif defined(OS_LINUX) || defined(OS_UNIX)
    auto size = ::readlink(path.data(), Variables::pathBuffer.data(), Variables::pathBuffer.size());

    if (size == -1) {
        if (ok)
            *ok = false;

        return {};
    }

    if (metaCast<sizeinfo>(size) < Variables::pathBuffer.size()) {
        if (ok)
            *ok = true;

        return { Variables::pathBuffer.data(), metaCast<sizeinfo>(size) };
    }

    auto buffer = std::vector<char>(Variables::pathBuffer.size() * Constants::scaleFactor);

    do {
        size = ::readlink(path.data(), buffer.data(), buffer.size());

        if (size == -1) {
            if (ok)
                *ok = false;

            return {};
        }

        if (metaCast<sizeinfo>(size) < Variables::pathBuffer.size()) {
            if (ok)
                *ok = true;

            return { Variables::pathBuffer.data(), metaCast<sizeinfo>(size) };
        }

        buffer.resize(buffer.size() * Constants::scaleFactor);
    } while (true);
#endif
}

auto removeAll(const std::string &path) noexcept -> uint32
{
    uint32 count {};

    FileInfo fileInfo { path };

    switch (fileInfo.type()) {
    case FileType::FileNotFound:
        break;

    case FileType::DirectoryFile: {
        DirectoryIterator it { path };

        while (it.hasNext()) {
            auto entry = it.next();

            if (entry == Constants::dotEntry || entry == Constants::dotDotEntry)
                continue;

            auto nativePath = path;

            if (!anyOf(Constants::separatorPattern)(nativePath.back()))
                nativePath += nativeSeparator();

            nativePath += entry;

            fileInfo = FileInfo(nativePath);

            switch (fileInfo.type()) {
            case FileType::FileNotFound:
                break;

            case FileType::DirectoryFile:
                count += removeAll(nativePath);

                break;

            case FileType::DirectorySymbolicLinkFile:
                if (removeDirectory(nativePath))
                    ++count;

                break;

            default:
                if (removeFile(nativePath))
                    ++count;

                break;
            }
        }

        if (removeDirectory(path))
            ++count;

        break;
    }

    case FileType::DirectorySymbolicLinkFile:
        if (removeDirectory(path))
            ++count;

        break;

    default:
        if (removeFile(path))
            ++count;

        break;
    }

    return count;
}

auto copyFile(const std::string &from, const std::string &to, bool failIfExists) noexcept -> bool
{
#if defined(OS_WINDOWS)
#   if defined(UNICODE)
    return ::CopyFile(metaCast<std::wstring>(from).data(), metaCast<std::wstring>(to).data(), failIfExists);
#   else
    return ::CopyFile(from.data(), to.data(), failIfExists);
#   endif
#elif defined(OS_LINUX) || defined(OS_UNIX)
    auto fromFile = ::open(from.data(), O_RDONLY);

    if (fromFile == -1)
        return false;

    FileInfo fileInfo { from };

    if (!fileInfo.exists())
        return false;

    auto toFile = ::open(to.data(), failIfExists ? O_CREAT | O_WRONLY | O_TRUNC | O_EXCL : O_CREAT | O_WRONLY | O_TRUNC, fileInfo.nativeAttributes());

    if (toFile == -1) {
        ::close(fromFile);

        return false;
    }

    sizeinfo processedBytes {};
    off_t offset {};

    while (processedBytes < fileInfo.size()) {
        auto bytes = ::sendfile(toFile, fromFile, &offset, Constants::copyBufferSize);

        if (bytes == -1) {
            ::close(toFile);
            ::close(fromFile);

            removeFile(to);

            return false;
        }

        processedBytes += bytes;
    }

    if (::close(toFile) == -1) {
        ::close(fromFile);

        removeFile(to);

        return false;
    }

    if (::close(fromFile) == -1)
        return false;

    return true;
#endif
}

} // end namespace FileSystem

} // end namespace Calibri
