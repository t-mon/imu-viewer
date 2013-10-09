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

#ifndef COMPASS_H
#define COMPASS_H

#include <QWidget>
#include <QPixmap>

class Compass : public QWidget
{
    Q_OBJECT
public:
    explicit Compass(QWidget *parent = 0);

private:
    void paintEvent(QPaintEvent *event);
    float m_angle;

signals:

public slots:
    void updateAngle(float angle);

};

#endif // COMPASS_H
