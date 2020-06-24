
#ifndef _TESTMEASUREMENT_
#define _TESTMEASUREMENT_

#include "common/DataTypes.h"

#include <modm/processing/timer/timestamp.hpp>

namespace DIYV
{

class TestMeasurement
{
public:
	void setSettings(DIYV::ControllerCommands commands);

	DIYV::Measurement measurement();

public:
	DIYV::ControllerCommands _commands;
	modm::Timestamp _startMeasurement;
};

}
#endif