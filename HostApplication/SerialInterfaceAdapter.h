/*******************************************************************************************
*    Copyright 2020 Felix Petriconi
*    Distributed under the Boost Software License, Version 1.0.
*    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
********************************************************************************************/

#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include "Modes.h"
#include "../controller/common/DataTypes.h"

#include <atomic>
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

#include <QTimer>

namespace DIYV
{

class SerialInterfaceAdapter
{
    class Interface;
    friend class Interface;

public:
    SerialInterfaceAdapter();
    ~SerialInterfaceAdapter();
    SerialInterfaceAdapter(SerialInterfaceAdapter&&) = default;
    SerialInterfaceAdapter& operator=(SerialInterfaceAdapter&&) = default;

    void sendControllerCommand(ControllerCommands data);
    void setNewMeasurementArrived(std::function<void(MeasurementTime)> fn);


private:
    std::unique_ptr<Interface> _interface;
    std::function<void(MeasurementTime)> _newMeasurementArrivedFn;
};

}

#endif // SERIALINTERFACE_H
