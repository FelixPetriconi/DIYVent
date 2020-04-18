//
// Created by felix on 4/18/20.
//

#ifndef DIYVENTILATOR_SERIALIZATIONHELPER_H
#define DIYVENTILATOR_SERIALIZATIONHELPER_H

#include "Serialization.h"

#include <type_traits>

namespace DIYV
{
    template <typename T>
    void serializePrimitive(Sink& sink, T value)
    {
        sink.writeType(TypeToTypeCode<T>::value);
        sink.write(&value, sizeof(T));
    }

    template <typename T>
    bool deSerializePrimitive(Source& source, T& value)
    {
        bool result{false};
        result = source.readType(TypeToTypeCode<T>::value);
        if (!result) return result;

        result = source.read(&value, sizeof(T));
        return result;
    }

    template <typename T>
    inline Sink & operator <<(Sink &sink, const T &value)
    {
        serialize(sink, value);
        return sink;
    }

    template <typename T>
    inline Source& operator >>(Source &source, T &value)
    {
        deserialize(source, value);
        return source;
    }

    template <typename T>
    T createFromSource(Source& source)
    {
        T value;
        deserialize(source, value);
        return value;
    }

    template <typename T>
    std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, void> serialize(Sink& sink, const T value)
    {
        serializePrimitive(sink, value);
    }

    template <typename T>
    std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, bool> deserialize(Source& source, T& value)
    {
        return deSerializePrimitive(source, value);
    }

    void serialize(Sink& sink, const char* text, std::uint8_t size);

    bool deserialize(Source& source, char* text, std::uint8_t size);
}

#endif //DIYVENTILATOR_SERIALIZATIONHELPER_H
