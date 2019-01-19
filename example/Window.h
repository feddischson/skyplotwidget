#ifndef WINDOW_H
#define WINDOW_H

#include <QGridLayout>
#include <QWidget>

#include "SkyplotWidget.h"

class Window : public QWidget {
   Q_OBJECT

  public:
   Window();

  private:
   SkyplotWidget *skyplotWidget;
};

#endif
