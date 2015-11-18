QT += core


TARGET = sneakyTron
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    openglwindow.cpp \
    gamewindow.cpp

HEADERS  += \
    openglwindow.h \
    gamewindow.h
