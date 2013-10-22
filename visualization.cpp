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

#include <QtGui>
#include <QtOpenGL>
#include <QGLWidget>
#include <GL/glut.h>


#include "visualization.h"

Visualization::Visualization(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
{
}

void Visualization::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Visualization::resizeGL(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0,(GLdouble)width/(GLdouble)height,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,width,height);
}

void Visualization::paintGL()
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //Set blending function.
    //glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);

    glTranslatef(0.0,0.0,-2.5);
    glRotatef(xRot + 90 , 1.0, 0.0, 0.0); // +90 to see in the right position
    glRotatef(yRot      , 0.0, 1.0, 0.0);
    glRotatef(zRot +180 , 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    drawObject();
    drawWiredQuader(0.2,1,0.5);
    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_BLEND);
    drawKoordinateSystem();
}

void Visualization::drawObject()
{
    glColor4f(0.5,0.5,0.0,1.0);
    // z ____________________________________________
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.25f,  0.1f);
    glVertex3f( 0.5f, -0.25f,  0.1f);
    glVertex3f( 0.5f,  0.25f,  0.1f);
    glVertex3f(-0.5f,  0.25f,  0.1f);
    glEnd();

    // -z ____________________________________________
    glBegin(GL_QUADS);
    glVertex3f( 0.5f, -0.25f, -0.1f);
    glVertex3f(-0.5f, -0.25f, -0.1f);
    glVertex3f(-0.5f,  0.25f, -0.1f);
    glVertex3f( 0.5f,  0.25f, -0.1f);
    glEnd();

    // x ____________________________________________
    glBegin(GL_QUADS);
    glVertex3f( 0.5f, -0.25f,  0.1f);
    glVertex3f( 0.5f, -0.25f, -0.1f);
    glVertex3f( 0.5f,  0.25f, -0.1f);
    glVertex3f( 0.5f,  0.25f,  0.1f);
    glEnd();

    // -x ____________________________________________
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.25f, -0.1f);
    glVertex3f(-0.5f, -0.25f,  0.1f);
    glVertex3f(-0.5f,  0.25f,  0.1f);
    glVertex3f(-0.5f,  0.25f, -0.1f);
    glEnd();

    // y ____________________________________________
    glBegin(GL_QUADS);
    glVertex3f(-0.5f,  0.25f,  0.1f);
    glVertex3f( 0.5f,  0.25f,  0.1f);
    glVertex3f( 0.5f,  0.25f, -0.1f);
    glVertex3f(-0.5f,  0.25f, -0.1f);
    glEnd();

    // -y ____________________________________________
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.25f, -0.1f);
    glVertex3f( 0.5f, -0.25f, -0.1f);
    glVertex3f( 0.5f, -0.25f,  0.1f);
    glVertex3f(-0.5f, -0.25f,  0.1f);
    glEnd();
}

void Visualization::drawWiredQuader(float height, float lenght, float width)
{
    height = height/2;
    lenght = lenght/2;
    width  = width/2;

    glDisable(GL_DEPTH_TEST);
    glColor4f(0.0,1.0,0.0,0.2);
    glBegin(GL_LINES);
    glVertex3f(-lenght, -width,  height);
    glVertex3f( lenght, -width,  height);

    glVertex3f( lenght,  width,  height);
    glVertex3f(-lenght,  width,  height);

    glVertex3f(-lenght, -width, -height);
    glVertex3f( lenght, -width, -height);

    glVertex3f( lenght,  width, -height);
    glVertex3f(-lenght,  width, -height);

    glVertex3f(-lenght, -width,  height);
    glVertex3f(-lenght, -width, -height);

    glVertex3f( lenght, -width,  height);
    glVertex3f( lenght, -width, -height);

    glVertex3f(-lenght,  width,  height);
    glVertex3f(-lenght,  width, -height);

    glVertex3f( lenght,  width,  height);
    glVertex3f( lenght,  width, -height);

    glVertex3f(-lenght, -width,  height);
    glVertex3f(-lenght,  width,  height);

    glVertex3f(-lenght, -width, -height);
    glVertex3f(-lenght,  width, -height);

    glVertex3f( lenght, -width, -height);
    glVertex3f( lenght,  width, -height);

    glVertex3f( lenght,  width,  height);
    glVertex3f( lenght, -width,  height);
    glEnd();
    glEnable(GL_DEPTH_TEST);
}

void Visualization::drawKoordinateSystem()
{

    float length = 0.8;
    glBegin(GL_LINES);
    // x
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(length,0,0);
    // y
    glColor3f(1,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,length,0);
    // z
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,length);
    glEnd();

    // x-arrow
    glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(length,0,0);
    glRotatef(90,0,1,0);
    glutSolidCone(length/38,length/18,10,10);
    glTranslatef(-length,0,0);
    glRotatef(-90,0,1,0);
    glPopMatrix();

    // y-arrow
    glPushMatrix();
    glColor3f(1,0,1);
    glTranslatef(0,length,0);
    glRotatef(-90,1,0,0);
    glutSolidCone(length/38,length/18,10,10);
    glTranslatef(0,-length,0);
    glRotatef(90,1,0,0);
    glPopMatrix();

    // z-arrow
    glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(0,0,length);
    glutSolidCone(length/38,length/18,10,10);
    glTranslatef(0,0,-length);
    glPopMatrix();

}

void Visualization::updateAngles(const float &roll, const float &pitch, const float &yaw)
{
    xRot = (int)pitch;
    yRot = (int)roll;
    zRot = (int)yaw * (-1);
    updateGL();
}
