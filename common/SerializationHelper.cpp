//
// Created by felix on 4/18/20.
//

#include "SerializationHelper.h"

#include <algorithm>

namespace DIYV
{
    void serialize(Sink& sink, const char* text, std::uint8_t size)
    {
        sink.writeType(TypeCode::CharArray);
        serialize(sink, size);
        sink.write(text, size);
    }

    bool deserialize(Source& source, char* text, std::uint8_t size)
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