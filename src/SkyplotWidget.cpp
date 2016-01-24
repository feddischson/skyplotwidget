// SkyplotWidget
// Copyright (C) 2011-2016 Christian Haettich feddischson[at]gmx.com
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
#include <stdlib.h>
#include <QDebug>
#include <QtMath>

#include "SkyplotWidget.h"

#ifndef SKYPLOT_QML_SUPPORT
SkyplotWidget::SkyplotWidget(QWidget *parent)
   : QWidget(parent)
#else
SkyplotWidget::SkyplotWidget(QQuickPaintedItem *parent)
   : QQuickPaintedItem(parent)
#endif
   , flash( false )
   , p_marginScale( 0.78 )
   , p_satScale( 0.03 )
   , p_fontScale( 0.02 )
   , p_gridColor( QColor( 150, 150, 150, 255 ) )
   , p_gridTextColor( QColor( 0, 0, 0, 255 ) )
   , p_gridWidth( 3 )
   , p_ellipses( 3 )
   , p_crosses( 3 )
   , p_textMargin( 10 )
   , p_flashIntervall( 500 )
   , p_withGridLabels( true )
   , p_antialiased( true )
{

#ifndef SKYPLOT_QML_SUPPORT
   setBackgroundRole(QPalette::Base);
   setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
#endif
   flashTimer.setInterval( p_flashIntervall );
   connect( &flashTimer, SIGNAL( timeout() ), this, SLOT( change_flash() ) );
   flashTimer.start( p_flashIntervall );
}

void SkyplotWidget::change_flash( void )
{
   flash = !flash;
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

   float          availableWidth    = widgetSize.width ();
   float          availableHeight   = widgetSize.height();

   if( availableHeight > availableWidth )
   {
      size = widgetSize.width() * p_marginScale;
      topMargin   = ( widgetSize.width() - widgetSize.width() * p_marginScale + 
            widgetSize.height() - widgetSize.width() ) / 2.0;
      leftMargin  = ( widgetSize.width() - widgetSize.width() * p_marginScale ) / 2.0;
   }
   else
   {
      size = widgetSize.height() * p_marginScale;
      leftMargin = ( widgetSize.height() - widgetSize.height() * p_marginScale + 
            widgetSize.width() - widgetSize.height()) / 2.0;
      topMargin  = ( widgetSize.height() - widgetSize.height() * p_marginScale ) / 2.0;
   }
   satelliteSize = size * p_satScale;

   painter->setRenderHint(QPainter::Antialiasing, p_antialiased);
   painter->translate( leftMargin, topMargin );
   fontSize = size * p_fontScale;


   painter->setFont( 
         QFont( "Arial", 
         static_cast< int >( fontSize ) ) );

   // paint the circles
   for( int i=0; i < p_ellipses; i++ )
   {
      float radius = size / 2.0 - i * ( size / ( 2.0  * p_ellipses )  );
      painter->setPen( QPen( p_gridColor, p_gridWidth ) );
      painter->drawEllipse(  
            QPoint( size/2.0, size/2.0 ), 
            static_cast< int >( radius ), 
            static_cast< int >( radius ) );
      if( p_withGridLabels )
      {
         painter->setPen( QPen( p_gridTextColor, p_gridWidth ) );
         painter->drawText( QPoint( size/2.0 + p_textMargin, size/2.0 - ( radius + p_textMargin ) ),
                            QString("%1").arg( i * (90 / p_ellipses ) ) );
      }
   }

   // paint the crosses
   for( int i=0; i < p_crosses; i ++ )
   {
      QLineF line1;
      QLineF line2;
      float angle = static_cast<float>(i) * 90.0 / static_cast<float>(p_crosses);
      line1.setP1( QPoint( size/2.0, size/2.0 ) );
      line1.setLength( size/2.0 );

      QRectF textRect( 0, 0, 4.0 * fontSize, fontSize + 2.0 );

      for( int c = 0; c < 4; c++ )
      {
         line1.setAngle( angle + c*90.0 + 90.0 );
         painter->setPen( QPen( p_gridColor, p_gridWidth ) );
         painter->drawLine( line1 );
         if( p_withGridLabels  )
         {
            painter->setPen( QPen( p_gridTextColor, p_gridWidth ) );
            line2 = QLineF( line1 );
            line2.setLength( size/2.0 + 2.0 * fontSize );
            textRect.moveCenter( line2.p2() );
            if( i > 0 )
               painter->drawText( textRect, Qt::AlignCenter, QString( "%1").arg( 360.0 - (c*90.0 ) - angle ) );
            else
               painter->drawText( textRect, Qt::AlignCenter, QString( "N") );
         }
      }
   }

   QBrush innerBrush = QBrush( Qt::SolidPattern );
   QBrush outerBrush = QBrush( );

   foreach( auto s, satellites )
   {

      // skip invisible satellites
      if(     s.state & SatelliteState::Invisible       ||  // the invisible flag is set

         ( !( s.state & SatelliteState::Visible ) &         // neither visible nor half-visible
           !( s.state & SatelliteState::HalfVisible ) ) || 

         (  s.state & SatelliteState::Flashing && flash )    // flashing flag is set and flash is active
         ) 
         continue;


      float el_s = ( 90 - s.el ) * size / ( 2 * 90.0 );
      QRectF labelRect( 0, 0, s.label.length() * satelliteSize, satelliteSize+2 );

      QPoint satPos( size/2   + sin( s.az * 2 * MY_PI / 360.0 ) * el_s, 
                     size/2   - cos( s.az * 2 * MY_PI / 360.0 ) * el_s ); 

      // define the color's alpha value (0.3 or 1.0)
      QColor innerColor = s.innerColor;
      QColor outerColor = s.outerColor;
      QColor fontColor  = s.fontColor;
      if( s.state & SatelliteState::Visible )
      {
         innerColor.setAlphaF( 1.0 );
         outerColor.setAlphaF( 1.0 );
         fontColor.setAlphaF( 1.0 );
      }
      else
      {
         innerColor.setAlphaF( 0.3 );
         outerColor.setAlphaF( 0.3 );
         fontColor.setAlphaF( 0.3 );
      }

      // paint the inner circle
      innerBrush.setColor( innerColor );
      painter->setBrush( innerBrush );
      if( s.state & SatelliteState::Marked )
         painter->setPen( QPen( outerColor, satelliteSize/4 ) );
      else
         painter->setPen( QPen( p_gridColor, 0 ) );
      painter->drawEllipse( 
            satPos, 
            static_cast< int >( satelliteSize ), 
            static_cast< int >( satelliteSize ) );


      // write the text
      painter->setPen( QPen( fontColor, 2 ) );
      painter->setFont( 
            QFont( "Arial", 
            static_cast< int >( satelliteSize ), 
            QFont::Bold ) );
      labelRect.moveCenter( satPos );
      painter->drawText( labelRect, Qt::AlignCenter, s.label );

   }

#ifndef SKYPLOT_QML_SUPPORT
   delete painter;
#endif
}

