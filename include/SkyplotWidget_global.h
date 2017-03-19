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



#ifndef _SKYPLOT_WIDGET_GLOBAL_H
#define _SKYPLOT_WIDGET_GLOBAL_H
 #include <QtCore/QtGlobal>


#if defined(SKYPLOTWIDGET_STATIC)
#  define SKYPLOTWIDGET_EXPORT
#elif defined(SKYPLOTWIDGET_LIBRARY)
 # define SKYPLOTWIDGET_EXPORT Q_DECL_EXPORT
#else
 #  define SKYPLOTWIDGET_EXPORT Q_DECL_IMPORT
 #endif

#endif

// vim: filetype=cpp et ts=3 sw=3 sts=3

