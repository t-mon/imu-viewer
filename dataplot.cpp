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

#include "dataplot.h"


DataPlot::DataPlot(QWidget *parent) :
    QWidget(parent)
{
    m_accPlot = new QCustomPlot(this);
    m_gyrPlot = new QCustomPlot(this);
    m_magPlot = new QCustomPlot(this);
    m_anglePlot = new QCustomPlot(this);

    m_timer = new QTimer(this);
    m_timer->setInterval(20);
    m_tickCounter = 0;

    connect(m_timer,SIGNAL(timeout()),this,SLOT(timerCounter()));
}

QWidget *DataPlot::createAccPlot()
{
    // setup plot
    m_accPlot->yAxis->setRange(-256,256);
    m_accPlot->xAxis->setTickLength(1);

    // set some pens, brushes and backgrounds:
    m_accPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    m_accPlot->yAxis->setBasePen(QPen(Qt::white, 1));
    m_accPlot->xAxis->setTickPen(QPen(Qt::white, 1));
    m_accPlot->yAxis->setTickPen(QPen(Qt::white, 1));
    m_accPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    m_accPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    m_accPlot->xAxis->setTickLabelColor(Qt::white);
    m_accPlot->yAxis->setTickLabelColor(Qt::white);
    m_accPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_accPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_accPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_accPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_accPlot->xAxis->grid()->setSubGridVisible(true);
    m_accPlot->yAxis->grid()->setSubGridVisible(true);
    m_accPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_accPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_accPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    m_accPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    m_accPlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    m_accPlot->axisRect()->setBackground(axisRectGradient);

    // create graphs

    // Acc x graph
    m_accPlot->addGraph();
    m_accPlot->graph(0)->setData(m_acc_x_Values,m_timestamps);
    m_accPlot->graph(0)->setPen(QPen(Qt::blue));

    // Acc y graph
    m_accPlot->addGraph();
    m_accPlot->graph(1)->setData(m_acc_y_Values,m_timestamps);
    m_accPlot->graph(1)->setPen(QPen(Qt::red));

    // Acc z graph
    m_accPlot->addGraph();
    m_accPlot->graph(2)->setData(m_acc_z_Values,m_timestamps);
    m_accPlot->graph(2)->setPen(QPen(Qt::green));

    m_accPlot->replot();
    return m_accPlot;
}

QWidget *DataPlot::createGyrPlot()
{
    // setup plot
    m_gyrPlot->yAxis->setRange(-2000,2000);
    m_gyrPlot->xAxis->setTickStep(2);

    // set some pens, brushes and backgrounds:
    m_gyrPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    m_gyrPlot->yAxis->setBasePen(QPen(Qt::white, 1));
    m_gyrPlot->xAxis->setTickPen(QPen(Qt::white, 1));
    m_gyrPlot->yAxis->setTickPen(QPen(Qt::white, 1));
    m_gyrPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    m_gyrPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    m_gyrPlot->xAxis->setTickLabelColor(Qt::white);
    m_gyrPlot->yAxis->setTickLabelColor(Qt::white);
    m_gyrPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_gyrPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_gyrPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_gyrPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_gyrPlot->xAxis->grid()->setSubGridVisible(true);
    m_gyrPlot->yAxis->grid()->setSubGridVisible(true);
    m_gyrPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_gyrPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_gyrPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    m_gyrPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    m_gyrPlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    m_gyrPlot->axisRect()->setBackground(axisRectGradient);

    // create graphs
    m_gyrPlot->addGraph();
    m_gyrPlot->graph(0)->setData(m_gyr_x_Values,m_timestamps);
    m_gyrPlot->graph(0)->setPen(QPen(Qt::blue));

    // gyr y graph
    m_gyrPlot->addGraph();
    m_gyrPlot->graph(1)->setData(m_gyr_y_Values,m_timestamps);
    m_gyrPlot->graph(1)->setPen(QPen(Qt::red));

    // gyr z graph
    m_gyrPlot->addGraph();
    m_gyrPlot->graph(2)->setData(m_gyr_z_Values,m_timestamps);
    m_gyrPlot->graph(2)->setPen(QPen(Qt::green));

    m_gyrPlot->replot();
    return m_gyrPlot;
}

