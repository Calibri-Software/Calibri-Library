// Self includes
#include "fileinfo.hpp"

// Std includes
#if defined(OS_WINDOWS)
#   include <memory>
#endif

// Calibri-Library includes
#include "filesystemengine.hpp"

namespace Calibri {

namespace FileSystem {

namespace Constants {

#if defined(OS_LINUX) || defined(OS_UNIX)
static const std::string dotEntry { ".", 1 };
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
#endif

} // end namespace Variables

FileInfo::FileInfo(const std::string &path) noexcept
{
    refresh(path);

    if (isExists()) {
#if defined(OS_WINDOWS)
#   if defined(UNICODE)
        auto unicodePath = metaCast<std::wstring>(path);

        auto size = ::GetFullPathName(unicodePath.data(), Variables::pathBuffer.size(), Variables::pathBuffer.data(), nullptr);
#   else
        auto size = ::GetFullPathName(path.data(), Variables::pathBuffer.size(), Variables::pathBuffer.data(), nullptr);
#   endif

        if (size > Variables::pathBuffer.size()) {
#   if defined(UNICODE)
            auto buffer = std::vector<wchar>(size);

            ::GetFullPathName(unicodePath.data(), size, buffer.data(), nullptr);

            m_absoluteFilePath.assign(metaCast<std::string>(std::wstring(buffer.data(), size)));
#   else
            auto buffer = std::vector<char>(size);

            ::GetFullPathName(path.data(), size, buffer.data(), nullptr);

            m_absoluteFilePath.assign(buffer.data(), size);
#   endif
        } else {
#   if defined(UNICODE)
            m_absoluteFilePath.assign(metaCast<std::string>(std::wstring(Variables::pathBuffer.data(), size)));
#   else
            m_absoluteFilePath.assign(Variables::pathBuffer.data(), size);
#   endif
        }
#elif defined(OS_LINUX) || defined(OS_UNIX)
        char *resolvedPath {};

        auto position = path.find_last_of(Constants::separatorPattern);

        if (position == std::string::npos) {
            resolvedPath = ::canonicalize_file_name(Constants::dotEntry.data());

            m_absoluteFilePath.assign(resolvedPath);
            m_absoluteFilePath += nativeSeparator();
            m_absoluteFilePath += path;
        } else {
            resolvedPath = ::canonicalize_file_name(path.substr(0, position).data());

            m_absoluteFilePath.assign(resolvedPath);
            m_absoluteFilePath += path.substr(position);
        }

        ::free(resolvedPath);
#endif
    }
}

auto FileInfo::refresh(const std::string &path) noexcept -> void
{
#if defined(OS_WINDOWS)
    auto fileStatus = WIN32_FILE_ATTRIBUTE_DATA();

#   if defined(UNICODE)
    if (!::GetFileAttributesEx(metaCast<std::wstring>(path).data(), ::GetFileExInfoStandard, &fileStatus)) {
#   else
    if (!::GetFileAttributesEx(path.data(), ::GetFileExInfoStandard, &fileStatus)) {
#   endif
        m_type = FileType::FileNotFound;
    } else {
        m_nativeAttributes = fileStatus.dwFileAttributes;

        if (fileStatus.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) {
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
                m_type = FileType::ReparseFile;
            } else {
                ulong reparseDataBufferSize {};

                if (!::DeviceIoControl(handle, FSCTL_GET_REPARSE_POINT, nullptr, 0, Variables::reparseDataBuffer.get(), MAXIMUM_REPARSE_DATA_BUFFER_SIZE, &reparseDataBufferSize, nullptr)) {
                    ::CloseHandle(handle);

                    m_type = FileType::ReparseFile;
                } else {
                    ::CloseHandle(handle);

                    switch (Variables::reparseDataBuffer->ReparseTag) {
                    case IO_REPARSE_TAG_SYMLINK:
                    case IO_REPARSE_TAG_MOUNT_POINT:
                        m_type = (fileStatus.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? FileType::DirectorySymbolicLinkFile : FileType::SymbolicLinkFile;

                        break;

                    default:
                        m_type = FileType::ReparseFile;

                        break;
                    }
                }
            }
        } else {
            if (fileStatus.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                m_type = FileType::DirectoryFile;
            } else {
                m_type = FileType::RegularFile;

                auto fileSize = LARGE_INTEGER();
                fileSize.LowPart = fileStatus.nFileSizeLow;
                fileSize.HighPart = fileStatus.nFileSizeHigh;

                m_size = fileSize.QuadPart;
            }
        }
    }
#elif defined(OS_LINUX) || defined(OS_UNIX)
    struct stat fileStatus = decltype(fileStatus)();

    if (::lstat(path.data(), &fileStatus) != 0) {
        m_type = FileType::FileNotFound;
    } else {
        m_nativeAttributes = fileStatus.st_mode;

        switch (fileStatus.st_mode & S_IFMT) {
        case S_IFLNK:
            m_type = FileType::SymbolicLinkFile;

            break;

        case S_IFDIR:
            m_type = FileType::DirectoryFile;

            break;

        case S_IFREG:
            m_type = FileType::RegularFile;
            m_size = fileStatus.st_size;

            break;

        default:
            m_type = FileType::UnknownFile;

            break;
        }
    }
#endif
}

} // end namespace FileSystem

} // end namespace Calibri
