//
// Created by felix on 4/18/20.
//

#ifndef DIYVENTILATOR_SERIALIZATIONHELPER_H
#define DIYVENTILATOR_SERIALIZATIONHELPER_H

#include "Serialization.h"


#include <algorithm>
#include <type_traits>

namespace DIYV
{
    template <typename S, typename T>
    void serializePrimitive(Sink<S>& sink, T value)
    {
        sink.writeType(TypeToTypeCode<T>::value);
        sink.write(&value, sizeof(T));
    }

    template <typename S, typename T>
    bool deSerializePrimitive(Source<S>& source, T& value)
    {
        bool result{false};
        result = source.readType(TypeToTypeCode<T>::value);
        if (!result) return result;

        result = source.read(&value, sizeof(T));
        return result;
    }

    template <typename S, typename T>
    inline Sink<S> & operator <<(Sink<S>& sink, const T &value)
    {
        serialize(sink, value);
        return sink;
    }

    template <typename S, typename T>
    inline Source<S> operator >>(Source<S>& source, T &value)
    {
        deserialize(source, value);
        return source;
    }

    template <typename S, typename T>
    T createFromSource(Source<S>& source)
    {
        T value;
        deserialize(source, value);
        return value;
    }

    template <typename S, typename T>
    std::enable_if_t<std::is_enum_v<T>, void> serialize(Sink<S>& sink, const T& value)
    {
        sink.writeType(TypeCode::Enum);
        sink.write(&value, sizeof(T));
    }

    template <typename S, typename T>
    std::enable_if_t<std::is_enum_v<T>, bool> deserialize(Source<S>& source, T& value)
    {
        auto result{false};
        result = source.readType(TypeCode::Enum);
        result = result && source.read(&value, sizeof(T));
        return result;
    }

    template <typename S, typename T>
    std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, void> serialize(Sink<S>& sink, const T& value)
    {
        serializePrimitive(sink, value);
    }

    template <typename S, typename T>
    std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, bool> deserialize(Source<S>& source, T& value)
    {
        return deSerializePrimitive(source, value);
    }

    template <typename S>
    void serialize(Sink<S>& sink, const char* text, std::uint8_t size)
    {
        sink.writeType(TypeCode::CharArray);
        serialize(sink, size);
        sink.write(text, size);
    }

    template <typename S>
    bool deserialize(Source<S>& source, char* text, std::uint8_t size)
    {
        bool result{false};
        result = (source.readType() == TypeCode::CharArray);
        if (!result) return result;

        std::uint8_t streamSize{0};
        result = deserialize(source, streamSize);
        if (!result) return result;
        result = source.read(text, std::min(streamSize, size));
        if (result && streamSize > size)
        {
            auto remainder = streamSize - size;
            while (remainder > 0 && result) {
                std::uint8_t dummy;
                result = source.read(&dummy, 1);
                --remainder;
            }
        }
        return result;
    }
}

#endif //DIYVENTILATOR_SERIALIZATIONHELPER_H
