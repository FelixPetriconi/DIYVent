/*******************************************************************************************
*    Copyright 2020 Felix Petriconi
*    Distributed under the Boost Software License, Version 1.0.
*    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
********************************************************************************************/

#ifndef _DATA_TYPES_
#define _DATA_TYPES_

#include "Serialization.h"

#include <chrono>
#include <vector>

namespace DIYV
{
    struct VentilationSettings
    {
        float peep=0.0;
        float maxPressure=0.0;
        float irRatio=0.0;
        float frequency=0.0;
    };

    template <typename T>
    void serialize(Sink<T>& sink, const VentilationSettings& settings)
    {
        serialize(sink, settings.peep);
        serialize(sink, settings.maxPressure);
        serialize(sink, settings.irRatio);
        serialize(sink, settings.frequency);
    }

    template <typename T>
    bool deserialize(Source<T>& source, VentilationSettings& settings)
    {
        bool result{true};
        result = result && deserialize(source, settings.peep);
        result = result && deserialize(source, settings.maxPressure);
        result = result && deserialize(source, settings.irRatio);
        result = result && deserialize(source, settings.frequency);
        return result;
    }


    enum class TherapyMode : std::uint8_t
    {
        PCV
    };

    enum class Command : std::uint8_t
    {
        Stop,
        Start,
        Calibrate,
        SelftTest
    };

    struct Measurement
    {
        std::int32_t status=0;
        std::int32_t pressure=0;
        std::int32_t o2=0;
        std::int32_t c02=0;
    };

    struct MeasurementTime
    {
        Measurement measurement;
        std::chrono::steady_clock::time_point timePoint;
    };

    using Measurements = std::vector<MeasurementTime>;


    template <typename T>
    void serialize(Sink<T>& sink, const Measurement& measurement)
    {
        serialize(sink, measurement.status);
        serialize(sink, measurement.pressure);
        serialize(sink, measurement.o2);
        serialize(sink, measurement.c02);
    }

    template <typename T>
    bool deserialize(Source<T>& source, Measurement& measurement)
    {
        bool result{true};
        result = result && deserialize(source, measurement.status);
        result = result && deserialize(source, measurement.pressure);
        result = result && deserialize(source, measurement.o2);
        result = result && deserialize(source, measurement.c02);
        return result;
    }

    struct ControllerCommands
    {
        Command command = Command::Stop;
        VentilationSettings settings;
    };

    template <typename T>
    void serialize(Sink<T>& sink, const ControllerCommands& command)
    {
        serialize(sink, command.command);
        serialize(sink, command.settings);
    }

    template <typename T>
    bool deserialize(Source<T>& source, ControllerCommands& command)
    {
        auto result{true};
        result = result && deserialize(source, command.command);
        result = result && deserialize(source, command.settings);
        return result;
    }
}


#endif
