// SkyplotWidget
// Copyright (C) 2011-2017 Christian Haettich feddischson[at]gmail.com
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



#ifndef _SKYPLOT_WIDGET_H
#define _SKYPLOT_WIDGET_H
#include <QMap>
#include <QTimer>

#ifndef SKYPLOT_QML_SUPPORT
#include <QWidget>
#else
#include <QtQml>
#include <QQuickPaintedItem>
#endif

#define MY_PI  3.141593

#include "SkyplotWidget_global.h"

#ifndef SKYPLOT_QML_SUPPORT
class SKYPLOTWIDGET_EXPORT SkyplotWidget : public QWidget
#else
class SKYPLOTWIDGET_EXPORT SkyplotWidget : public QQuickPaintedItem
#endif
{
   Q_OBJECT

   Q_CLASSINFO( "Version", _SKP_VERSION )
   Q_PROPERTY( float  marginScale       READ marginScale     WRITE setMarginScale    )
   Q_PROPERTY( float  satelliteScale    READ satelliteScale  WRITE setSatelliteScale )
   Q_PROPERTY( float  fontScale         READ fontScale       WRITE setFontScale      )
   Q_PROPERTY( QColor gridColor         READ gridColor       WRITE setGridColor      )
   Q_PROPERTY( QColor gridTextColor     READ gridTextColor   WRITE setGridTextColor  )
   Q_PROPERTY( int    gridWidth         READ gridWidth       WRITE setGridWidth      )
   Q_PROPERTY( int    ellipses          READ ellipses        WRITE setEllipses       )
   Q_PROPERTY( int    crosses           READ crosses         WRITE setCrosses        )
   Q_PROPERTY( int    textMargin        READ textMargin      WRITE setTextMargin     )
   Q_PROPERTY( int    flashIntervall    READ flashIntervall  WRITE setFlashIntervall )
   Q_PROPERTY( bool   withGridLabels    READ withGridLabels  WRITE setWithGridLabels )
   Q_PROPERTY( bool   antialiased       READ antialiased     WRITE setAntialiased    )


public:
   enum SatelliteState : quint8 { 
      Invisible   = 0x00,
      Visible     = 0x01,
      HalfVisible = 0x02,
      Marked      = 0x04,
      Flashing    = 0x08 };
   Q_ENUMS( SatelliteState )

#ifndef SKYPLOT_QML_SUPPORT
   explicit SkyplotWidget( QWidget *parent = nullptr );
#else
   SkyplotWidget( QQuickPaintedItem *parent = nullptr );
#endif

#ifdef SKYPLOT_QML_SUPPORT
   static void declareQml( ) {
      qmlRegisterType<SkyplotWidget>( "SkyplotWidget",  _SKP_VERSION_MAJ, _SKP_VERSION_MIN, "SkyplotWidget"  );
      qmlRegisterType<SkyplotWidget>( "SatelliteState", _SKP_VERSION_MAJ, _SKP_VERSION_MIN, "SatelliteState" );
   }
#endif

   SkyplotWidget(const SkyplotWidget & spw )             = delete;
   SkyplotWidget& operator= (const SkyplotWidget & spw)  = delete;
   SkyplotWidget( SkyplotWidget && rhs )                 = delete;
   SkyplotWidget& operator=( SkyplotWidget && rhs )      = delete;
   ~SkyplotWidget()                                      = default;


   void  setMarginScale    ( float          scale ){ p_marginScale    = scale;       this->update(); }
   void  setSatelliteScale ( float          scale ){ p_satScale       = scale;       this->update(); }
   void  setFontScale      ( float          scale ){ p_fontScale      = scale;       this->update(); }
   void  setGridColor      ( const QColor & color ){ p_gridColor      = color;       this->update(); }
   void  setGridTextColor  ( const QColor & color ){ p_gridTextColor  = color;       this->update(); }
   void  setGridWidth      ( int            width ){ p_gridWidth      = width;       this->update(); }
   void  setEllipses       ( int               no ){ p_ellipses       = no;          this->update(); }
   void  setCrosses        ( int               no ){ p_crosses        = no;          this->update(); }
   void  setTextMargin     ( int           margin ){ p_textMargin     = margin;      this->update(); }
   void  setFlashIntervall ( int        intervall ){ p_flashIntervall = intervall;   this->update(); }
   void  setWithGridLabels ( int       withLabels ){ p_withGridLabels = withLabels;  this->update(); }
   void  setAntialiased    ( int      antialiased ){ p_antialiased    = antialiased; this->update(); }


   float          marginScale       ( void ) const { return p_marginScale;    }
   float          satelliteScale    ( void ) const { return p_satScale;       }
   float          fontScale         ( void ) const { return p_fontScale;      }
   const QColor & gridColor         ( void ) const { return p_gridColor;      }
   const QColor & gridTextColor     ( void ) const { return p_gridTextColor;  }
   int            gridWidth         ( void ) const { return p_gridWidth;      }
   int            ellipses          ( void ) const { return p_ellipses;       }
   int            crosses           ( void ) const { return p_crosses;        }
   int            textMargin        ( void ) const { return p_textMargin;     }
   int            flashIntervall    ( void ) const { return p_flashIntervall; }
   int            withGridLabels    ( void ) const { return p_withGridLabels; }
   int            antialiased       ( void ) const { return p_antialiased;    }

   QColor         innerColor     ( int id ) const;
   QColor         outerColor     ( int id ) const;
   QColor         fontColor      ( int id ) const;
   SatelliteState state          ( int id ) const;
   QString        label          ( int id ) const;
   float          azimuth        ( int id ) const;
   float          elevation      ( int id ) const;

   QList< int >  ids( void ) const;

public slots:

   void insert( int   id,
                float az = 0,
                float el = 90.0,
                const QString & label      = QString(""),
                const QColor  & outerColor = Qt::red,
                const QColor  & innerColor = Qt::lightGray,
                const QColor  & fontColor  = Qt::black,
                SatelliteState  state      = SatelliteState::Visible );

   void remove( int id );

   bool contains( int id ) const;

   void setInnerColor  ( int id, const QColor & c       );
   void setOuterColor  ( int id, const QColor & c       );
   void setFontColor   ( int id, const QColor & c       );
   void setState       ( int id, SatelliteState state   );
   void setLabel       ( int id, const QString & label  );
   void setAzimuth     ( int id, float az               );
   void setElevation   ( int id, float el               );


 protected:
#ifndef SKYPLOT_QML_SUPPORT
   void paintEvent(QPaintEvent *event);
#else
   void paint(QPainter *painter);
#endif

private:


   bool      flash;
   QTimer    flashTimer;


   float     p_marginScale;
   float     p_satScale;
   float     p_fontScale;
   QColor    p_gridColor;
   QColor    p_gridTextColor;
   int       p_gridWidth;
   int       p_ellipses;
   int       p_crosses;
   int       p_textMargin;
   int       p_flashIntervall;
   bool      p_withGridLabels;
   bool      p_antialiased;

   typedef struct _Satellite
   {
      QString  label;
      QColor   innerColor;
      QColor   outerColor;
      QColor   fontColor;
      float    az;
      float    el;
      SatelliteState  state;
   } Satellite;


   QHash< int, Satellite > satellites;


private slots:
   void change_flash( void );
};

SkyplotWidget::SatelliteState operator| ( 
      SkyplotWidget::SatelliteState lhs, 
      SkyplotWidget::SatelliteState rhs );


#endif

// vim: filetype=cpp et ts=3 sw=3 sts=3

