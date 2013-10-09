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

#include "core.h"

Core::Core(QObject *parent) :
    QObject(parent)
{
    m_window = new MainWindow();
    m_window->setMinimumSize(QSize(800,600));
    m_window->show();

    m_client = new TcpClient(this);

    connect(m_window,SIGNAL(connectServer(QString,QString)),m_client,SLOT(connectToHost(QString,QString)));
    connect(m_window,SIGNAL(disconnectServer()),m_client,SLOT(disconnectFromHost()));
    connect(m_client,SIGNAL(connectionStatusChanged(bool)),m_window,SLOT(connectionStatusChanged(bool)));
    connect(m_client,SIGNAL(imuDataAvailable(QVector3D,QVector3D,QVector3D)),m_window,SLOT(updateSensorData(QVector3D,QVector3D,QVector3D)));
    connect(m_client,SIGNAL(anglesAvailabe(float,float,float)),m_window,SLOT(updateAngleData(float,float,float)));
}
