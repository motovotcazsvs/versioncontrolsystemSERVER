QT += core network sql
QT -= gui

CONFIG += c++11

TARGET = versioncontrolsystemSERVER
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    tcpipastm.cpp

HEADERS += \
    tcpipastm.h
