/*
 *    This application is visualizes data from imu-utils over tcp
 *
 *    Copyright (C) 2013 Simon Stürz (stuerz.simon@gmail.com)
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "compass.h"
#include <QPainter>
#include <QColor>
#include <QStyleOption>

Compass::Compass(QWidget *parent) :
    QWidget(parent)
{
    m_angle = 0;

}

void Compass::paintEvent(QPaintEvent *event)
{


    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(Qt::black);
    p.drawRect(0,0,width(),height());

    // ---------------------needle--------------------------
    // triangle north left
    static const QPoint needleNL[3] = {
        QPoint(5, 0),
        QPoint(-5, 0),
        QPoint(0, -45)
    };
    // triangle north right
    static const QPoint needleNR[3] = {
        QPoint(-5, 0),
        QPoint(5, 0),
        QPoint(0, -45)
    };
    // triangle south left
    static const QPoint needleSL[3] = {
        QPoint(5, 0),
        QPoint(-5, 0),
        QPoint(0, 45)
    };
    // triangle south right
    static const QPoint needleSR[3] = {
        QPoint(-5, 0),
        QPoint(5, 0),
        QPoint(0, 45)
    };

    // define colors of needle parts
    QColor needleColorNL(255, 0, 0);
    QColor needleColorSR(0, 127, 127, 191);

    QColor needleColorNR(200, 0, 0);
    QColor needleColorSL(0, 100, 100, 191);

    // create painter
    QPainter painter(this);
    // draw black rectangle (background)

    // find the min sidelength
    int side = qMin(width(), height());
    // set render and translate the 0,0 koordinate in the midle of the widget
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    // scale the compass
    painter.scale(side / 130.0, side / 130.0);

    // save current painter setting
    painter.save();

    // rotate the needle
    painter.rotate(m_angle);

    // draw the needle
    painter.setPen(Qt::NoPen);
    painter.setBrush(needleColorNL);
    painter.drawConvexPolygon(needleNL, 4);

    painter.setPen(Qt::NoPen);
    painter.setBrush(needleColorNR);
    painter.drawConvexPolygon(needleNR, 4);

    painter.setPen(Qt::NoPen);
    painter.setBrush(needleColorSL);
    painter.drawConvexPolygon(needleSL, 4);

    painter.setPen(Qt::NoPen);
    painter.setBrush(needleColorSR);
    painter.drawConvexPolygon(needleSR, 4);

    // restore current painter setting
    painter.restore();

    // ---------------------compass rose--------------------------
    // green Pen
    QPen pen;
    pen.setWidth(0.5);
    pen.setBrush(Qt::green);
    pen.setStyle(Qt::SolidLine);

    painter.setPen(pen);
    painter.drawText(-5,-52,"N");
    painter.drawText(-80,-50,QString::number(((int)m_angle-360)*(-1))+"°");

    for(int i = 0; i < 360; ++i) {
        painter.drawLine(50, 0, 48, 0);
        painter.rotate(1.0);
    }
    for(int i = 0; i < 120; ++i) {
        painter.drawLine(50, 0, 46, 0);
        painter.rotate(3.0);
    }

    pen.setWidth(0.6);
    painter.setPen(pen);
    for(int i = 0; i < 8; ++i) {
        painter.drawLine(50, 0, 43, 0);
        painter.rotate(45.0);
    }
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawEllipse(QPoint(0,0),50,50);

}

void Compass::updateAngle(float angle)
{
    m_angle = angle;
    update();
}
