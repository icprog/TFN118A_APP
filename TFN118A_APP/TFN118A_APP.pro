#-------------------------------------------------
#
# Project created by QtCreator 2017-07-18T11:16:33
#
#-------------------------------------------------

QT       += core gui
QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TFN118A_APP
TEMPLATE = app
DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += main.cpp\
        dialog.cpp \
    configpage.cpp \
    userpage.cpp \
    updatepage.cpp \
    serial.cpp \
    packet.cpp \
    crc16.cpp

HEADERS  += dialog.h \
    configpage.h \
    userpage.h \
    updatepage.h \
    serial.h \
    packet.h \
    crc16.h

RESOURCES   += dialog.qrc


