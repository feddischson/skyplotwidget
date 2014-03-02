 #include <QtGui>
 #include "Window.h"

 Window::Window()
 {




   QGridLayout *layout = new QGridLayout;

   QColor fontColor( 0, 0, 0 );

   skyplotWidget = new SkyplotWidget;

   skyplotWidget->addSatellite( 0,  0, 10, QString( "0" ), QColor(  50,  20, 255 ), QColor( 150, 50, 20 ), fontColor, false, true, true, false    );
   skyplotWidget->addSatellite( 1, 10, 10, QString( "1" ), QColor(   0, 255, 255 ), QColor( 150, 50, 20 ), fontColor, true, false, true, true     );
  
   skyplotWidget->addSatellite( 2,  0, 30, QString(  "12" ), QColor(  50,  20, 255 ), QColor( 150, 50, 20 ), fontColor, false, true, false, true  );
   skyplotWidget->addSatellite( 3, 10, 30, QString(  "13" ), QColor(   0, 255, 255 ), QColor( 150, 50, 20 ), fontColor, true, false, false, false );
   
   
   skyplotWidget->addSatellite( 4, 120, 20, QString( "1" ), QColor(   0, 255, 0 ), QColor(   0,  50, 255 ), fontColor, true, true, true, false );
   skyplotWidget->addSatellite( 5, 195, 20, QString( "3" ),    QColor( 255,   0, 0 ), QColor( 150, 150,   0 ), fontColor, true, true, true, false );
   skyplotWidget->addSatellite( 6, 290, 60, QString( "6" ),    QColor(   0,   0, 0 ), QColor( 255,  50,   0 ), fontColor, true, true, true, false );






   skyplotWidget->setGridColor( QColor( 0, 255, 0 ) );
   skyplotWidget->setGridWidth( 1.5 );
   skyplotWidget->setCrosses( 6 );
   skyplotWidget->setEllipses( 6 );
   skyplotWidget->setSatelliteScale( 0.02 );


   for( int i=50; i <= 70; i ++ ) 
   {
      skyplotWidget->addSatellite( i, 0, 0, QString(  "0" ), QColor(   0, 0, 0 ), QColor( 0, 0, 0 ), fontColor, true, false, false, false );
      skyplotWidget->setSatBlinking    ( i, false );
      skyplotWidget->setSatInnerColor  ( i, QColor( 255, 255, 255 ) );
      skyplotWidget->setSatOuterColor  ( i, QColor(   0, 255, 255 ) );
      skyplotWidget->setSatFontColor   ( i, QColor( 255,   0, 0   ) );
      skyplotWidget->setSatState1      ( i, true );
      skyplotWidget->setSatState2      ( i, true );
      skyplotWidget->setSatState3      ( i, true );
      skyplotWidget->setSatLabel       ( i, QString( "%1" ).arg(i)        );
      skyplotWidget->setSatAzimuth     ( i, (i*30)%360  );
      skyplotWidget->setSatElevation   ( i, (i*5)%90  );
   }

   layout->addWidget(skyplotWidget, 0, 0 );


   setLayout(layout);
 
   setWindowTitle(tr("Skyplot examples"));
 }

