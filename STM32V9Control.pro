QT       += core gui
QT       += serialport  mqtt
QT       += concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fiocanopen.cpp \
    fiomodbus.cpp \
    fiomqtt.cpp \
    v9canopen.cpp \
    databutton.cpp \
    main.cpp \
    v9mqtt.cpp \
    widget.cpp

HEADERS += \
    fiocanopen.h \
    fiomodbus.h \
    fiomqtt.h \
    v9canopen.h \
    databutton.h \
    v9mqtt.h \
    widget.h

FORMS += \
    fiocanopen.ui \
    fiomodbus.ui \
    fiomqtt.ui \
    v9canopen.ui \
    v9mqtt.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc



INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/CandleApiDriver
include($$PWD/CandleApiDriver/CandleApiDriver.pri)


RC_ICONS = images/logo.ico
