// SkyplotWidget
// Copyright (C) 2011 Christian Haettich feddischson[at]gmx.com
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


#include <QDesignerCustomWidgetInterface>

class SkyplotWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
   Q_OBJECT
   Q_INTERFACES(QDesignerCustomWidgetInterface)

   public:
      SkyplotWidgetPlugin( QObject* parent=0 );
      ~SkyplotWidgetPlugin();

      QString  name        ( void ) const;
      QString  includeFile ( void ) const;
      QString  group       ( void ) const;
      QIcon    icon        ( void ) const;
      QString  toolTip     ( void ) const;
      QString  whatsThis   ( void ) const;
      bool     isContainer ( void ) const;
      QWidget* createWidget( QWidget* parent );

};

