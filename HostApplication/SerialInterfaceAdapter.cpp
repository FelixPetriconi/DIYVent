/*******************************************************************************************
*    Copyright 2020 Felix Petriconi
*    Distributed under the Boost Software License, Version 1.0.
*    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
********************************************************************************************/

#include "SerialInterfaceAdapter.h"

#include "../controller/common/SerializerImpl.h"
#include "../controller/common/SerializationHelper.h"

#include <modm/debug/logger.hpp>
#include <modm/platform/uart/static_serial_interface.hpp>
#include <modm/communication/sab.hpp>
#include <modm/communication/sab2.hpp>

#include <algorithm>
#include <cassert>
#include <QDebug>

using StaticPort = modm::platform::StaticSerialInterface<1>;
using SABMaster = modm::sab2::Interface<StaticPort, DIYV::MaxPayloadLength>;

namespace
{
    modm::platform::SerialInterface port("/dev/ttyUSB1", 38400);
    SABMaster sab;
}

namespace DIYV
{
class SerialInterfaceAdapter::Interface
{
public:
    Interface(SerialInterfaceAdapter& adapter)
        : _adapter(adapter)
    {
        assert(StaticPort::initialize<38400>(port));
        _serialWorker = std::thread([this]{ this->worker(); });
    }

    ~Interface()
    {
        _stop = true;
        _sendConditon.notify_one();
        if (_serialWorker.joinable()) _serialWorker.join();
    }

    void sendCommand(ControllerCommands data)
    {
        std::unique_lock<std::mutex> block{_sendQueueMutex};
        _sendQueue.push(data);
    }

private:

    void worker()
    {
        while (!_stop)
        {
            std::optional<ControllerCommands> command;
            {
                std::unique_lock<std::mutex> block{_sendQueueMutex};

                if (!_sendQueue.empty())
                {
                    command = _sendQueue.front();
                    _sendQueue.pop();
                }
            }

            if (command)
            {
                SerializerSink<MaxPayloadLength> sink;
                sink << *command;
                {
                    sab.sendMessage(0x01, modm::sab::REQUEST, 0x02, sink.payload(), sink.payloadLength());
                    sab.update();
                }
                MODM_LOG_DEBUG << "Start/Stop send";
            }

            sab.update();
            while (sab.isMessageAvailable())
            {
                MODM_LOG_DEBUG << "Messaage available";
                if (sab.getCommand() == 0x01)
                {
                    MODM_LOG_DEBUG << "Measurement arrived";
                    DIYV::SerializerSource source(sab.getPayload(), sab.getPayloadLength());
                    MeasurementTime measurement;

                    source >> measurement.measurement;
                    measurement.timePoint = std::chrono::steady_clock::now();

                    _adapter._newMeasurementArrivedFn(measurement);
                }
                sab.dropMessage();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    SerialInterfaceAdapter& _adapter;
    std::atomic_bool _stop{false};
    std::queue<ControllerCommands> _sendQueue;
    std::mutex _sendQueueMutex;
    std::condition_variable _sendConditon;
    std::thread _serialWorker;
};


SerialInterfaceAdapter::SerialInterfaceAdapter()
    : _interface(new Interface(*this))
{
}

SerialInterfaceAdapter::~SerialInterfaceAdapter()
{
}


void SerialInterfaceAdapter::sendControllerCommand(ControllerCommands data)
{
    _interface->sendCommand(data);
}

void SerialInterfaceAdapter::setNewMeasurementArrived(std::function<void(MeasurementTime)> fn)
{
    _newMeasurementArrivedFn = fn;
}



}
