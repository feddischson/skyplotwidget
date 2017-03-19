TARGET            = skyplotwidgetdesigner
TEMPLATE          = lib
CONFIG           += qt warn_on plugin
MOC_DIR           = tmp
OBJECTS_DIR       = tmp
DEPENDPATH        = ../include ../src
DESTDIR           = ../lib
INCLUDEPATH      += ../include

DEFINES          += SKYPLOTWIDGET_STATIC

#win32:TEMPLATE             = vclib
win32:CONFIG              += dll 
win32:dll:DEFINES         += QT_DLL
win32:QMAKE_CXXFLAGS      += $$QMAKE_CFLAGS_STL

include(../SkyplotWidget.pri)

!contains(DEFINES, SKYPLOT_QML_SUPPORT) {
    QT      += designer widgets gui
    HEADERS +=  SkyplotWidgetPlugin.h   
    SOURCES +=  SkyplotWidgetPlugin.cpp 
} else {
  QT += qml quick
}

OTHER_FILES += \
    skyplotwidget.json

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

