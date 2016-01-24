 #include <QtGui>
 #include "Window.h"

 Window::Window()
 {




   QGridLayout *layout = new QGridLayout;

   QColor fontColor( 0, 0, 0 );

   skyplotWidget = new SkyplotWidget;


   skyplotWidget->insert( 0,  0, 10,  QString( "0" ), Qt::red, Qt::blue, fontColor, 
      SkyplotWidget::SatelliteState::Visible 
         );
   skyplotWidget->insert( 1, 10, 10,  QString( "1" ), Qt::red, Qt::blue, fontColor,
      SkyplotWidget::SatelliteState::HalfVisible
         );

   skyplotWidget->insert( 2,  40, 15,  QString( "2" ), Qt::red, Qt::yellow, fontColor, 
      SkyplotWidget::SatelliteState::Visible  |
      SkyplotWidget::SatelliteState::Marked 

         );
   skyplotWidget->insert( 3, 80, 15,  QString( "3" ), Qt::red, Qt::yellow, fontColor,
      SkyplotWidget::SatelliteState::HalfVisible |
      SkyplotWidget::SatelliteState::Marked 
         );

   skyplotWidget->insert( 4,  120, 15,  QString( "4" ), Qt::red, Qt::white, fontColor, 
      SkyplotWidget::SatelliteState::Visible  |
      SkyplotWidget::SatelliteState::Marked   |
      SkyplotWidget::SatelliteState::Flashing
         );
   skyplotWidget->insert( 5, 150, 15,  QString( "5" ), Qt::red, Qt::white, fontColor,
      SkyplotWidget::SatelliteState::HalfVisible |
      SkyplotWidget::SatelliteState::Marked      |
      SkyplotWidget::SatelliteState::Flashing
         );


   skyplotWidget->setGridColor( QColor( 0, 255, 0 ) );
   skyplotWidget->setGridWidth( 1.5 );
   skyplotWidget->setCrosses( 2 );
   skyplotWidget->setEllipses( 6 );
   skyplotWidget->setSatelliteScale( 0.02 );

   for( int i=50; i <= 70; i ++ ) 
   {
      skyplotWidget->insert( i, 0, 0, 
            QString(  "0"+QString::number(i) ), 
            Qt::magenta, 
            Qt::white, 
            fontColor, 
            SkyplotWidget::SatelliteState::Visible );
      skyplotWidget->setInnerColor  ( i, Qt::white );
      skyplotWidget->setOuterColor  ( i, Qt::blue );
      skyplotWidget->setFontColor   ( i, Qt::red );
      skyplotWidget->setLabel       ( i, QString( "%1" ).arg(i)        );
      skyplotWidget->setState( i,
            SkyplotWidget::SatelliteState::Visible |
            SkyplotWidget::SatelliteState::Marked );

      skyplotWidget->setAzimuth     ( i, (i*30)%360  );
      skyplotWidget->setElevation   ( i, (i*5)%90  );
   }
   layout->addWidget(skyplotWidget, 0, 0 );


   setLayout(layout);

   setWindowTitle(tr("Skyplot examples"));
 }

