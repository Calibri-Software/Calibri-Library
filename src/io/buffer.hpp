#ifndef CALIBRI_IO_BUFFER_HPP
#define CALIBRI_IO_BUFFER_HPP

// Calibri-Library includes
#include "iorandomaccessinterface.hpp"
#include "tools/bytearray.hpp"

namespace Calibri {

namespace Io {

// Buffer class
class Buffer : public IORandomAccessInterface
{
public:
    Buffer() = default;
    Buffer(const ByteArray &data);
    Buffer(const char *data, sizeinfo size);
    Buffer(const char *data);
    Buffer(Buffer &&other) noexcept;

    auto operator =(Buffer &&other) noexcept -> Buffer &;
    auto operator ==(const Buffer &other) const noexcept -> bool;
    auto operator !=(const Buffer &other) const noexcept -> bool;

    auto data() const noexcept -> const ByteArray &;
    auto size() const noexcept -> sizeinfo;

    using IORandomAccessInterface::read;
    auto read(sizeinfo size) noexcept -> ByteArray;

    using IORandomAccessInterface::readLine;
    auto readLine(sizeinfo size) noexcept -> ByteArray;

    using IORandomAccessInterface::write;
    auto write(const ByteArray &data) noexcept -> sizeinfo;

    virtual auto canReadLine() const noexcept -> bool override;
    virtual auto atEnd() const noexcept -> bool override;

protected:
    virtual auto readData(char *data, sizeinfo size) noexcept -> sizeinfo override;
    virtual auto writeData(const char *data, sizeinfo size) noexcept -> sizeinfo override;
    virtual auto readLineData(char *data, sizeinfo size) noexcept -> sizeinfo override;
    virtual auto seekData(sizeinfo pos) noexcept -> bool override;

private:
    ByteArray m_byteArray {};
};

// Buffer inline methods
inline Buffer::Buffer(const ByteArray &data) :
    m_byteArray { data }
{
}

inline Buffer::Buffer(const char *data, sizeinfo size) :
    m_byteArray { data, size }
{
}

inline Buffer::Buffer(const char *data) :
    m_byteArray { data }
{
}

inline Buffer::Buffer(Buffer &&other) noexcept :
    m_byteArray { std::move(other.m_byteArray) }
{
    setPos(other.pos());

    other.reset();
}

inline auto Buffer::operator =(Buffer &&other) noexcept -> Buffer &
{
    m_byteArray = std::move(other.m_byteArray);

    setPos(other.pos());

    other.reset();

    return *this;
}

inline auto Buffer::operator ==(const Buffer &other) const noexcept -> bool
{
    return m_byteArray == other.m_byteArray;
}

inline auto Buffer::operator !=(const Buffer &other) const noexcept -> bool
{
    return m_byteArray != other.m_byteArray;
}

inline auto Buffer::data() const noexcept -> const ByteArray &
{
    return m_byteArray;
}

inline auto Buffer::size() const noexcept -> sizeinfo
{
    return m_byteArray.size();
}

// Non-member operators
inline auto operator <<(std::ostream &stream, const Buffer &data) noexcept -> std::ostream &
{
    return stream << data.data();
}

} // end namespace Io

using Io::Buffer;

} // end namespace Calibri

#endif // CALIBRI_IO_BUFFER_HPP