void 
SkyplotWidget::insert(  int id, 
                        float az,
                        float el,
                        const QString & label, 
                        const QColor & outerColor, 
                        const QColor & innerColor,
                        const QColor & fontColor,
                        SatelliteState  state )
{
   Satellite   sat;
   sat.label      = label;
   sat.az         = az;
   sat.el         = el;
   sat.state      = state;
   sat.innerColor = innerColor; 
   sat.outerColor = outerColor;
   sat.fontColor  = fontColor;

   this->update();

   satellites.insert( id, sat );
}


void 
SkyplotWidget::remove( int id )
{
   satellites.remove( id );
}


bool SkyplotWidget::contains( int id ) const
{
    return satellites.contains( id );
}




QColor 
SkyplotWidget::innerColor( int id ) const
{
   return satellites[ id ].innerColor;
}

QColor 
SkyplotWidget::outerColor( int id ) const
{
   return satellites[ id ].outerColor;
}

QColor  
SkyplotWidget::fontColor( int id ) const
{
   return satellites[ id ].fontColor;
}

void   
SkyplotWidget::setInnerColor( int id, const QColor & c )
{
   satellites[ id ].innerColor = c;
   this->update();
}

void   
SkyplotWidget::setOuterColor( int id, const QColor & c )
{
   satellites[ id ].outerColor = c;
}

void    
SkyplotWidget::setFontColor( int id, const QColor & c )
{
   satellites[ id ].fontColor = c;
}


SkyplotWidget::SatelliteState  
SkyplotWidget::state( int id ) const
{
   return satellites[ id ].state;
}

void  
SkyplotWidget::setState( int id, SatelliteState state )
{
   satellites[ id ].state = state;
   this->update();
}


QString 
SkyplotWidget::label( int id ) const
{
   return satellites[ id ].label;
}

void  
SkyplotWidget::setLabel( int id, const QString & label )
{
   satellites[ id ].label = label;
   this->update();
}


float 
SkyplotWidget::azimuth( int id ) const
{
   return satellites[ id ].az;
}

float 
SkyplotWidget::elevation( int id ) const
{
   return satellites[ id ].el;
}

void  
SkyplotWidget::setAzimuth( int id, float az )
{
   satellites[ id ].az = az;
   this->update();
}

void  
SkyplotWidget::setElevation( int id, float el )
{
   satellites[ id ].el = el;
   this->update();
}

QList< int > SkyplotWidget::ids( void ) const
{
   return satellites.keys();
}


SkyplotWidget::SatelliteState operator| ( 
      SkyplotWidget::SatelliteState lhs, 
      SkyplotWidget::SatelliteState rhs )
{
   return static_cast< SkyplotWidget::SatelliteState >(
         static_cast< quint8 >( lhs ) | static_cast< quint8 >( rhs ) 
         );
}


// vim: filetype=cpp et ts=3 sw=3 sts=3
//
