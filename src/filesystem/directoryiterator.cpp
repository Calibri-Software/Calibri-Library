// Self includes
#include "directoryiterator.hpp"

// Calibri-Library includes
#include "filesystemengine.hpp"
#include "algorithms/anyof.hpp"

namespace Calibri {

namespace FileSystem {

DirectoryIterator::DirectoryIterator(const std::string &path) noexcept
{
#if defined(OS_WINDOWS)
    if (!path.empty()) {
        auto nativePath = path;

        if (!anyOf(Constants::separatorPattern)(nativePath.back()))
            nativePath += nativeSeparator();

        nativePath += '*';

#   if defined(UNICODE)
        m_entry = ::FindFirstFile(metaCast<std::wstring>(nativePath).data(), &m_entryData);
#   else
        m_entry = ::FindFirstFile(nativePath.data(), &m_entryData);
#   endif
    }
#elif defined(OS_LINUX) || defined(OS_UNIX)
    if (!path.empty()) {
        auto nativePath = path;

        if (!anyOf(Constants::separatorPattern)(nativePath.back()))
            nativePath += nativeSeparator();

        m_entry = ::opendir(nativePath.data());

        if (m_entry) {
            auto entryData = &m_entryData;

            if (::readdir_r(m_entry, &m_entryData, &entryData) != 0 || !entryData) {
                ::closedir(m_entry);

                m_entry = nullptr;
            }
        }
    }
#endif
}

auto DirectoryIterator::next() noexcept -> std::string
{
#if defined(OS_WINDOWS)
#   if defined(UNICODE)
    auto path = metaCast<std::string>(std::wstring(m_entryData.cFileName));
#   else
    auto path = std::string(m_entryData.cFileName);
#   endif

    if (m_entry != INVALID_HANDLE_VALUE) {
        if (!::FindNextFile(m_entry, &m_entryData)) {
            ::FindClose(m_entry);

            m_entry = INVALID_HANDLE_VALUE;
            m_entryData = decltype(m_entryData)();
        }
    }

    return path;
#elif defined(OS_LINUX) || defined(OS_UNIX)
    auto path = std::string(m_entryData.d_name);

    if (m_entry) {
        auto entryData = &m_entryData;

        if (::readdir_r(m_entry, &m_entryData, &entryData) != 0 || !entryData) {
            ::closedir(m_entry);

            m_entry = nullptr;
            m_entryData = decltype(m_entryData)();
        }
    }

    return path;
#endif
}

} // end namespace FileSystem

} // end namespace Calibri
