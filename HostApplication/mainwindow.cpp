/*******************************************************************************************
*    Copyright 2020 Felix Petriconi
*    Distributed under the Boost Software License, Version 1.0.
*    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
********************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../controller/common/DataTypes.h"

#include <modm/debug/logger.hpp>
#include <QMessageBox>
#include <QTimer>

void log(const char* text);

namespace DIYV
{

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    QTimer::singleShot(0, this, SLOT(showDisclaimer()));
}

MainWindow::~MainWindow()
{
    _renderer.reset();
    delete ui;
}

void MainWindow::setControllerCommandFn(std::function<void(ControllerCommands)> fn)
{
    _controllerCommandsFn = fn;
}

void MainWindow::appendNewMeasurements(MeasurementTime value)
{
    if (ui->_startStop->isChecked())
    {
        _renderer->appendNewValue(value);
    }
}


void MainWindow::init()
{
    connect(ui->_startStop, SIGNAL(clicked(bool)), this, SLOT(startStopPressed(bool)));
    connect(ui->_screenLocked, SIGNAL(clicked(bool)), this, SLOT(lockedPressed(bool)));

    ui->_therapyMode->insertItem(0, tr("PCV"));
    ui->_screenLocked->setChecked(false);
    ui->_startStop->setChecked(false);

    _scene = new QGraphicsScene(0, 0, 640, 330, this);
    ui->_graphicsView->setScene(_scene);
    ui->_graphicsView->setSceneRect(0, 0, 640, 330);
    _renderer = std::make_unique<GraphRenderer>(*_scene);
    _renderer->setRecentTimeWindow(std::chrono::milliseconds(12000));

    startStopPressed(false);
    lockedPressed(false);
}

void MainWindow::showDisclaimer()
{
    QMessageBox messageBox(QMessageBox::Warning, "Disclaimer",
                           tr("This is not a medical device and\nit must not be used in a clinical environment.\nDo you accept?"),
                           QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No, this);

    messageBox.move(size().width()-messageBox.size().width() / 2, size().height()-messageBox.size().height() / 2);
    auto choice = messageBox.exec();

    if (choice != QMessageBox::StandardButton::Yes)
    {
        qApp->quit();
    }
}

void MainWindow::startStopPressed(bool value)
{
    MODM_LOG_DEBUG << "Start/Stop pressed" << modm::flush;

    ui->_startStop->setText(value? tr("Stop") : tr("Start"));
    ControllerCommands command{value? Command::Start : Command::Stop, {}};
    auto& settings = command.settings;
    settings.peep = ui->_peep->value();
    settings.maxPressure = ui->_maxPressure->value();
    settings.irRatio = ui->_irRatio->value();
    settings.frequency = ui->_frequency->value();
    if (_controllerCommandsFn) _controllerCommandsFn(command);

    if (value)
    {
        _renderer->start();
    }
}

void MainWindow::lockedPressed(bool locked)
{
    ui->_screenLocked->setText(locked? tr("Unlock") : tr("Lock"));
    ui->_therapyMode->setEnabled(!locked);
    ui->_peep->setEnabled(!locked);
    ui->_maxPressure->setEnabled(!locked);
    ui->_irRatio->setEnabled(!locked);
    ui->_frequency->setEnabled(!locked);
}

}
