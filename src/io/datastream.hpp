#ifndef CALIBRI_IO_DATASTREAM_HPP
#define CALIBRI_IO_DATASTREAM_HPP

//! Std includes
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

//! Calibri-Library includes
#include "buffer.hpp"
#include "tools/disablecopyable.hpp"
#include "tools/metacast.hpp"

namespace Calibri {

namespace Io {

//! Enumerations
enum class DataStreamStatus : uint8 {
    Ok,
    ReadError,
    WriteError
};

namespace Constants {

static constexpr char nullTerminator { '\0' };

} // end namespace Constants

/*!
 *  DataStream class
 */
template<typename DeviceType,
         typename std::enable_if<std::is_base_of<IOInterface, DeviceType>::value>::type ...Enabler>
class DataStream : private DisableCopyable
{
public:
    DataStream(DeviceType *device) noexcept;

    auto device() const noexcept -> DeviceType *;

    auto status() const noexcept -> DataStreamStatus;

    auto setStatus(DataStreamStatus status) noexcept -> void;

    auto resetStatus() noexcept -> void;

private:
    DeviceType *m_device {};

    DataStreamStatus m_status { DataStreamStatus::Ok };
};

/*!
 *  DataStream inline methods
 */
template<typename DeviceType,
         typename std::enable_if<std::is_base_of<IOInterface, DeviceType>::value>::type ...Enabler>
inline DataStream<DeviceType, Enabler ...>::DataStream(DeviceType *device) noexcept :
    DisableCopyable(),
    m_device { device }
{
}

template<typename DeviceType,
         typename std::enable_if<std::is_base_of<IOInterface, DeviceType>::value>::type ...Enabler>
inline auto DataStream<DeviceType, Enabler ...>::device() const noexcept -> DeviceType *
{
    return m_device;
}

template<typename DeviceType,
         typename std::enable_if<std::is_base_of<IOInterface, DeviceType>::value>::type ...Enabler>
inline auto DataStream<DeviceType, Enabler ...>::status() const noexcept -> DataStreamStatus
{
    return m_status;
}

template<typename DeviceType,
         typename std::enable_if<std::is_base_of<IOInterface, DeviceType>::value>::type ...Enabler>
inline auto DataStream<DeviceType, Enabler ...>::setStatus(DataStreamStatus status) noexcept -> void
{
    m_status = status;
}

template<typename DeviceType,
         typename std::enable_if<std::is_base_of<IOInterface, DeviceType>::value>::type ...Enabler>
inline auto DataStream<DeviceType, Enabler ...>::resetStatus() noexcept -> void
{
    m_status = DataStreamStatus::Ok;
}

/*!
 *  DataStream write operators
 */
template<typename DeviceType,
         typename DataType,
         typename std::enable_if<std::is_arithmetic<DataType>::value>::type ...Enabler>
inline auto operator <<(DataStream<DeviceType> &dataStream, DataType data) noexcept -> DataStream<DeviceType> &
{
    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    if (dataStream.device()->write(reinterpret_cast<const char *>(&data), sizeof(DataType)) != sizeof(DataType))
        dataStream.setStatus(DataStreamStatus::WriteError);

    return dataStream;
}

template<typename DeviceType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const char *data) noexcept -> DataStream<DeviceType> &
{
    auto size = std::char_traits<char>::length(data);

    dataStream << metaCast<uint32>(size);

    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    if (dataStream.device()->write(data, size) != size)
        dataStream.setStatus(DataStreamStatus::WriteError);

    return dataStream;
}

template<typename DeviceType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::string &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << metaCast<uint32>(data.size());

    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    if (dataStream.device()->write(data.data(), data.size()) != data.size())
        dataStream.setStatus(DataStreamStatus::WriteError);

    return dataStream;
}

//! Sequence containers
template<typename DeviceType,
         typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::vector<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << metaCast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType,
         typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::deque<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << metaCast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType,
         typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::forward_list<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << metaCast<uint32>(std::distance(std::begin(data), std::end(data)));

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType,
         typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::list<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << metaCast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

//! Associative containers
template<typename DeviceType,
         typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::set<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << metaCast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType,
         typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::multiset<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << metaCast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType,
         typename KeyType,
         typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::map<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << metaCast<uint32>(data.size());

    for (const auto &pair : data) {
        dataStream << pair.first;
        dataStream << pair.second;
    }

    return dataStream;
}

template<typename DeviceType,
         typename KeyType,
         typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::multimap<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << metaCast<uint32>(data.size());

    for (const auto &pair : data) {
        dataStream << pair.first;
        dataStream << pair.second;
    }

    return dataStream;
}

//! Unordered associative containers
template<typename DeviceType,
         typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::unordered_set<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << metaCast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType,
         typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::unordered_multiset<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << metaCast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType,
         typename KeyType,
         typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::unordered_map<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << metaCast<uint32>(data.size());

    for (const auto &pair : data) {
        dataStream << pair.first;
        dataStream << pair.second;
    }

    return dataStream;
}

template<typename DeviceType,
         typename KeyType,
         typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::unordered_multimap<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << metaCast<uint32>(data.size());

    for (const auto &pair : data) {
        dataStream << pair.first;
        dataStream << pair.second;
    }

    return dataStream;
}

/*!
 *  DataStream read operators
 */
template<typename DeviceType,
         typename DataType,
         typename std::enable_if<std::is_arithmetic<DataType>::value>::type ...Enabler>
