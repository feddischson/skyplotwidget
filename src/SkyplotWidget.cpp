// SkyplotWidget
// Copyright (C) 2011-2014 Christian Haettich feddischson[at]gmx.com
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA


#include <QGuiApplication>
#include <QtGui>
#include "SkyplotWidget.h"
#include <stdlib.h>
#include <QDebug>
#include <QtMath>



#ifndef SKYPLOT_QML_SUPPORT
SkyplotWidget::SkyplotWidget(QWidget *parent)
    : QWidget(parent)
#else
SkyplotWidget::SkyplotWidget(QQuickPaintedItem *parent)
    : QQuickPaintedItem(parent)
#endif
    , p_antialiased( true )
    , noBlinkingSats( 0 )
    , p_marginScale( 0.78 )
    , p_gridColor( QColor( 150, 150, 150, 255 ) )
    , p_gridWidth(3)
    , p_textMargin(10)
    , p_withGridLabels(true)
    , p_ellipses(3)
    , p_crosses(3)
    , p_blinkIntervall(500)
    , p_satScale(0.03)
    , p_fontScale(0.02)
    , blink(false)
{

#ifndef SKYPLOT_QML_SUPPORT
   setBackgroundRole(QPalette::Base);
   setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
#endif
   blinkTimer.setInterval( p_blinkIntervall );
   connect( &blinkTimer, SIGNAL( timeout() ), this, SLOT( change_blink() ) );
}



void SkyplotWidget::change_blink( void )
{
   blink = !blink;
   this->update();
}




