/*******************************************************************************************
*    Copyright 2020 Felix Petriconi
*    Distributed under the Boost Software License, Version 1.0.
*    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
********************************************************************************************/

#ifndef DIYVENTILATOR_SERIALIZATION_H
#define DIYVENTILATOR_SERIALIZATION_H

#include "TemplateHelpers.h"

#include <cstdint>

namespace DIYV
{
    enum class TypeCode : std::uint8_t
    {
        Bool,
        SignedInt8,
        UnsignedInt8,
        SignedInt16,
        UnsignedInt16,
        SignedInt32,
        UnsignedInt32,
        Float,
        Double,
        Enum,
        Char,
        CharArray
    };

    template <typename T>
    struct TypeToTypeCode;

    template<> struct TypeToTypeCode<bool> { static constexpr TypeCode value = TypeCode::Bool; };
    template<> struct TypeToTypeCode<std::int8_t> { static constexpr TypeCode value = TypeCode::SignedInt8; };
    template<> struct TypeToTypeCode<std::uint8_t> { static constexpr TypeCode value = TypeCode::UnsignedInt8; };
    template<> struct TypeToTypeCode<std::int16_t> { static constexpr TypeCode value = TypeCode::SignedInt16; };
    template<> struct TypeToTypeCode<std::uint16_t> { static constexpr TypeCode value = TypeCode::UnsignedInt16; };
    template<> struct TypeToTypeCode<std::int32_t> { static constexpr TypeCode value = TypeCode::SignedInt32; };
    template<> struct TypeToTypeCode<std::uint32_t> { static constexpr TypeCode value = TypeCode::UnsignedInt32; };
    template<> struct TypeToTypeCode<float> { static constexpr TypeCode value = TypeCode::Float; };
    template<> struct TypeToTypeCode<double> { static constexpr TypeCode value = TypeCode::Double; };
    template<> struct TypeToTypeCode<char> { static constexpr TypeCode value = TypeCode::Char; };

    template <typename Derived>
    class Sink : public crtp<Derived, Sink>
    {
    public:
        void writeType(TypeCode c)
        {
            write(static_cast<const void*>(&c), sizeof(TypeCode));
        }


        void write(const void* data, std::uint16_t size)
        {
            std::uint16_t i = 0;
            while (i < size)
            {
                write(reinterpret_cast<const std::uint8_t*>(data)[i]);
                ++i;
            }
        }

        
        void write(std::uint8_t val)
        {
            this->underlying().writeImpl(val);
        }
    };

    template <typename Derived>
    class Source : public crtp<Derived, Source>
    {
    public:
        bool readType(TypeCode expected)
        {
            std::uint8_t code;
            read(&code, sizeof(TypeCode));
            return static_cast<TypeCode>(code) == expected;
        }

        TypeCode readType()
        {
            std::uint8_t code;
            read(&code, sizeof(TypeCode));
            return static_cast<TypeCode>(code);
        }

        bool read(std::uint8_t& data)
        {
            return this->underlying().readImpl(data);
        }

        bool read(void* data, std::uint16_t size)
        {
            std::uint16_t i = 0;
            auto result{true};
            while (result && i < size)
            {
                result = result && read(reinterpret_cast<std::uint8_t*>(data)[i]);
                ++i;
            }
            return result;
        }

    };
}

#endif //DIYVENTILATOR_SERIALIZATION_H
