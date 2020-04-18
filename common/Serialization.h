//
// Created by felix on 4/18/20.
//

#ifndef DIYVENTILATOR_SERIALIZATION_H
#define DIYVENTILATOR_SERIALIZATION_H

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

    class Sink
    {
    public:
        virtual ~Sink() = default;
        void writeType(TypeCode c);
        virtual void write(const void* data, std::uint16_t size) = 0;
    };

    class Source
    {
    public:
        virtual ~Source() = default;
        bool readType(TypeCode expected);
        TypeCode readType();
        virtual bool read(void* data, std::uint16_t size) = 0;
    };
}

#endif //DIYVENTILATOR_SERIALIZATION_H
