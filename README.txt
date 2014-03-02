  SkyplotWidget
  Copyright (C) 2011 Christian Haettich feddischson[at]gmx.com
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
  -----------------------------------------------------------------------------------



  Description:

  Each satellite can be painted with a circle, a ring around the circle and a
  label. The satellites are addressed with an id.
  Depending on the state (state1, state2, state3 and blinking), the circle,
  the ring is painted or not, is painted with alpha = 0.3 or/and blinks.
  


     //
     // use this function to add a satellite
     //
     void addSatellite(          int     id,            // satellite id
                               float     az,            // azimuth
                               float     el,            // elevation
                         const QString & label,         // label
                         const QColor  & outerColor,    // color of outerring
                         const QColor  & innerColor,    // color of inner circle
                         const QColor  & fontColor,     // font color
                         bool  state1   = true,         // inner circle is painted
                         bool  state2   = true,         // outer ring is painted 
                         bool  state3   = true,         // ring and circle is painted with alpha  = 0.3
                         bool  blinking = true          // satellite blinks
                         );

     // use this function to remove a satellite
     void removeSatellite( int id );



     //
     // use this functions to modify the satellites
     //
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

     //
     // use this functions to get information about the satellites
     //
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


     //
     // use this functions to modify the widget
     //

     // set the margin between the 0 degree circle and the boarder
     void     setMarginScale    ( float          scale ); 

     // set the size of the satellites relative to the widget size
     void     setSatelliteScale ( float          scale );

     // set the font size relative to the widget size
     void     setFontScale      ( float          scale );

     // set the grid color
     void     setGridColor      ( const QColor & color );

     // set the gird width
     void     setGridWidth      ( int            width );

     // set the number of elevation ellipses
     void     setEllipses       ( int               no );

     // set the number of azimuth crosses
     void     setCrosses        ( int               no );

     // set the margin of the grid-labels
     void     setTextMargin     ( int           margin );

     // set the blinking interval
     void     setBlinkIntervall ( int        intervall );

     // turn on/off grid labels
     void     setWithGridLabels ( int       withLabels );

     // turn on/off anti-aliasing
     void     setAntialiased    ( int      antialiased );



