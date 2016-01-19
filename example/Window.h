 #ifndef WINDOW_H
 #define WINDOW_H
 #include "SkyplotWidget.h"
 #include <QWidget>
 #include <QGridLayout>


 class Window : public QWidget
 {
     Q_OBJECT

 public:
     Window();

 private:
     SkyplotWidget *skyplotWidget;
 };

 #endif
