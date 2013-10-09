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
