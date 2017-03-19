TARGET            = skyplotwidget
TEMPLATE          = app
CONFIG           += qt warn_on debug 
MOC_DIR           = tmp
OBJECTS_DIR       = tmp
DEPENDPATH        = .
DESTDIR           = .
QT               += 
INCLUDEPATH       = .
DEFINES          += SKYPLOTWIDGET_STATIC

include(../SkyplotWidget.pri)
!contains(DEFINES, SKYPLOT_QML_SUPPORT) {
    QT += gui widgets
    HEADERS += Window.h
    SOURCES += Window.cpp
} else {
    QT += qml quick
    OTHER_FILES += \
    main.qml
}

SOURCES += main.cpp

RESOURCES += \
    resources.qrc