#ifndef SKYPLOT_QML_SUPPORT
void SkyplotWidget::paintEvent(QPaintEvent *)
#else
void SkyplotWidget::paint(QPainter *painter)
#endif
{
#ifndef SKYPLOT_QML_SUPPORT
   QSize          widgetSize( this->size() );
   QPalette       p = palette();
   QPainter      *painter = new QPainter(this);
#else
   QSize          widgetSize( this->width(), this->height() );
   QPalette       p = QGuiApplication::palette();
#endif

   float          topMargin ;
   float          leftMargin;
   float          size;
   float          satelliteSize;
   float          fontSize;
   float          bottomMargin;

   float          availableWidth    = widgetSize.width ();
   float          availableHeight   = widgetSize.height();

   if( availableHeight > availableWidth )
   {
      size = widgetSize.width() * p_marginScale;
      topMargin   = ( widgetSize.width() - widgetSize.width() * p_marginScale + widgetSize.height() - widgetSize.width() ) / 2;
      leftMargin  = ( widgetSize.width() - widgetSize.width() * p_marginScale ) / 2;
   }
   else
   {
      size = widgetSize.height() * p_marginScale;
      leftMargin = ( widgetSize.height() - widgetSize.height() * p_marginScale + widgetSize.width() - widgetSize.height()) / 2;
      topMargin  = ( widgetSize.height() - widgetSize.height() * p_marginScale ) / 2;
   }
   satelliteSize = size * p_satScale;

   painter->setRenderHint(QPainter::Antialiasing, p_antialiased);
   painter->translate( leftMargin, topMargin );
   fontSize = size * p_fontScale;


   painter->setFont( QFont( "Arial", (int)fontSize ) );
   for( int i=0; i < p_ellipses; i++ )
   {
      float radius = size / 2 - i * ( size / (2  * p_ellipses )  );
      painter->setPen( QPen( p_gridColor, p_gridWidth ) );
      painter->drawEllipse(  QPoint( size/2, size/2 ), (int)radius, (int)radius );
      if( p_withGridLabels )
      {
         painter->setPen( QPen( p.text( ).color( ), p_gridWidth ) );
         painter->drawText( QPoint( size/2 + p_textMargin, size/2 - ( radius + p_textMargin ) ),
                           QString("%1").arg( i * (90 / p_ellipses ) ) );
      }
   }


   for( int i=0; i < p_crosses; i ++ )
   {
      QLineF line1;
      QLineF line2;
      float angle = i * 90 / p_crosses;
      line1.setP1( QPoint( size/2, size/2 ) );
      line1.setLength( size/2 );


      QRectF textRect( 0, 0, 4 * fontSize, fontSize + 2 );


      line1.setAngle( angle + 90 );
      painter->setPen( QPen( p_gridColor, p_gridWidth ) );
      painter->drawLine( line1 );
      if( p_withGridLabels  )
      {
         painter->setPen( QPen( p.text( ).color( ), p_gridWidth ) );
         line2 = QLineF( line1 );
         line2.setLength( size/2 + 2 * fontSize );
         textRect.moveCenter( line2.p2() );
         if( i > 0 )
            painter->drawText( textRect, Qt::AlignCenter, QString( "%1").arg( 360 - angle ) );
         else
            painter->drawText( textRect, Qt::AlignCenter, QString( "N") );
      }

      line1 = line1.normalVector();
      painter->setPen( QPen( p_gridColor, p_gridWidth ) );
      painter->drawLine( line1 );
      if( p_withGridLabels )
      {
         painter->setPen( QPen( p.text( ).color( ), p_gridWidth ) );
         line2 = QLineF( line1 );
         line2.setLength( size/2 + 2 * fontSize );
         textRect.moveCenter( line2.p2() );
         if( i > 0 )
            painter->drawText( textRect, Qt::AlignCenter, QString( "%1").arg( 360 - 90 - angle ) );
         else
            painter->drawText( textRect, Qt::AlignCenter, QString( "W") );

      }

      line1 = line1.normalVector();
      painter->setPen( QPen( p_gridColor, p_gridWidth ) );
      painter->drawLine( line1 );
      if( p_withGridLabels )
      {
         painter->setPen( QPen( p.text( ).color( ), p_gridWidth ) );
         line2 = QLineF( line1 );
         line2.setLength( size/2 + 2 * fontSize );
         textRect.moveCenter( line2.p2() );
         if( i > 0 )
            painter->drawText( textRect, Qt::AlignCenter, QString( "%1").arg( 360 - 180 - angle ) );
         else
            painter->drawText( textRect, Qt::AlignCenter, QString( "S") );
      }

      line1 = line1.normalVector();
      painter->setPen( QPen( p_gridColor, p_gridWidth ) );
      painter->drawLine( line1 );
      if( p_withGridLabels )
      {
         painter->setPen( QPen( p.text( ).color( ), p_gridWidth ) );
         line2 = QLineF( line1 );
         line2.setLength( size/2 + 2 * fontSize );
         textRect.moveCenter( line2.p2() );
         if( i > 0 )
            painter->drawText( textRect, Qt::AlignCenter, QString( "%1").arg( 360 - 270 - angle ) );
         else
            painter->drawText( textRect, Qt::AlignCenter, QString( "E") );
      }

   }


   QBrush innerBrush = QBrush( Qt::SolidPattern );
   QBrush outerBrush = QBrush( );




   for( I_satellite i= satellites.begin(); i != satellites.end(); i++ )
   {
      float el_s     = ( 90 - i->el ) * size / ( 2 * 90.0 );
      QRectF labelRect( 0, 0, i->label.length() * satelliteSize, satelliteSize+2 );

      QPoint satPos( size/2   + sin( i->az * 2 * MY_PI / 360 ) * el_s, 
                     size/2   - cos( i->az * 2 * MY_PI / 360 ) * el_s ); 


      if(      ( i->state1 && i->blinking && blink )
            || ( i->state1 && !i->blinking         ) )
      {
         innerBrush.setColor( i->innerColor );
         painter->setBrush( innerBrush );
         painter->setPen( QPen( p_gridColor, 0 ) );
         painter->drawEllipse( satPos, (int)satelliteSize, (int)satelliteSize );
      }


      if(      ( i->state2 && i->blinking && blink )
            || ( i->state2 && !i->blinking         ) )
      {
         painter->setBrush( outerBrush );
         painter->setPen( QPen( i->outerColor, satelliteSize/4 ) );
         painter->drawEllipse( satPos, (int)satelliteSize, (int)satelliteSize );
      
      }

      if( ( i->blinking && blink ) || !i->blinking )
      {
         painter->setPen( QPen( i->fontColor, 2 ) );
         painter->setFont( QFont( "Arial", (int)satelliteSize, QFont::Bold ) );
         labelRect.moveCenter( satPos );
         painter->drawText( labelRect, Qt::AlignCenter, i->label );
      }
   }

#ifndef SKYPLOT_QML_SUPPORT
   delete painter;
#endif
}













void 
SkyplotWidget::addSatellite(  int id, 
                              float az,
                              float el,
                              const QString & label, 
                              const QColor & outerColor, 
                              const QColor & innerColor,
                              const QColor & fontColor,
                              bool  state1,
                              bool  state2,
                              bool  state3,
                              bool  blinking)
{
   Satellite   sat;
   sat.label      = label;
   sat.az         = az;
   sat.el         = el;
   sat.state1     = state1;
   sat.state2     = state2;
   sat.state3     = state3;
   sat.blinking   = blinking;
   sat.innerColor = innerColor; 
   sat.outerColor = outerColor;
   sat.fontColor  = fontColor;

   if( state3 )
   {
      sat.innerColor.setAlphaF( 1.0 );
      sat.outerColor.setAlphaF( 1.0 );
      sat.fontColor.setAlphaF( 1.0 );
   }
   else
   {
      sat.innerColor.setAlphaF( 0.3 );
      sat.outerColor.setAlphaF( 0.3 );
      sat.fontColor.setAlphaF( 0.3 );
   }

   if( blinking )
   {
      if( noBlinkingSats == 0)
      {
         blinkTimer.start( p_blinkIntervall );
      }
      noBlinkingSats++;
   }
   else
      this->update();

   satellites.insert( id, sat );
}

