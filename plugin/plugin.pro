TARGET            = skyplotwidgetdesigner
TEMPLATE          = lib
CONFIG           += qt warn_on debug designer plugin 
MOC_DIR           = tmp
OBJECTS_DIR       = tmp
DEPENDPATH        = ../include ../src
DESTDIR           = ../lib

INCLUDEPATH      += ../include
VERSION           = 1.0.1


#win32:TEMPLATE             = vclib
win32:CONFIG              += dll 
win32:dll:DEFINES         += QT_DLL
win32:QMAKE_CXXFLAGS      += $$QMAKE_CFLAGS_STL



HEADERS +=  SkyplotWidgetPlugin.h   ../include/SkyplotWidget.h
SOURCES +=  SkyplotWidgetPlugin.cpp ../src/SkyplotWidget.cpp

