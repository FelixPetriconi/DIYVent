#ifndef VENTILATORCONTROLLER_H
#define VENTILATORCONTROLLER_H

#include "SerialInterfaceAdapter.h"
#include "TestInterfaceAdapter.h"

#include <functional>
#include <variant>
#include <QObject>

namespace DIYV
{

class VentilatorController : public QObject
{
    Q_OBJECT
public:
    VentilatorController();

    void setTestMode(bool mode);

    void sendControllerCommand(ControllerCommands command);

signals:
    void newMeasurement(MeasurementTime);

private:
    std::variant<SerialInterfaceAdapter, TestInterfaceAdapter> _adapter;
    void newMeasurementArrivedFromController(MeasurementTime data);
};

}


#endif // VENTILATORCONTROLLER_H
