INCLUDEPATH    += . $$PWD/include
HEADERS        += $$PWD/include/SkyplotWidget.h $$PWD/include/SkyplotWidget_global.h
SOURCES        += $$PWD/src/SkyplotWidget.cpp
CONFIG         += c++11 # set -std=c++0x
unix
{
 QMAKE_CXXFLAGS += -Werror
 QMAKE_CXXFLAGS += -Wextra
}
CONFIG         += warn_on #

VER_MAJ = 2
VER_MIN = 0
VER_PAT = 0
VERSION = 2.0.0
DEFINES += _SKP_VERSION=\\\"$$VERSION\\\"
DEFINES += _SKP_VERSION_MAJ=$$VER_MAJ
DEFINES += _SKP_VERSION_MIN=$$VER_MIN
DEFINES += _SKP_VERSION_PAT=$$VER_PAT

