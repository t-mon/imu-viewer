#include <QtGui>
#include <QtOpenGL>
#include <QGLWidget>
#include <qgl.h>
#include <QMatrix4x4>
#include <QVector3D>
#include <qmath.h>
#include <GL/glut.h>
#include <GL/gl.h>


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
    //gluLookAt(0,0,-10,0,0,0,0,0,0);
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

    glTranslatef(0.0,0.0,-5);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glutWireCube(1);

    drawObject();
}

void Visualization::mousePressEvent(QMouseEvent *event)
{

}

void Visualization::mouseMoveEvent(QMouseEvent *event)
{

}

void Visualization::wheelEvent(QWheelEvent *event)
{

}

void Visualization::drawObject()
{
    //drawCylinder(1,1);
}

void Visualization::drawCylinder(float radius, float height)
{
    int slices = 32;

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluQuadricDrawStyle(quadratic,GL_POINT);
    gluCylinder(quadratic,radius,radius,height,slices,slices);
    gluQuadricDrawStyle(quadratic, GL_POINT);
    gluDisk(quadratic,0,radius,slices,slices);
    glPushMatrix();
    glTranslatef(0,0,height);
    gluQuadricDrawStyle(quadratic, GL_POINT);
    gluDisk(quadratic,0,radius,slices,slices);
    glPopMatrix();
}

void Visualization::updateAngles(const float &roll, const float &pitch, const float &yaw)
{
    xRot = pitch;
    yRot = roll;
    zRot = yaw;
    updateGL();
}
