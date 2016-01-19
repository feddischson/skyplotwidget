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
    : QObject(parent)
    , initialized(false)
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
   return QString( "Display Widgets [Examples]" );

}

QIcon    
SkyplotWidgetPlugin::icon ( void ) const
{
    return QIcon();
}

QString
SkyplotWidgetPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
            " <widget class=\"SkyplotWidget\" name=\"skyplotWidget\">\n"
            "  <property name=\"geometry\">\n"
            "   <rect>\n"
            "    <x>0</x>\n"
            "    <y>0</y>\n"
            "    <width>300</width>\n"
            "    <height>300</height>\n"
            "   </rect>\n"
            "  </property>\n"
            "  <property name=\"toolTip\" >\n"
            "   <string>The skyplot satellite widget</string>\n"
            "  </property>\n"
            "  <property name=\"whatsThis\" >\n"
            "   <string>The skyplot widget displays the satellite constellation.</string>\n"
            "  </property>\n"
            " </widget>\n"
            "</ui>\n";
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

void
SkyplotWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool
SkyplotWidgetPlugin::isInitialized() const
{
    return initialized;
}

QWidget* 
SkyplotWidgetPlugin::createWidget( QWidget* parent )
{
   return new SkyplotWidget( parent );
}
