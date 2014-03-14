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



#include "SkyplotWidgetPlugin.h"
#include "SkyplotWidget.h"
#include <qplugin.h>


SkyplotWidgetPlugin::SkyplotWidgetPlugin( QObject* parent )
{

}

SkyplotWidgetPlugin::~SkyplotWidgetPlugin()
{

}


QString  
SkyplotWidgetPlugin::name ( void ) const
{
   return QString( "SkyplotWidget" );
}

QString  
SkyplotWidgetPlugin::includeFile ( void ) const
{
   return QString( "SkyplotWidget.h" );
}

QString  
SkyplotWidgetPlugin::group ( void ) const
{
   return QString( "" );

}

QIcon    
SkyplotWidgetPlugin::icon ( void ) const
{
   return QIcon();
}

QString  
SkyplotWidgetPlugin::toolTip ( void ) const
{
   return QString( "Skyplot Widget" );

}

QString  
SkyplotWidgetPlugin::whatsThis ( void ) const
{
   return QString( "Skyplot Widget to visualize satellite position data" );

}

bool     
SkyplotWidgetPlugin::isContainer ( void ) const
{
   return false;
}

QWidget* 
SkyplotWidgetPlugin::createWidget( QWidget* parent )
{
   return new SkyplotWidget( parent );
}




Q_EXPORT_PLUGIN2( SkyplotWidget, SkyplotWidgetPlugin )

