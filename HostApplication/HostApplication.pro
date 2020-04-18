QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++1z
#QMAKE_CXX_FLAGS += -std=c++17

QMAKE_CC=gcc-9.1
QMAKE_CXX=g++-9.1

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../common/Serialization.cpp \
    ../common/SerializationHelper.cpp \
    GraphRenderer.cpp \
    SerialInterfaceAdapter.cpp \
    TestInterfaceAdapter.cpp \
    TransportObjects.cpp \
    VentilatorController.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../common/Serialization.h \
    ../common/SerializationHelper.h \
    ../common/SerializerImpl.h \
    GraphRenderer.h \
    Modes.h \
    PressureMeasurement.h \
    SerialInterfaceAdapter.h \
    TemplateHelpers.h \
    TestInterfaceAdapter.h \
    TransportObjects.h \
    VentilatorController.h \
    mainwindow.h

INCLUDEPATH += /usr/include/arm-linux-gnueabihf

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    HostApplication_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
