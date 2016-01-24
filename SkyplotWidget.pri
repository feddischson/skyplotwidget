INCLUDEPATH += . $$PWD/include
HEADERS += $$PWD/include/SkyplotWidget.h $$PWD/include/SkyplotWidget_global.h
SOURCES += $$PWD/src/SkyplotWidget.cpp
VERSION  = 2.0.0
DEFINES += _SKP_VERSION=\\\"$$VERSION\\\"
CONFIG += c++11 # set -std=c++0x

QMAKE_CXXFLAGS += -Werror # set -werror
QMAKE_CXXFLAGS += -Wextra # set -wextra
CONFIG         += warn_on#
