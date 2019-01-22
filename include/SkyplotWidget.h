// SkyplotWidget
// Copyright (C) 2011-2019 Christian Haettich feddischson[at]gmail.com
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA

#ifndef _SKYPLOT_WIDGET_H
#define _SKYPLOT_WIDGET_H
#include <QMap>
#include <QTimer>

#ifndef SKYPLOT_QML_SUPPORT
#include <QWidget>
#else
#include <QQuickPaintedItem>
#include <QtQml>
#endif

#define MY_PI 3.141593

#include "SkyplotWidget_global.h"

#ifndef SKYPLOT_QML_SUPPORT
class SKYPLOTWIDGET_EXPORT SkyplotWidget : public QWidget
#else
class SKYPLOTWIDGET_EXPORT SkyplotWidget : public QQuickPaintedItem
#endif
{
   Q_OBJECT

   Q_CLASSINFO("Version", _SKP_VERSION)
   Q_PROPERTY(qreal marginScale READ marginScale WRITE setMarginScale)
   Q_PROPERTY(qreal satelliteScale READ satelliteScale WRITE setSatelliteScale)
   Q_PROPERTY(qreal fontScale READ fontScale WRITE setFontScale)
   Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor)
   Q_PROPERTY(QColor gridTextColor READ gridTextColor WRITE setGridTextColor)
   Q_PROPERTY(qreal gridWidth READ gridWidth WRITE setGridWidth)
   Q_PROPERTY(int ellipses READ ellipses WRITE setEllipses)
   Q_PROPERTY(int crosses READ crosses WRITE setCrosses)
   Q_PROPERTY(int textMargin READ textMargin WRITE setTextMargin)
   Q_PROPERTY(int flashIntervall READ flashIntervall WRITE
                  setFlashIntervall)
   Q_PROPERTY(bool withGridLabels READ withGridLabels WRITE setWithGridLabels)
   Q_PROPERTY(bool antialiased READ antialiased WRITE setAntialiased)

  public:
   enum SatelliteState : quint8 {
      Invisible = 0x00,
      Visible = 0x01,
      HalfVisible = 0x02,
      Marked = 0x04,
      Flashing = 0x08
   };
   Q_ENUMS(SatelliteState)

#ifndef SKYPLOT_QML_SUPPORT
   explicit SkyplotWidget(QWidget* parent = nullptr);
#else
   SkyplotWidget(QQuickPaintedItem* parent = nullptr);
#endif

#ifdef SKYPLOT_QML_SUPPORT
   static void declareQml() {
      qmlRegisterType<SkyplotWidget>("SkyplotWidget", _SKP_VERSION_MAJ,
                                     _SKP_VERSION_MIN, "SkyplotWidget");
      qmlRegisterType<SkyplotWidget>("SatelliteState", _SKP_VERSION_MAJ,
                                     _SKP_VERSION_MIN, "SatelliteState");
   }
#endif

   SkyplotWidget(const SkyplotWidget& spw) = delete;
   SkyplotWidget& operator=(const SkyplotWidget& spw) = delete;
   SkyplotWidget(SkyplotWidget&& rhs) = delete;
   SkyplotWidget& operator=(SkyplotWidget&& rhs) = delete;
   ~SkyplotWidget() = default;

   void setMarginScale(qreal scale) {
      p_marginScale = scale;
      this->update();
   }
   void setSatelliteScale(qreal scale) {
      p_satScale = scale;
      this->update();
   }
   void setFontScale(qreal scale) {
      p_fontScale = scale;
      this->update();
   }
   void setGridColor(const QColor& color) {
      p_gridColor = color;
      this->update();
   }
   void setGridTextColor(const QColor& color) {
      p_gridTextColor = color;
      this->update();
   }
   void setGridWidth(qreal width) {
      p_gridWidth = width;
      this->update();
   }
   void setEllipses(quint16 no) {
      p_ellipses = no;
      this->update();
   }
   void setCrosses(quint16 no) {
      p_crosses = no;
      this->update();
   }
   void setTextMargin(qint16 margin) {
      p_textMargin = margin;
      this->update();
   }
   void setFlashIntervall(quint16 intervall) {
      p_flashIntervall = intervall;
      flashTimer.setInterval(p_flashIntervall);
      this->update();
   }
   void setWithGridLabels(int withLabels) {
      p_withGridLabels = withLabels;
      this->update();
   }
   void setAntialiased(int antialiased) {
      p_antialiased = antialiased;
      this->update();
   }

   qreal marginScale() const { return p_marginScale; }
   qreal satelliteScale() const { return p_satScale; }
   qreal fontScale() const { return p_fontScale; }
   const QColor& gridColor() const { return p_gridColor; }
   const QColor& gridTextColor() const { return p_gridTextColor; }
   int gridWidth() const { return p_gridWidth; }
   quint16 ellipses() const { return p_ellipses; }
   quint16 crosses() const { return p_crosses; }
   qint16 textMargin() const { return p_textMargin; }
   quint16 flashIntervall() const { return p_flashIntervall; }
   int withGridLabels() const { return p_withGridLabels; }
   int antialiased() const { return p_antialiased; }

   QColor innerColor(quint32 id) const;
   QColor outerColor(quint32 id) const;
   QColor fontColor(quint32 id) const;
   SatelliteState state(quint32 id) const;
   QString label(quint32 id) const;
   qreal azimuth(quint32 id) const;
   qreal elevation(quint32 id) const;

   QList<quint32> ids() const;

  public slots:

   void insert(quint32 id, qreal az = 0, qreal el = 90.0,
               const QString& label = QString(""),
               const QColor& outerColor = Qt::red,
               const QColor& innerColor = Qt::lightGray,
               const QColor& fontColor = Qt::black,
               SatelliteState state = SatelliteState::Visible);

   void remove(quint32 id);

   bool contains(quint32 id) const;

   void setInnerColor(quint32 id, const QColor& c);
   void setOuterColor(quint32 id, const QColor& c);
   void setFontColor(quint32 id, const QColor& c);
   void setState(quint32 id, SatelliteState state);
   void setLabel(quint32 id, const QString& label);
   void setAzimuth(quint32 id, qreal az);
   void setElevation(quint32 id, qreal el);

  protected:
#ifndef SKYPLOT_QML_SUPPORT
   void paintEvent(QPaintEvent* event);
#else
   void paint(QPainter* painter);
#endif

  private:
   bool flash;
   QTimer flashTimer;

   qreal p_marginScale;
   qreal p_satScale;
   qreal p_fontScale;
   QColor p_gridColor;
   QColor p_gridTextColor;
   qreal p_gridWidth;
   quint16 p_ellipses;
   quint16 p_crosses;
   qint16 p_textMargin;
   quint16 p_flashIntervall;
   bool p_withGridLabels;
   bool p_antialiased;

   typedef struct _Satellite {
      QString label;
      QColor innerColor;
      QColor outerColor;
      QColor fontColor;
      qreal az;
      qreal el;
      SatelliteState state;
   } Satellite;

   QHash<quint32, Satellite> satellites;

  private slots:
   void change_flash();
};

SkyplotWidget::SatelliteState operator|(SkyplotWidget::SatelliteState lhs,
                                        SkyplotWidget::SatelliteState rhs);

#endif

// vim: filetype=cpp et ts=3 sw=3 sts=3
