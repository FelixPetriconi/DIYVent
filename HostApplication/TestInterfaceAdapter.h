#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include "Modes.h"
#include "../controller/common/DataTypes.h"
#include "PressureMeasurement.h"

#include <atomic>
#include <functional>
#include <memory>
#include <thread>

#include <QObject>
#include <QTimer>

namespace DIYV
{

class TestInterfaceAdapter;

class DataGenerator : public QObject
{
Q_OBJECT
public:
    DataGenerator(TestInterfaceAdapter& adapter);
    virtual ~DataGenerator();
    void setOperationalMode(OperationalModes mode);

private slots:
    void sendNewData();

private:
    void sender();
    TestInterfaceAdapter& _adapter;
    QTimer _testTimer;
    std::atomic_bool _stop;
    std::atomic_bool _run;
    std::thread _sender;
};


class TestInterfaceAdapter
{   
    friend class DataGenerator;

public:
    TestInterfaceAdapter();
    ~TestInterfaceAdapter();
    TestInterfaceAdapter(TestInterfaceAdapter&&) = default;
    TestInterfaceAdapter& operator=(TestInterfaceAdapter&&) = default;

    void sendControllerCommand(ControllerCommands data);
    void newMeasurementsArrived(const Measurements &values);
    void setNewMeasurementArrived(std::function<void(MeasurementTime)> fn);

private:
    void sendNewData();
    std::unique_ptr<DataGenerator> _dataGenerator;
    std::function<void(MeasurementTime)> _newMeasurementArrivedFn;
};


}

#endif // TESTCONTROLLER_H
