// Self includes
#include "buffer.hpp"

namespace Calibri {

namespace Io {

namespace Constants {

static constexpr char endOfLine { '\n' };

} // end namespace Constants

auto Buffer::read(sizeinfo size) noexcept -> ByteArray
{
    auto data = ByteArray(size);

    data.resize(read(data, size));

    return data;
}

auto Buffer::readLine(sizeinfo size) noexcept -> ByteArray
{
    auto data = ByteArray(size);

    data.resize(readLine(data, size));

    return data;
}

auto Buffer::write(const ByteArray &data) noexcept -> sizeinfo
{
    return write(data.data(), data.size());
}

auto Buffer::canReadLine() const noexcept -> bool
{
    return std::find(std::next(std::begin(m_byteArray), pos()), std::end(m_byteArray), Constants::endOfLine) != std::end(m_byteArray);
}

auto Buffer::atEnd() const noexcept -> bool
{
    return pos() == m_byteArray.size();
}

auto Buffer::readData(char *data, sizeinfo size) noexcept -> sizeinfo
{
    size = std::min<decltype(size)>(m_byteArray.size() - pos(), size);

    std::copy_n(std::next(std::begin(m_byteArray), pos()), size, data);

    setPos(pos() + size);

    return size;
}

auto Buffer::writeData(const char *data, sizeinfo size) noexcept -> sizeinfo
{
    auto nextPos = pos() + size;

    if (nextPos > m_byteArray.size())
        m_byteArray.resize(nextPos);

    std::copy_n(data, size, std::next(std::begin(m_byteArray), pos()));

    setPos(nextPos);

    return size;
}

auto Buffer::readLineData(char *data, sizeinfo size) noexcept -> sizeinfo
{
    size = std::min<decltype(size)>(m_byteArray.size() - pos(), size);

    auto begin = std::next(std::begin(m_byteArray), pos());
    auto endOfLineIt = std::find(begin, std::end(m_byteArray), Constants::endOfLine);

    if (endOfLineIt != std::end(m_byteArray))
        size = std::min<decltype(size)>(std::distance(begin, endOfLineIt) + 1, size);

    std::copy_n(begin, size, data);

    setPos(pos() + size);

    return size;
}

auto Buffer::seekData(sizeinfo pos) noexcept -> bool
{
    if (pos > m_byteArray.size())
        return false;

    setPos(pos);

    return true;
}

} // end namespace Io

} // end namespace Calibri