QWidget *DataPlot::createMagPlot()
{
    // setup plot
    m_magPlot->yAxis->setRange(-600,600);

    // set some pens, brushes and backgrounds:
    m_magPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    m_magPlot->yAxis->setBasePen(QPen(Qt::white, 1));
    m_magPlot->xAxis->setTickPen(QPen(Qt::white, 1));
    m_magPlot->yAxis->setTickPen(QPen(Qt::white, 1));
    m_magPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    m_magPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    m_magPlot->xAxis->setTickLabelColor(Qt::white);
    m_magPlot->yAxis->setTickLabelColor(Qt::white);
    m_magPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_magPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_magPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_magPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_magPlot->xAxis->grid()->setSubGridVisible(true);
    m_magPlot->yAxis->grid()->setSubGridVisible(true);
    m_magPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_magPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_magPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    m_magPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    m_magPlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    m_magPlot->axisRect()->setBackground(axisRectGradient);

    // create graphs
    m_magPlot->addGraph();
    m_magPlot->graph(0)->setData(m_mag_x_Values,m_timestamps);
    m_magPlot->graph(0)->setPen(QPen(Qt::blue));

    // mag y graph
    m_magPlot->addGraph();
    m_magPlot->graph(1)->setData(m_mag_y_Values,m_timestamps);
    m_magPlot->graph(1)->setPen(QPen(Qt::red));

    // mag z graph
    m_magPlot->addGraph();
    m_magPlot->graph(2)->setData(m_mag_z_Values,m_timestamps);
    m_magPlot->graph(2)->setPen(QPen(Qt::green));

    m_magPlot->replot();
    return m_magPlot;
}

QWidget *DataPlot::createAnglePlot()
{
    // setup plot
    m_anglePlot->yAxis->setRange(-180,180);

    // set some pens, brushes and backgrounds:
    m_anglePlot->xAxis->setBasePen(QPen(Qt::white, 1));
    m_anglePlot->yAxis->setBasePen(QPen(Qt::white, 1));
    m_anglePlot->xAxis->setTickPen(QPen(Qt::white, 1));
    m_anglePlot->yAxis->setTickPen(QPen(Qt::white, 1));
    m_anglePlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    m_anglePlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    m_anglePlot->xAxis->setTickLabelColor(Qt::white);
    m_anglePlot->yAxis->setTickLabelColor(Qt::white);
    m_anglePlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_anglePlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_anglePlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_anglePlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_anglePlot->xAxis->grid()->setSubGridVisible(true);
    m_anglePlot->yAxis->grid()->setSubGridVisible(true);
    m_anglePlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_anglePlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_anglePlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    m_anglePlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    m_anglePlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    m_anglePlot->axisRect()->setBackground(axisRectGradient);

    // create graphs
    m_anglePlot->addGraph();
    m_anglePlot->graph(0)->setData(m_angle_x_Values,m_timestamps);
    m_anglePlot->graph(0)->setPen(QPen(Qt::blue));

    // angle y graph
    m_anglePlot->addGraph();
    m_anglePlot->graph(1)->setData(m_angle_y_Values,m_timestamps);
    m_anglePlot->graph(1)->setPen(QPen(Qt::red));

    // angle z graph
    m_anglePlot->addGraph();
    m_anglePlot->graph(2)->setData(m_angle_z_Values,m_timestamps);
    m_anglePlot->graph(2)->setPen(QPen(Qt::green));

    m_anglePlot->replot();
    return m_anglePlot;
}

