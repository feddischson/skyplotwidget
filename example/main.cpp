#ifndef SKYPLOT_QML_SUPPORT
#include <QApplication>

#include "Window.h"
#else
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "SkyplotWidget.h"
#endif

int main(int argc, char *argv[]) {
#ifndef SKYPLOT_QML_SUPPORT
   QApplication app(argc, argv);
   Window window;

   QPalette p(window.palette());
   p.setColor(QPalette::Background, Qt::black);
   window.setPalette(p);

   window.show();
   window.resize(QSize(500, 500));
#else
   QGuiApplication app(argc, argv);
   SkyplotWidget::declareQml();
   QQmlApplicationEngine engine;
   engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
#endif
   return app.exec();
}
