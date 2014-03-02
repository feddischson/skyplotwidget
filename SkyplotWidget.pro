TARGET            = skyplotwidget
TEMPLATE          = lib
CONFIG           += qt warn_on debug designer plugin static
MOC_DIR           = tmp
OBJECTS_DIR       = tmp
INCLUDEPATH       = include
DEPENDPATH        = include src
DESTDIR           = lib
QT               += 


unix:VERSION            = 1.0.0


#win32:TEMPLATE             = vclib
win32:CONFIG              += dll 
win32:dll:DEFINES         += QT_DLL
win32:QMAKE_CXXFLAGS      += $$QMAKE_CFLAGS_STL


# Input
HEADERS +=  include/SkyplotWidget.h           \ 
            include/SkyplotWidgetPlugin.h     

SOURCES +=  src/SkyplotWidget.cpp         \
            src/SkyplotWidgetPlugin.cpp 