void DataPlot::timerCounter()
{
    m_tickCounter+= 0.025;

    m_accPlot->xAxis->setRange(m_tickCounter-10,m_tickCounter +2);
    m_gyrPlot->xAxis->setRange(m_tickCounter-10,m_tickCounter +2);
    m_magPlot->xAxis->setRange(m_tickCounter-10,m_tickCounter +2);
    m_anglePlot->xAxis->setRange(m_tickCounter-10,m_tickCounter +2);

    m_accPlot->replot();
    m_gyrPlot->replot();
    m_magPlot->replot();
    m_anglePlot->replot();
}

void DataPlot::plotting(const bool &enable)
{
    if(enable){
        m_timer->start();
    }else{
        m_timer->stop();
    }
}

void DataPlot::updateSensorData(const QVector3D &accData, const QVector3D &gyrData, const QVector3D &magData)
{
    int dataLength = 500;

    // save timestamp
    m_timestamps.append(m_tickCounter);

    // acc
    m_acc_x_Values.append(accData.x());
    m_acc_y_Values.append(accData.y());
    m_acc_z_Values.append(accData.z());
    m_accPlot->graph(0)->setData(m_timestamps,m_acc_x_Values);
    m_accPlot->graph(1)->setData(m_timestamps,m_acc_y_Values);
    m_accPlot->graph(2)->setData(m_timestamps,m_acc_z_Values);

    //gyr
    m_gyr_x_Values.append(gyrData.x());
    m_gyr_y_Values.append(gyrData.y());
    m_gyr_z_Values.append(gyrData.z());
    m_gyrPlot->graph(0)->setData(m_timestamps,m_gyr_x_Values);
    m_gyrPlot->graph(1)->setData(m_timestamps,m_gyr_y_Values);
    m_gyrPlot->graph(2)->setData(m_timestamps,m_gyr_z_Values);

    // mag
    m_mag_x_Values.append(magData.x());
    m_mag_y_Values.append(magData.y());
    m_mag_z_Values.append(magData.z());
    m_magPlot->graph(0)->setData(m_timestamps,m_mag_x_Values);
    m_magPlot->graph(1)->setData(m_timestamps,m_mag_y_Values);
    m_magPlot->graph(2)->setData(m_timestamps,m_mag_z_Values);

    // change vector leght
    if(m_timestamps.count() > dataLength){
        m_timestamps.remove(0);
    }

    if(m_acc_x_Values.count() > dataLength){
        m_acc_x_Values.remove(0);
    }
    if(m_acc_y_Values.count() > dataLength){
        m_acc_y_Values.remove(0);
    }
    if(m_acc_z_Values.count() > dataLength){
        m_acc_z_Values.remove(0);
    }


    if(m_gyr_x_Values.count() > dataLength){
        m_gyr_x_Values.remove(0);
    }
    if(m_gyr_y_Values.count() > dataLength){
        m_gyr_y_Values.remove(0);
    }
    if(m_gyr_z_Values.count() > dataLength){
        m_gyr_z_Values.remove(0);
    }


    if(m_mag_x_Values.count() > dataLength){
        m_mag_x_Values.remove(0);
    }
    if(m_mag_y_Values.count() > dataLength){
        m_mag_y_Values.remove(0);
    }
    if(m_mag_z_Values.count() > dataLength){
        m_mag_z_Values.remove(0);
    }


}

void DataPlot::updateAngleData(const QVector3D &angleData)
{

    int dataLength = 500;

    // angle
    m_angle_x_Values.append(angleData.x());
    m_angle_y_Values.append(angleData.y());
    m_angle_z_Values.append(angleData.z());
    m_anglePlot->graph(0)->setData(m_timestamps,m_angle_x_Values);
    m_anglePlot->graph(1)->setData(m_timestamps,m_angle_y_Values);
    m_anglePlot->graph(2)->setData(m_timestamps,m_angle_z_Values);

    if(m_angle_x_Values.count() > dataLength){
        m_angle_x_Values.remove(0);
    }
    if(m_angle_y_Values.count() > dataLength){
        m_angle_y_Values.remove(0);
    }
    if(m_angle_z_Values.count() > dataLength){
        m_angle_z_Values.remove(0);
    }

}
