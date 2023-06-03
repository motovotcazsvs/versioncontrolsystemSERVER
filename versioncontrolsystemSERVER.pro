QT += core network sql
QT -= gui

CONFIG += c++11

TARGET = versioncontrolsystemSERVER
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    tcpipastm.cpp \
    database.cpp \
    control.cpp \
    actions.cpp

HEADERS += \
    tcpipastm.h \
    database.h \
    control.h \
    actions.h
