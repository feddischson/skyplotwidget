
Introduction
=============
The Skyplot widget is a small QT library to visualize satellite skyplots.
![screenshot-01](https://github.com/feddischson/skyplotwidget/blob/master/screenshots/screenshot01.jpeg)
![screenshot-02](https://github.com/feddischson/skyplotwidget/blob/master/screenshots/screenshot02.jpeg)


INSTALLATION:
===============


**If you have a command line by your hand, do**

```
      qmake
      make
      make install
```
to build and install the widgets.

This not only installs the Skyplot widget, it also installs a designer plugin.

To build the skyplot-widget with QML support, run the following:
```
      qmake DEFINES+=SKYPLOT_QML_SUPPORT
      make
      make install
```
A QML/QtQuick example can be found in `examples/main.qml` and `examples/main.cpp`.


**If you ware working with the Qt Creator:**

Open the file `SkyplotWidget.pro` and adapt the Project settings:
Add a custom build step with the make argument "install". After doing the build, the resulting files get installed.
On windows, the installation path is set to `c:/skyplotwidget-x.x.x`. This path can be adapted in `src/src.pro`.

**If you want to include the sources directly:**

You only need to include `SkyplotWidget.pri` in your `*.pro` file and you have to define `SKYPLOTWIDGET_STATIC`.
Have a look at `example/example.pro`.
The `SKYPLOTWIDGET_STATIC` disables the `Q_DECL_EXPORT` / `Q_DECL_IMPORT` behaviour for the library (only relevant for windows).


Usage:
=========
See https://github.com/feddischson/skyplotwidget/wiki


Versions
==============

2.0.1
------
 - Improves QML exampe
 - Improves C++ coding style
 - Improves internal types and interfaces
 - Fixes flash timer issue
 - Fixes build issues on windows

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
  Copyright (C) 2011-2017 Christian Haettich feddischson[at]gmail.com

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

