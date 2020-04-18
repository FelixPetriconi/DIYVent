//
// Created by felix on 4/18/20.
//

#include "Serialization.h"

namespace DIYV
{
    void Sink::writeType(DIYV::TypeCode c)
    {
        write(static_cast<const void*>(&c), sizeof(TypeCode));
    }
    bool Source::readType(DIYV::TypeCode expected)
    {
        std::uint8_t code;
        read(&code, sizeof(TypeCode));
        return static_cast<TypeCode>(code) == expected;
    }

    TypeCode Source::readType()
    {
        std::uint8_t code;
        read(&code, sizeof(TypeCode));
        return static_cast<TypeCode>(code);
    }
}