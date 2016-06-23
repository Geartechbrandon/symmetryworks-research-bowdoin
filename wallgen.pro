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
    mainwindow.cpp

HEADERS  += \
    interface.h \
    geomath.h \
    display.h \
    colorwheel.h \
    functions.h \
    pairs.h \
    mainwindow.h

RESOURCES += \
    softwareresources.qrc
