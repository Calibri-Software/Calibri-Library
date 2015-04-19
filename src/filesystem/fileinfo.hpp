#ifndef CALIBRI_FILESYSTEM_FILEINFO_HPP
#define CALIBRI_FILESYSTEM_FILEINFO_HPP

// Std includes
#include <string>

// Calibri-Library includes
#include "global/types.hpp"

namespace Calibri {

namespace FileSystem {

// Enumerations
enum class FileType : uint8 {
    FileNotFound,
    RegularFile,
    DirectoryFile,
    SymbolicLinkFile,
    DirectorySymbolicLinkFile,
    ReparseFile,
    UnknownFile
};

namespace Constants {

static const std::string separatorPattern { "\\/", 2 };

} // end namespace Constants

// FileInfo class
class FileInfo
{
public:
    FileInfo(const std::string &path) noexcept;

    // Getters
    auto absoluteFilePath() const noexcept -> const std::string &;
    auto absolutePath() const noexcept -> std::string;
    auto fileName() const noexcept -> std::string;
    auto type() const noexcept -> FileType;
    auto size() const noexcept -> sizeinfo;
    auto nativeAttributes() const noexcept -> uint16;


    // Controls
    auto isExists() const noexcept -> bool;
    auto isDirectory() const noexcept -> bool;
    auto isRegularFile() const noexcept -> bool;
    auto isSymbolicLink() const noexcept -> bool;
    auto isDirectorySymbolicLink() const noexcept -> bool;
    auto isOther() const noexcept -> bool;
    auto refresh() noexcept -> void;

private:
    std::string m_absoluteFilePath {};
    FileType m_type {};
    sizeinfo m_size {};
    uint16 m_nativeAttributes {};

    auto refresh(const std::string &path) noexcept -> void;
};

// FileInfo inline methods
inline auto FileInfo::absoluteFilePath() const noexcept -> const std::string &
{
    return m_absoluteFilePath;
}

inline auto FileInfo::absolutePath() const noexcept -> std::string
{
    auto position = m_absoluteFilePath.find_last_of(Constants::separatorPattern);

    if (position == std::string::npos)
        return {};

    return m_absoluteFilePath.substr(0, position);
}

inline auto FileInfo::fileName() const noexcept -> std::string
{
    auto position = m_absoluteFilePath.find_last_of(Constants::separatorPattern);

    if (position == std::string::npos)
        return {};

    return m_absoluteFilePath.substr(++position);
}

inline auto FileInfo::type() const noexcept -> FileType
{
    return m_type;
}

inline auto FileInfo::size() const noexcept -> sizeinfo
{
    return m_size;
}

inline auto FileInfo::nativeAttributes() const noexcept -> uint16
{
    return m_nativeAttributes;
}

inline auto FileInfo::isExists() const noexcept -> bool
{
    return m_type != FileType::FileNotFound;
}

inline auto FileInfo::isDirectory() const noexcept -> bool
{
    return m_type == FileType::DirectoryFile;
}

inline auto FileInfo::isRegularFile() const noexcept -> bool
{
    return m_type == FileType::RegularFile;
}

inline auto FileInfo::isSymbolicLink() const noexcept -> bool
{
    return m_type == FileType::SymbolicLinkFile;
}

inline auto FileInfo::isDirectorySymbolicLink() const noexcept -> bool
{
    return m_type == FileType::DirectorySymbolicLinkFile;
}

inline auto FileInfo::isOther() const noexcept -> bool
{
    return isExists() && !isDirectory() && !isRegularFile() && !isSymbolicLink() && !isDirectorySymbolicLink();
}

inline auto FileInfo::refresh() noexcept -> void
{
    refresh(absoluteFilePath());
}

} // end namespace FileSystem

using FileSystem::FileType;
using FileSystem::FileInfo;

} // end namespace Calibri

#endif // CALIBRI_FILESYSTEM_FILEINFO_HPP
