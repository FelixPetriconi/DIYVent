//
// Created by felix on 4/18/20.
//

#ifndef DIYVENTILATOR_SERIALIZERIMPL_H
#define DIYVENTILATOR_SERIALIZERIMPL_H

#include "Serialization.h

namespace DIYV
{
    template <typename T>
    class SerializerImpl : public Sink, public Source
    {
        T& _interface;
    public:

        virtual ~SerializerImpl() = default;
        void write(const void* data, std::uint16_t size) override
        {
            _interface.writeBytes(reinterpret_cast<const std::uint8_t*>(data), size);
        }

        bool read(void* data, std::uint16_t size) override
        {
            _interface.readBytes(reinterpret_cast<std::uint8_t*>(data), size);
        }
    };
}

#endif //DIYVENTILATOR_SERIALIZERIMPL_H
