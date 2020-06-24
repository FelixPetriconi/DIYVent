/*******************************************************************************************
*    Copyright 2020 Felix Petriconi
*    Distributed under the Boost Software License, Version 1.0.
*    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
********************************************************************************************/

#include "TestInterfaceAdapter.h"
#include <cmath>
#include <QObject>
#include <QTimer>

namespace
{
    const auto ramp = 200;
    const auto inspiration = 1000 - ramp;
    const auto exspiration = inspiration + 2000;
    const auto peep = 8;
    const auto maxp = 28;
    const auto interval = 10;
    const auto updateInterval = 100;
    const auto MillisecondsPerMinute = 60000;

    auto calculateTestPressure(int tms)
    {
        if (tms < ramp)
        {
            return peep + static_cast<int>(std::round(tms* (maxp-peep) / ramp));
        }
        else if (tms < inspiration)
        {
            return maxp;
        }
        else if (tms < exspiration)
        {
            return static_cast<int>(std::round(maxp - (tms-inspiration) * (maxp-peep) / (exspiration-inspiration)));
        }
        else
        {
            return 0;
        }
    }

    std::chrono::steady_clock::time_point currentTimePoint;
}

namespace DIYV
{

DataGenerator::DataGenerator(TestInterfaceAdapter& adapter)
    : _adapter(adapter)
    , _stop(false)
    , _run(false)
    , _sender([this]{ this->sender(); })
{
    //_testTimer.setSingleShot(false);
    //connect(&_testTimer, SIGNAL(timeout()), this, SLOT(sendNewData()));
}

DataGenerator::~DataGenerator()
{
    _stop = true;
    _sender.join();
}

void DataGenerator::sender()
{
    while (!_stop)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (_run) sendNewData();
    }
}

void DataGenerator::setOperationalMode(OperationalModes mode)
{
    switch (mode)
    {
    case OperationalModes::Stop:
        _run = false;
        //_testTimer.stop();
        break;
    case OperationalModes::Start:
        _run = true;//_testTimer.start(updateInterval);
        break;
    default:
        assert(!"Unknown mode");

    }
}


void DataGenerator::sendNewData()
{
    _adapter.sendNewData();
}


TestInterfaceAdapter::TestInterfaceAdapter()
    : _dataGenerator(new DataGenerator(*this))
{
}

TestInterfaceAdapter::~TestInterfaceAdapter()
{
}

void TestInterfaceAdapter::sendControllerCommand(ControllerCommands data)
{
    if (data.command == Command::Start)
    {
        currentTimePoint = std::chrono::steady_clock::now();
        _dataGenerator->setOperationalMode(OperationalModes::Start);
    }
    else
    {
        _dataGenerator->setOperationalMode(OperationalModes::Stop);
    }
}

void TestInterfaceAdapter::setNewMeasurementArrived(std::function<void (MeasurementTime)> fn)
{
    _newMeasurementArrivedFn = fn;
}

void TestInterfaceAdapter::sendNewData()
{
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - currentTimePoint).count();
    MeasurementTime measurement;
    measurement.measurement.pressure = calculateTestPressure(elapsed % (MillisecondsPerMinute / 25));
    measurement.timePoint = std::chrono::steady_clock::now();
    _newMeasurementArrivedFn(measurement);
}


}
