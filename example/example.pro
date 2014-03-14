TARGET            = skyplotwidget
TEMPLATE          = app
CONFIG           += qt warn_on debug 
MOC_DIR           = tmp
OBJECTS_DIR       = tmp
DEPENDPATH        = .
DESTDIR           = .
QT               += 
INCLUDEPATH       = . ../include/

HEADERS += Window.h
SOURCES += main.cpp Window.cpp
LIBS += -L../lib -lskyplotwidget