inline auto operator >>(DataStream<DeviceType> &dataStream, DataType &data) noexcept -> DataStream<DeviceType> &
{
    data = 0;

    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    if (dataStream.device()->read(reinterpret_cast<char *>(&data), sizeof(DataType)) != sizeof(DataType)) {
        dataStream.setStatus(DataStreamStatus::ReadError);

        data = 0;
    }

    return dataStream;
}

template<typename DeviceType>
inline auto operator >>(DataStream<DeviceType> &dataStream, char *&data) noexcept -> DataStream<DeviceType> &
{
    data = nullptr;

    uint32 size {};
    dataStream >> size;

    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    data = new char[ metaCast<sizeinfo>(size + 1) ];

    if (dataStream.device()->read(data, metaCast<sizeinfo>(size)) != metaCast<sizeinfo>(size)) {
        dataStream.setStatus(DataStreamStatus::ReadError);

        delete[] data;
        data = nullptr;
    } else {
        data[size] = Constants::nullTerminator;
    }

    return dataStream;
}

template<typename DeviceType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::string &data) noexcept -> DataStream<DeviceType> &
{
    data.clear();

    uint32 size {};
    dataStream >> size;

    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    auto buffer = std::vector<char>(metaCast<sizeinfo>(size));

    if (dataStream.device()->read(buffer.data(), metaCast<sizeinfo>(size)) != metaCast<sizeinfo>(size)) {
        dataStream.setStatus(DataStreamStatus::ReadError);

        data.clear();
    } else {
        data.assign(buffer.data(), size);
    }

    return dataStream;
}

//! Sequence containers
template<typename DeviceType,
         typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::vector<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    data.clear();

    uint32 size {};
    dataStream >> size;

    for (decltype(size) i = 0; i < size; ++i) {
        ValueType value {};
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        data.emplace_back(std::move(value));
    }

    return dataStream;
}

template<typename DeviceType,
         typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::deque<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    data.clear();

    uint32 size {};
    dataStream >> size;

    for (decltype(size) i = 0; i < size; ++i) {
        ValueType value {};
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        data.emplace_back(std::move(value));
    }

    return dataStream;
}

template<typename DeviceType,
         typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::forward_list<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    data.clear();

    uint32 size {};
    dataStream >> size;

    auto it = data.cbefore_begin();

    for (decltype(size) i = 0; i < size; ++i) {
        ValueType value {};
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        it = data.emplace_after(it, std::move(value));
    }

    return dataStream;
}

template<typename DeviceType,
         typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::list<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    data.clear();

    uint32 size {};
    dataStream >> size;

    for (decltype(size) i = 0; i < size; ++i) {
        ValueType value {};
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        data.emplace_back(std::move(value));
    }

    return dataStream;
}

//! Associative containers
template<typename DeviceType,
         typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::set<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    data.clear();

    uint32 size {};
    dataStream >> size;

    for (decltype(size) i = 0; i < size; ++i) {
        ValueType value {};
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        data.emplace(std::move(value));
    }

    return dataStream;
}

template<typename DeviceType,
         typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::multiset<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    data.clear();

    uint32 size {};
    dataStream >> size;

    for (decltype(size) i = 0; i < size; ++i) {
        ValueType value {};
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        data.emplace(std::move(value));
    }

    return dataStream;
}

template<typename DeviceType,
         typename KeyType,
         typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::map<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    data.clear();

    uint32 size {};
    dataStream >> size;

    for (decltype(size) i = 0; i < size; ++i) {
        KeyType key {};
        dataStream >> key;

        ValueType value {};
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        data.emplace(std::move(key), std::move(value));
    }

    return dataStream;
}

template<typename DeviceType,
         typename KeyType,
         typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::multimap<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    data.clear();

    uint32 size {};
    dataStream >> size;

    for (decltype(size) i = 0; i < size; ++i) {
        KeyType key {};
        dataStream >> key;

        ValueType value {};
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        data.emplace(std::move(key), std::move(value));
    }

    return dataStream;
}

//! Unordered associative containers
template<typename DeviceType,
         typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::unordered_set<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    data.clear();

    uint32 size {};
    dataStream >> size;

    for (decltype(size) i = 0; i < size; ++i) {
        ValueType value {};
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        data.emplace(std::move(value));
    }

    return dataStream;
}

template<typename DeviceType,
         typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::unordered_multiset<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    data.clear();

    uint32 size {};
    dataStream >> size;

    for (decltype(size) i = 0; i < size; ++i) {
        ValueType value {};
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        data.emplace(std::move(value));
    }

    return dataStream;
}

template<typename DeviceType,
         typename KeyType,
         typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::unordered_map<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    data.clear();

    uint32 size {};
    dataStream >> size;

    for (decltype(size) i = 0; i < size; ++i) {
        KeyType key {};
        dataStream >> key;

        ValueType value {};
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        data.emplace(std::move(key), std::move(value));
    }

    return dataStream;
}

template<typename DeviceType,
         typename KeyType,
         typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::unordered_multimap<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    data.clear();

    uint32 size {};
    dataStream >> size;

    for (decltype(size) i = 0; i < size; ++i) {
        KeyType key {};
        dataStream >> key;

        ValueType value {};
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        data.emplace(std::move(key), std::move(value));
    }

    return dataStream;
}

} // end namespace Io

using Io::DataStreamStatus;
using Io::DataStream;

} // end namespace Calibri

#endif // CALIBRI_IO_DATASTREAM_HPP
