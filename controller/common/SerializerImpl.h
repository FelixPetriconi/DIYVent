//
// Created by felix on 4/18/20.
//

#ifndef DIYVENTILATOR_SERIALIZERIMPL_H
#define DIYVENTILATOR_SERIALIZERIMPL_H

#include "Serialization.h"
#include <cctype>

namespace DIYV
{
    constexpr std::size_t MaxPayloadLength = 128;

    template <std::size_t PayloadLength>
    class SerializerSink : public Sink<SerializerSink<PayloadLength>>
    {
         std::uint8_t _payload[MaxPayloadLength];
         std::size_t _payloadLength = 0;
    public:
        SerializerSink() : _payloadLength(0) {}

        void writeImpl(std::uint8_t data)
        {
            if (_payloadLength == MaxPayloadLength) return;
            _payload[_payloadLength] = data;
            ++_payloadLength;
        }

        std::size_t payloadLength() const 
        {
            return _payloadLength;
        }

        const std::uint8_t* payload() const 
        {
            return _payload;
        }
    };

    class SerializerSource : public Source<SerializerSource>
    {
        const std::uint8_t* _payload;
        const std::size_t _payloadLength;
        std::size_t _usedPayload = 0;
    public:
        SerializerSource(const std::uint8_t* payload, std::size_t payloadLength)
            : _payload(payload)
            , _payloadLength(payloadLength)
        {
        }


        bool readImpl(std::uint8_t& data)
        {
            if (_usedPayload == _payloadLength) return false;
            data = _payload[_usedPayload];
            ++_usedPayload;
            return true;
        }
    };
}

#endif //DIYVENTILATOR_SERIALIZERIMPL_H
