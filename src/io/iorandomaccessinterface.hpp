#ifndef CALIBRI_IO_IORANDOMACCESSINTERFACE_HPP
#define CALIBRI_IO_IORANDOMACCESSINTERFACE_HPP

// Calibri-Library includes
#include "iointerface.hpp"

namespace Calibri {

namespace Io {

// IORandomAccessInterface class
class IORandomAccessInterface : public IOInterface
{
public:
    auto pos() const noexcept -> sizeinfo;
    auto seek(sizeinfo pos) noexcept -> bool;
    auto skip(sizeinfo size) noexcept -> bool;
    auto reset() noexcept -> void;

    auto readLine(char *data, sizeinfo size) noexcept -> sizeinfo;

    virtual auto canReadLine() const noexcept -> bool = 0;
    virtual auto atEnd() const noexcept -> bool = 0;

protected:
    auto setPos(sizeinfo pos) noexcept -> void;

    virtual auto readLineData(char *data, sizeinfo size) noexcept -> sizeinfo = 0;
    virtual auto seekData(sizeinfo pos) noexcept -> bool = 0;

private:
    sizeinfo m_pos {};
};

// IORandomAccessInterface inline methods
inline auto IORandomAccessInterface::pos() const noexcept -> sizeinfo
{
    return m_pos;
}

inline auto IORandomAccessInterface::seek(sizeinfo pos) noexcept -> bool
{
    return seekData(pos);
}

inline auto IORandomAccessInterface::skip(sizeinfo size) noexcept -> bool
{
    return seek(pos() + size);
}

inline auto IORandomAccessInterface::reset() noexcept -> void
{
    setPos(0);
}

inline auto IORandomAccessInterface::readLine(char *data, sizeinfo size) noexcept -> sizeinfo
{
    return readLineData(data, size);
}

inline auto IORandomAccessInterface::setPos(sizeinfo pos) noexcept -> void
{
    m_pos = pos;
}

} // end namespace Io

using Io::IORandomAccessInterface;

} // end namespace Calibri

#endif // CALIBRI_IO_IORANDOMACCESSINTERFACE_HPP
