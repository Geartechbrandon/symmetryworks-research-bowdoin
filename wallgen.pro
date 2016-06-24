#-------------------------------------------------
#
# Project created by QtCreator 2011-07-27T01:31:44
#
#-------------------------------------------------

QT       += core gui
QT       += widgets printsupport
QT       += charts

TARGET = wallgen
TEMPLATE = app


SOURCES += \
    main.cpp \
    interface.cpp \
    display.cpp \
    colorwheel.cpp \
    functions.cpp \
    port.cpp \
    mainwindow.cpp \
    renderthread.cpp

HEADERS  += \
    interface.h \
    geomath.h \
    display.h \
    colorwheel.h \
    functions.h \
    pairs.h \
    port.h \
    mainwindow.h \
    renderthread.h

RESOURCES += \
    softwareresources.qrc
