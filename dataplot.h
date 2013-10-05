#ifndef DATAPLOT_H
#define DATAPLOT_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QTabWidget>
#include <QTimer>
#include <QVector>
#include <QVector3D>

#include <qcustomplot.h>
#include <visualization.h>

class DataPlot : public QWidget
{
    Q_OBJECT
public:
    explicit DataPlot(QWidget *parent = 0);
    void updateSensorData(const QVector3D &accData, const QVector3D &gyrData, const QVector3D &magData);
    void updateAngleData(const QVector3D &angleData);

    QWidget *createAccPlot();
    QWidget *createGyrPlot();
    QWidget *createMagPlot();
    QWidget *createAnglePlot();

private:
    QTabWidget *m_tabWidget;
    Visualization *m_visualization;

    // plot data
    QCustomPlot *m_accPlot;
    QCustomPlot *m_gyrPlot;
    QCustomPlot *m_magPlot;
    QCustomPlot *m_anglePlot;

    QTimer *m_timer;
    double m_tickCounter;

    QVector<double> m_acc_x_Values;
    QVector<double> m_acc_y_Values;
    QVector<double> m_acc_z_Values;

    QVector<double> m_gyr_x_Values;
    QVector<double> m_gyr_y_Values;
    QVector<double> m_gyr_z_Values;

    QVector<double> m_mag_x_Values;
    QVector<double> m_mag_y_Values;
    QVector<double> m_mag_z_Values;

    QVector<double> m_angle_x_Values;
    QVector<double> m_angle_y_Values;
    QVector<double> m_angle_z_Values;


    QVector<double> m_timestamps;



private slots:
    void timerCounter();

signals:

public slots:
    void plotting(const bool &enable);

};

#endif // DATAPLOT_H