void
SkyplotWidget::setSatBlinking( int id, bool state )
{
   if( satellites.contains( id ) )
   {

      if( satellites[ id ].blinking && !state )
      {
         if( (--noBlinkingSats) == 0 )
         {
            blinkTimer.stop();
         }
         satellites[ id ].blinking = state;
      }
      else if( !satellites[ id ].blinking && state )
      {
         if( noBlinkingSats == 0)
         {
            blinkTimer.start( p_blinkIntervall );
         }
         noBlinkingSats++;
         satellites[ id ].blinking = state;
      }
   }
}


bool 
SkyplotWidget::satIsBlinking( int id )
{
   if( satellites.contains( id ) )
   {
      return satellites[ id ].blinking;
   }
   else
      return false;
}


void 
SkyplotWidget::removeSatellite( int id )
{
   if( satellites.contains( id ) )
   {
      if( satellites[ id ].blinking )
      {
         if( (--noBlinkingSats) == 0 )
         {
            blinkTimer.stop();
         }
      }
      satellites.remove( id );
   }
}


bool SkyplotWidget::isSatExists(int id)
{
    return satellites.contains( id );
}




QColor 
SkyplotWidget::satInnerColor( int id )
{
   if( satellites.contains( id ) )
      return satellites[ id ].innerColor;
   else
      return QColor( 0, 0, 0 );
}

QColor 
SkyplotWidget::satOuterColor( int id )
{
   if( satellites.contains( id ) )
      return satellites[ id ].outerColor;
   else
      return QColor( 0, 0, 0 );
}

QColor  
SkyplotWidget::satFontColor( int id )
{
   if( satellites.contains( id ) )
      return satellites[ id ].fontColor;
   else
      return QColor( 0, 0, 0 );

}

void   
SkyplotWidget::setSatInnerColor( int id, const QColor & c )
{
   if( satellites.contains( id ) )
      satellites[ id ].innerColor = c;
   this->update();
}

void   
SkyplotWidget::setSatOuterColor( int id, const QColor & c )
{
   if( satellites.contains( id ) )
      satellites[ id ].outerColor = c;
   this->update();
}

void    
SkyplotWidget::setSatFontColor( int id, const QColor & c )
{
   if( satellites.contains( id ) )
      satellites[ id ].fontColor = c;
   this->update();
}


bool  
SkyplotWidget::satState1( int id )
{
   if( satellites.contains( id ) )
      return satellites[ id ].state1;
   else
      return false;
}

bool  
SkyplotWidget::satState2( int id )
{
   if( satellites.contains( id ) )
      return satellites[ id ].state2;
   else
      return false;
}

bool  
SkyplotWidget::satState3( int id )
{
   if( satellites.contains( id ) )
      return satellites[ id ].state3;
   else
      return false;
}

void  
SkyplotWidget::setSatState1( int id, bool state)
{
   if( satellites.contains( id ) )
      satellites[ id ].state1 = state;
   this->update();
}

void  
SkyplotWidget::setSatState2( int id, bool state)
{
   if( satellites.contains( id ) )
      satellites[ id ].state2 = state;
   this->update();
}

void  
SkyplotWidget::setSatState3( int id, bool state)
{
   if( satellites.contains( id ) )
      satellites[ id ].state3 = state;
   this->update();
}

QString 
SkyplotWidget::satLabel( int id )
{
   if( satellites.contains( id ) )
      return satellites[ id ].label;
   else
      return QString( "" );
}

void  
SkyplotWidget::setSatLabel( int id, const QString & label )
{
   if( satellites.contains( id ) )
      satellites[ id ].label = label;
   this->update();
}


float 
SkyplotWidget::satAzimuth( int id )
{
   if( satellites.contains( id ) )
      return satellites[ id ].az;
   else
      return 0.0;

}

float 
SkyplotWidget::satElevation( int id )
{
   if( satellites.contains( id ) )
      return satellites[ id ].el;
   else
      return 0.0;
}

void  
SkyplotWidget::setSatAzimuth( int id, float az )
{
   if( satellites.contains( id ) )
      satellites[ id ].az = az;
   this->update();
}

void  
SkyplotWidget::setSatElevation( int id, float el )
{
   if( satellites.contains( id ) )
      satellites[ id ].el = el;
   this->update();
}


