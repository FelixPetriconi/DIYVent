cmake_minimum_required(VERSION 3.15)
project(DIYVentilator)

set(CMAKE_CXX_STANDARD 17)

include_directories(common)
include_directories(HostApplication/HostApplication)

add_executable(DIYVentilator
        common/Serialization.cpp
        common/Serialization.h
        common/SerializationHelper.cpp
        common/SerializationHelper.h
        common/SerializerImpl.h
        HostApplication/HostApplication/GraphRenderer.cpp
        HostApplication/HostApplication/GraphRenderer.h
        HostApplication/HostApplication/main.cpp
        HostApplication/HostApplication/mainwindow.cpp
        HostApplication/HostApplication/mainwindow.h
        HostApplication/HostApplication/moc_mainwindow.cpp
        HostApplication/HostApplication/moc_predefs.h
        HostApplication/HostApplication/moc_TestInterfaceAdapter.cpp
        HostApplication/HostApplication/Modes.h
        HostApplication/HostApplication/PressureMeasurement.h
        HostApplication/HostApplication/SerialInterfaceAdapter.cpp
        HostApplication/HostApplication/SerialInterfaceAdapter.h
        HostApplication/HostApplication/TemplateHelpers.h
        HostApplication/HostApplication/TestInterfaceAdapter.cpp
        HostApplication/HostApplication/TestInterfaceAdapter.h
        HostApplication/HostApplication/TransportObjects.cpp
        HostApplication/HostApplication/TransportObjects.h
        HostApplication/HostApplication/ui_mainwindow.h
        HostApplication/HostApplication/VentilatorController.cpp
        HostApplication/HostApplication/VentilatorController.h)
