/*******************************************************************************************
*    Copyright 2020 Felix Petriconi
*    Distributed under the Boost Software License, Version 1.0.
*    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
********************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GraphRenderer.h"
#include "Modes.h"
#include "../controller/common/DataTypes.h"
#include "PressureMeasurement.h"

#include <functional>
#include <memory>

#include <QMainWindow>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


namespace DIYV
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setControllerCommandFn(std::function<void(ControllerCommands)> fn);

public slots:
    void appendNewMeasurements(MeasurementTime values);

private slots:
    void showDisclaimer();
    void startStopPressed(bool);
    void lockedPressed(bool);

private:
    void init();

    Ui::MainWindow *ui;
    std::unique_ptr<GraphRenderer> _renderer;
    QGraphicsScene* _scene;
    std::function<void(ControllerCommands)> _controllerCommandsFn;
};

}

#endif // MAINWINDOW_H
