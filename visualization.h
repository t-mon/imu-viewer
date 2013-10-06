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
