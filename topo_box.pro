#-------------------------------------------------
#
# Project created by QtCreator 2021-01-21T12:26:26
#
#-------------------------------------------------

QT       += core gui webenginewidgets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = topo_box
TEMPLATE = app
CONFIG += c++11
CONFIG += resource_big
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Simulator.cpp \
    WTraffic.cpp \
    dialogplaysimulator.cpp \
    dialogresult.cpp \
    loader.cpp \
        main.cpp \
        mainwindow.cpp \
    Fiber.cpp \
    FiberLink.cpp \
    PhysicalNode.cpp \
    VirtualLink.cpp \
    VirtualNode.cpp \
    Weaver.cpp \
    WLink.cpp \
    WNode.cpp \
    dialogaddnode.cpp \
    qtadapter.cpp \
    dialogaddfiberlink.cpp \
    dialoglinkres.cpp \
    dialogaddfiberlink.cpp \
    dialogaddnode.cpp \
    dialoglinkres.cpp \
    Fiber.cpp \
    FiberLink.cpp \
    main.cpp \
    mainwindow.cpp \
    PhysicalNode.cpp \
    qtadapter.cpp \
    VirtualLink.cpp \
    VirtualNode.cpp \
    Weaver.cpp \
    WLink.cpp \
    WNode.cpp \
    bmapbridge.cpp

HEADERS += \
    DAlgorithm.hpp \
    Simulator.h \
    WTraffic.h \
    dialogplaysimulator.h \
    dialogresult.h \
    loader.h \
        mainwindow.h \
    Fiber.h \
    FiberLink.h \
    PhysicalNode.h \
    VirtualLink.h \
    VirtualNode.h \
    Weaver.h \
    WLink.h \
    WNode.h \
    dialogaddnode.h \
    qtadapter.h \
    dialogaddfiberlink.h \
    dialoglinkres.h \
    dialogaddfiberlink.h \
    dialogaddnode.h \
    dialoglinkres.h \
    Fiber.h \
    FiberLink.h \
    mainwindow.h \
    PhysicalNode.h \
    qtadapter.h \
    VirtualLink.h \
    VirtualNode.h \
    Weaver.h \
    WLink.h \
    WNode.h \
    bmapbridge.h

FORMS += \
    dialogplaysimulator.ui \
    dialogresult.ui \
        mainwindow.ui \
    dialogaddnode.ui \
    dialogaddfiberlink.ui \
    dialoglinkres.ui

RESOURCES += \
    resource.qrc

