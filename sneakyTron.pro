QT += core

TARGET = sneakyTron
CONFIG -= app_bundle
INSTALLS += target

TEMPLATE = app

SOURCES += main.cpp \
    openglwindow.cpp \
    gamewindow.cpp \
    player.cpp

HEADERS  += \
    openglwindow.h \
    gamewindow.h \
    player.h
