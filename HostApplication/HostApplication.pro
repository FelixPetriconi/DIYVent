QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++1z
QMAKE_CXX_FLAGS += -Wall

unix {
  contains(QMAKE_HOST.arch, arm.*):{
      QMAKE_CXX_FLAGS += -Wno-psabi
      QMAKE_CC=gcc-9.1
      QMAKE_CXX=g++-9.1
    }else {
      QMAKE_CC=clang-9
      QMAKE_CXX=clang++-9
    }
}

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
    ../controller/common/DataTypes.cpp \
    ../controller/common/Serialization.cpp \
    ../controller/common/SerializationHelper.cpp \
    ../controller/common/SerializerImpl.cpp \
    ../modm/src/modm/communication/sab2/interface.cpp \
    ../modm/src/modm/driver/io/terminal.cpp \
    ../modm/src/modm/io/iostream.cpp \
    ../modm/src/modm/io/iostream_printf.cpp \
    ../modm/src/modm/platform/uart/serial_interface.cpp \
    FileIODevice.cpp \
    GraphRenderer.cpp \
    SerialInterfaceAdapter.cpp \
    TestInterfaceAdapter.cpp \
    VentilatorController.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../controller/common/DataTypes.h \
    ../controller/common/Serialization.h \
    ../controller/common/SerializationHelper.h \
    ../controller/common/SerializerImpl.h \
    ../controller/common/TemplateHelpers.h \
    ../modm/src/modm/communication/sab.hpp \
    ../modm/src/modm/communication/sab2.hpp \
    ../modm/src/modm/communication/sab2/constants.hpp \
    ../modm/src/modm/communication/sab2/interface.hpp \
    ../modm/src/modm/communication/sab2/interface_impl.hpp \
    FileIODevice.h \
    GraphRenderer.h \
    Modes.h \
    PressureMeasurement.h \
    SerialInterfaceAdapter.h \
    TestInterfaceAdapter.h \
    VentilatorController.h \
    mainwindow.h

INCLUDEPATH += /usr/include/arm-linux-gnueabihf \
              ../ \
              ../modm/src/ \
              ../modm/ext/

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    HostApplication_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
