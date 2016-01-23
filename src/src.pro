TARGET            = skyplotwidget
TEMPLATE          = lib
CONFIG           += qt warn_on debug
MOC_DIR           = tmp
OBJECTS_DIR       = tmp
INCLUDEPATH       = ../include
DEPENDPATH        = ../include ../src
DESTDIR           = ../lib
VERSION           = 1.0.1

include(../SkyplotWidget.pri)

!contains(DEFINES, SKYPLOT_QML_SUPPORT) {
    QT += gui widgets designer
} else {
    QT += qml quick
}

isEmpty(PREFIX) {
  PREFIX=/usr/local
}

unix {
    INSTALLBASE    = /usr/local/
}

win32 {
    INSTALLBASE    = C:/skyplotwidget-$$VERSION
}
headers.path   = $$INSTALLBASE/include/
target.path    = $$INSTALLBASE/lib
headers.files  = $$HEADERS



#win32:TEMPLATE            = vclib
win32:CONFIG              += dll 
win32:dll:DEFINES         += QT_DLL
win32:QMAKE_CXXFLAGS      += $$QMAKE_CFLAGS_STL

INSTALLS += target headers
