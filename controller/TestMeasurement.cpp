#include "TestMeasurement.h"

#include <modm/architecture/interface/clock.hpp>

namespace
{
	const long MillisecondsPerMinute = 60l * 1000;
}

namespace DIYV
{
	void TestMeasurement::setSettings(ControllerCommands commands)
	{
		_commands = commands;
		_startMeasurement = modm::Clock::now(); 
	}


	Measurement TestMeasurement::measurement()
	{
		Measurement result;

	    std::int32_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(modm::Clock::now() - _startMeasurement).count();
	    std::int32_t tms = elapsed % static_cast<std::int32_t>((static_cast<float>(MillisecondsPerMinute) / _commands.settings.frequency));
	    
	    const float period = static_cast<float>(MillisecondsPerMinute) / _commands.settings.frequency;
	    const float inspiration = period * _commands.settings.irRatio;
	    const float ramp = inspiration / 5.0;
	    const float exspiration = period;
	    const float t = static_cast<float>(tms);

	    if (t < ramp)
	    {
	        result.pressure = _commands.settings.peep + static_cast<std::int32_t>(t * (_commands.settings.maxPressure-_commands.settings.peep) / ramp + 0.5);
	    }
	    else if (t < inspiration)
	    {
	        result.pressure = _commands.settings.maxPressure;
	    }
	    else if (t < exspiration)
	    {
	        result.pressure = static_cast<std::int32_t>(_commands.settings.maxPressure - (t-inspiration) * (_commands.settings.maxPressure-_commands.settings.peep) / (exspiration-inspiration) + 0.5);
	    }
	    else
	    {
	        result.pressure = 0;
	    }

	    return result;
	}

}