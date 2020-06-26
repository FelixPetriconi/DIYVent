/*
 * Copyright (c) 2010-2011, Fabian Greif
 * Copyright (c) 2012-2014, 2017, Niklas Hauser
 * Copyright (c) 2013, Sascha Schade
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include "DisplayIODevice.hpp"
#include "TestMeasurement.h"

#include "common/Serialization.h"
#include "common/SerializationHelper.h"
#include "common/SerializerImpl.h"
#include "common/DataTypes.h"

#include <modm/board.hpp>
#include <modm/io/iostream.hpp>
#include <modm/platform.hpp>
#include <modm/driver/display/ssd1306.hpp>
#include <modm/communication/sab2.hpp>

using namespace modm::literals;
using namespace modm::platform;

typedef A4 Sda;
typedef A5 Scl;
typedef I2cMaster MyI2cMaster;

modm::Ssd1306<MyI2cMaster> *logDisplay = nullptr;
modm::sab2::Interface<Uart0, DIYV::MaxPayloadLength> sab;

modm::Ssd1306<MyI2cMaster> display;
DIYV::DisplayIODevice<modm::Ssd1306<MyI2cMaster>> ioDevice(display);

modm::log::Logger myDebug(ioDevice);
modm::log::Logger myInfo(ioDevice);
modm::log::Logger myWarning(ioDevice);
modm::log::Logger myError(ioDevice);

void init()
{
    SystemClock::enable();

    Uart0::connect<D1::Txd, D0::Rxd>();
    Uart0::initialize<SystemClock, 38400>();

    enableInterrupts();    

    MyI2cMaster::connect<Scl::Scl, Sda::Sda>();
    MyI2cMaster::initialize<Board::SystemClock, 400_kHz>();   
}

int
main()
{
    init();

    display.initializeBlocking();
    display.clear();
    display.setFont(modm::font::AllCaps3x5);
    display << "Ventilator Controller";
    display.update();

    DIYV::TestMeasurement measurment;

    modm::ShortPeriodicTimer measurementTimer(100ms);  
    DIYV::ControllerCommands commands;

    int messages{0};

    while (true)
    {
        sab.update();
        while (sab.isMessageAvailable()) 
        {
            if (/*(sab.getAddress() == 0x01) &*/ (sab.getCommand() == 0x02)) 
            {
                DIYV::SerializerSource source(sab.getPayload(), sab.getPayloadLength());

                source >> commands;

                if  (commands.command == DIYV::Command::Start) 
                {
                    measurment.setSettings(commands);

                    display.setCursor(0,20);
                    display << "Start  ";
                    display.setCursor(0,30);
                    display << "p:" << static_cast<std::int32_t>(commands.settings.peep)
                        << " mp:" << static_cast<std::int32_t>(commands.settings.maxPressure)
                        << " ir:" << static_cast<std::int32_t>(commands.settings.irRatio)
                        << " f:" << static_cast<std::int32_t>(commands.settings.frequency);

                    display.update();
                }
                else if (commands.command == DIYV::Command::Stop)
                { 
                    display.setCursor(0,20);
                    display << "Stop  ";
                    display.update();
                }
            }
            sab.dropMessage();
        }

        if (measurementTimer.execute())
        {
            measurementTimer.restart();
            if (commands.command == DIYV::Command::Start)
            {
                auto m = measurment.measurement();
                display.setCursor(0,40);
                display << "P: " << m.pressure;
                display.update();

                DIYV::SerializerSink<128> sink;
                sink << m;

                sab.sendMessage(0x01, modm::sab::REQUEST, 0x01, sink.payload(), sink.payloadLength());
                sab.update();
            }
        }
    }
}

