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

     Q_CLASSINFO( "Version", "0.0.1" )
     Q_PROPERTY( float  marginScale       READ marginScale     WRITE setMarginScale    )
     Q_PROPERTY( float  satelliteScale    READ satelliteScale  WRITE setSatelliteScale )
     Q_PROPERTY( float  fontScale         READ fontScale       WRITE setFontScale      )
     Q_PROPERTY( QColor gridColor         READ gridColor       WRITE setGridColor      )
     Q_PROPERTY( int    gridWidth         READ gridWidth       WRITE setGridWidth      )
     Q_PROPERTY( int    ellipses          READ ellipses        WRITE setEllipses       )
     Q_PROPERTY( int    crosses           READ crosses         WRITE setCrosses        )
     Q_PROPERTY( int    textMargin        READ textMargin      WRITE setTextMargin     )
     Q_PROPERTY( int    blinkIntervall    READ blinkIntervall  WRITE setBlinkIntervall )
     Q_PROPERTY( bool   withGridLabels    READ withGridLabels  WRITE setWithGridLabels )
     Q_PROPERTY( bool   antialiased       READ antialiased     WRITE setAntialiased    )


 public:
#ifndef SKYPLOT_QML_SUPPORT
      SkyplotWidget(QWidget *parent = 0);
#else
      SkyplotWidget(QQuickPaintedItem *parent = 0);
      static void declareQml() {
          qmlRegisterType<SkyplotWidget>("SkyplotWidget", 0, 1,
                                           "SkyplotWidget");
      }
#endif


      void     setMarginScale    ( float          scale ){ p_marginScale    = scale;       this->update(); }
      void     setSatelliteScale ( float          scale ){ p_satScale       = scale;       this->update(); }
      void     setFontScale      ( float          scale ){ p_fontScale      = scale;       this->update(); }
      void     setGridColor      ( const QColor & color ){ p_gridColor      = color;       this->update(); }
      void     setGridWidth      ( int            width ){ p_gridWidth      = width;       this->update(); }
      void     setEllipses       ( int               no ){ p_ellipses       = no;          this->update(); }
      void     setCrosses        ( int               no ){ p_crosses        = no;          this->update(); }
      void     setTextMargin     ( int           margin ){ p_textMargin     = margin;      this->update(); }
      void     setBlinkIntervall ( int        intervall ){ p_blinkIntervall = intervall;   this->update(); }
      void     setWithGridLabels ( int       withLabels ){ p_withGridLabels = withLabels;  this->update(); }
      void     setAntialiased    ( int      antialiased ){ p_antialiased    = antialiased; this->update(); }


      float    marginScale       ( void ){ return p_marginScale;    }
      float    satelliteScale    ( void ){ return p_satScale;       }
      float    fontScale         ( void ){ return p_fontScale;      }
      QColor   gridColor         ( void ){ return p_gridColor;      }
      int      gridWidth         ( void ){ return p_gridWidth;      }
      int      ellipses          ( void ){ return p_ellipses;       }
      int      crosses           ( void ){ return p_crosses;        }
      int      textMargin        ( void ){ return p_textMargin;     }
      int      blinkIntervall    ( void ){ return p_blinkIntervall; }
      int      withGridLabels    ( void ){ return p_withGridLabels; }
      int      antialiased       ( void ){ return p_antialiased;    }
      

      bool     satIsBlinking     ( int id );
      QColor   satInnerColor     ( int id );
      QColor   satOuterColor     ( int id );
      QColor   satFontColor      ( int id );
      bool     satState1         ( int id );
      bool     satState2         ( int id );
      bool     satState3         ( int id );
      QString  satLabel          ( int id );
      float    satAzimuth        ( int id );
      float    satElevation      ( int id );

      void     setSatBlinking    ( int id, bool  state            );
      void     setSatInnerColor  ( int id, const QColor & c       );
      void     setSatOuterColor  ( int id, const QColor & c       );
      void     setSatFontColor   ( int id, const QColor & c       );
      void     setSatState1      ( int id, bool  state            );
      void     setSatState2      ( int id, bool  state            );
      void     setSatState3      ( int id, bool  state            );
      void     setSatLabel       ( int id, const QString & label  );
      void     setSatAzimuth     ( int id, float az               );
      void     setSatElevation   ( int id, float el               );


 public slots:

      void addSatellite(  int id,
                          float     az,
                          float     el,
                          const QString & label,
                          const QColor  & outerColor,
                          const QColor  & innerColor,
                          const QColor  & fontColor,
                          bool  state1   = true,
                          bool  state2   = true,
                          bool  state3   = true,
                          bool  blinking = true);

      void removeSatellite( int id );

      bool isSatExists( int id );


 protected:
#ifndef SKYPLOT_QML_SUPPORT
      void paintEvent(QPaintEvent *event);
#else
      void paint(QPainter *painter);
#endif

 private:


      int       noBlinkingSats;
      bool      blink;
      QTimer    blinkTimer;
      

      float     p_marginScale;
      float     p_satScale;
      float     p_fontScale;
      QColor    p_gridColor;
      int       p_gridWidth;
      int       p_ellipses;
      int       p_crosses;
      int       p_textMargin;
      int       p_blinkIntervall;
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
            bool     state1;
            bool     state2;
            bool     state3;
            bool     blinking;
      }Satellite;


      QMap< int, Satellite > satellites;
      typedef QMap< int, SkyplotWidget::Satellite >::const_iterator  I_satellite;


 private slots:
   void change_blink( void );


 };

 #endif
