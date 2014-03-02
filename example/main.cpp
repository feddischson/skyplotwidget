 #include <QApplication>

 #include "Window.h"

 int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);
     Window window;
   
    QPalette p( window.palette() );
    p.setColor( QPalette::Background, Qt::black );
    window.setPalette( p );


     window.show();
     window.resize( QSize( 500, 500 ) );
     return app.exec();
 }
