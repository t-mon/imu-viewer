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

    glTranslatef(0.0,0.0,-3);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.

    drawObject();

    glDisable(GL_DEPTH_TEST);
    drawKoordinateSystem();
    glEnable(GL_DEPTH_TEST);

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


    glColor4f(1.0,0.0,1.0,0.5);
    glRotatef(90,14,0,0);
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.25f,  0.1f);
    glVertex3f( 0.5f, -0.25f,  0.1f);
    glVertex3f( 0.5f,  0.25f,  0.1f);
    glVertex3f(-0.5f,  0.25f,  0.1f);
    glEnd();

    glColor4f(1.0,0.0,1.0,0.5);
    glBegin(GL_QUADS);
    glVertex3f( 0.5f, -0.25f, -0.1f);
    glVertex3f(-0.5f, -0.25f, -0.1f);
    glVertex3f(-0.5f,  0.25f, -0.1f);
    glVertex3f( 0.5f,  0.25f, -0.1f);
    glEnd();

    glColor4f(0.0,1.0,0.0,0.5);
    glBegin(GL_QUADS);
    glVertex3f( 0.5f, -0.25f,  0.1f);
    glVertex3f( 0.5f, -0.25f, -0.1f);
    glVertex3f( 0.5f,  0.25f, -0.1f);
    glVertex3f( 0.5f,  0.25f,  0.1f);
    glEnd();

    glColor4f(0.0,0.0,1.0,0.5);
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.25f, -0.1f);
    glVertex3f(-0.5f, -0.25f,  0.1f);
    glVertex3f(-0.5f,  0.25f,  0.1f);
    glVertex3f(-0.5f,  0.25f, -0.1f);
    glEnd();

    glColor4f(1.0,0.0,0.0,0.5);
    glBegin(GL_QUADS);
    glVertex3f(-0.5f,  0.25f,  0.1f);
    glVertex3f( 0.5f,  0.25f,  0.1f);
    glVertex3f( 0.5f,  0.25f, -0.1f);
    glVertex3f(-0.5f,  0.25f, -0.1f);
    glEnd();

    glColor4f(1.0,1.0,0.0,0.5);
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.25f, -0.1f);
    glVertex3f( 0.5f, -0.25f, -0.1f);
    glVertex3f( 0.5f, -0.25f,  0.1f);
    glVertex3f(-0.5f, -0.25f,  0.1f);
    glEnd();
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

    xRot = (int)roll;
    yRot = (int)yaw;
    zRot = (int)pitch;
    updateGL();
}
