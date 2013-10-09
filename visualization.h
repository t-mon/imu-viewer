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

#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <QObject>
#include <QGLWidget>
#include <qgl.h>

class Visualization : public QGLWidget
{
    Q_OBJECT
public:
    explicit Visualization(QWidget *parent = 0);

private:
    float xRot;
    float yRot;
    float zRot;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void drawObject();
    void drawKoordinateSystem();
    void drawCylinder(float radius, float height);


signals:

public slots:
    void updateAngles(const float &roll, const float &pitch, const float &yaw);


};

#endif // VISUALIZATION_H
