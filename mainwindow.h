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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>

#include <visualization.h>
#include <qcustomplot.h>
#include <dataplot.h>
#include <compass.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QLineEdit *hostLineEdit;
    QLineEdit *portLineEdit;
    QLabel *connectionStatusLabel;

    QLabel *accLableX;
    QLabel *accLableY;
    QLabel *accLableZ;

    QLabel *gyrLableX;
    QLabel *gyrLableY;
    QLabel *gyrLableZ;

    QLabel *magLableX;
    QLabel *magLableY;
    QLabel *magLableZ;

    QLabel *rollLabel;
    QLabel *pitchLabel;
    QLabel *yawLabel;

    QGroupBox *createConnectionGroupbox();
    QGroupBox *createAccDataGroupbox();
    QGroupBox *createGyrDataGroupbox();
    QGroupBox *createMagDataGroupbox();
    QGroupBox *createAngleGroupbox();

    QGroupBox *createVisualizazionGroupbox();

    DataPlot *m_dataPlot;
    Visualization *m_visualization;
    Compass *m_compass;

signals:
    void connectServer(const QString &ipAddress, const QString &port);
    void disconnectServer();
    void enablePlotting(const bool &connectionState);

private slots:
    void connectServerClicked();

public slots:
    void connectionStatusChanged(const bool &connectionState);
    void updateSensorData(const QVector3D &accData,const QVector3D &gyroData, const QVector3D &magData);
    void updateAngleData(const float &roll, const float &pitch, const float &yaw);


};

#endif // MAINWINDOW_H
