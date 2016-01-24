
Introduction
=============
The Skyplot widget is a small QT library to visualize satellite skyplots.



INSTALLATION:
===============


Run the following

```
      qmake
      make
      make install
```
to build and install the widget.

To make the widget available for the designer, please copy
lib/libskyplotwidgetdesigner.so into your qt-designer's library directory.
Linux users may check the environment-variable `QT_PLUGIN_PATH`.

To build the skyplot-widget with QML support, run the following:
```
      qmake DEFINES+=SKYPLOT_QML_SUPPORT
      make
      make install
```
A QML/QtQuick example can be found in `examples/main.qml` and `examples/main.cpp`.





Usage:
=========
See https://github.com/feddischson/skyplotwidget/wiki


Versions
==============
2.0.0
------
 - Changes the interface
   - Shorter method names
   - Better handling of the state
   - More const declarations for getter methods
 - Requires c++11

1.1.0
-----
 - Adds QML Support

1.0.1
------
 - Placed code to a github repo
 - First stable version which supports
    - Adding and removing satellites
    - Different satellite states
    - Coloring (font, ring, satellite-background, widget-background)
    - Different configurations and styles



License
===============
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  SkyplotWidget
  Copyright (C) 2011-2016 Christian Haettich feddischson[at]gmx.com

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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

