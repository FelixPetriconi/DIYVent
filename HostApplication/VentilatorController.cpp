/*******************************************************************************************
*    Copyright 2020 Felix Petriconi
*    Distributed under the Boost Software License, Version 1.0.
*    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
********************************************************************************************/

#include "VentilatorController.h"

namespace DIYV
{

VentilatorController::VentilatorController()
    : _adapter(TestInterfaceAdapter{})
{

}

void VentilatorController::setTestMode(bool mode)
{
    if (mode)
    {
        _adapter.emplace<1>();
    }
    else
    {
        _adapter.emplace<0>();
    }
    std::visit([&](auto& item) { item.setNewMeasurementArrived([this](const auto& data){ this->newMeasurementArrivedFromController(data); }); }, _adapter);
}

void VentilatorController::sendControllerCommand(ControllerCommands command)
{
    std::visit([&](auto& item) { item.sendControllerCommand(command); }, _adapter );
}

void VentilatorController::newMeasurementArrivedFromController(MeasurementTime data)
{
    emit newMeasurement(data);
}

}
