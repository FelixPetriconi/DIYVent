/*******************************************************************************************
*    Copyright 2020 Felix Petriconi
*    Distributed under the Boost Software License, Version 1.0.
*    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
********************************************************************************************/

#include "mainwindow.h"
#include "VentilatorController.h"
#include "FileIODevice.h"
#include <QApplication>
#include <modm/debug/logger.hpp>
#include <modm/driver/io/terminal.hpp>

using namespace DIYV;



DIYV::FileIODevice outputDevice;

modm::log::StyleWrapper< modm::log::Prefix< char[10] > > loggerDeviceDebug( \
        modm::log::Prefix< char[10] >("Debug  : ", outputDevice ));
modm::log::Logger modm::log::debug( loggerDeviceDebug );

modm::log::StyleWrapper< modm::log::Prefix< char[10] > > loggerDeviceInfo( \
        modm::log::Prefix< char[10] >("Info   : ", outputDevice ));
modm::log::Logger modm::log::info( loggerDeviceInfo );

modm::log::StyleWrapper< modm::log::Prefix< char[10] > > loggerDeviceWarning( \
        modm::log::Prefix< char[10] >("Warning: ", outputDevice ));
modm::log::Logger modm::log::warning(loggerDeviceWarning);

modm::log::StyleWrapper< modm::log::Prefix< char[10] > > loggerDeviceError( \
        modm::log::Prefix< char[10] >("Error  : ", outputDevice ));
modm::log::Logger modm::log::error(loggerDeviceError);



int main(int argc, char *argv[])
{
    outputDevice.open("HostApplication.log");

    QApplication a(argc, argv);
    qRegisterMetaType<MeasurementTime>("MeasurementTime");

    VentilatorController controller;
    controller.setTestMode(false);
    MainWindow w;

    w.setControllerCommandFn([&controller](ControllerCommands command) { controller.sendControllerCommand(command); });
    QObject::connect(&controller, SIGNAL(newMeasurement(MeasurementTime)), &w, SLOT(appendNewMeasurements(MeasurementTime)));

    w.show();
    return a.exec();
}
