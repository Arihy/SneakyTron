QT += core
QMAKE_CXXFLAGS += -stdlib=libc++ -std=c++11
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


RESOURCES += gestionnaire.qrc

DISTFILES += \
    player.frag \
    player.vert
