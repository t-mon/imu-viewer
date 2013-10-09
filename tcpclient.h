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

#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QVector3D>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = 0);

private:
    QTcpSocket *m_tcpSocket;

signals:
    void connectionStatusChanged(const bool &connectionState);
    void imuDataAvailable(const QVector3D &accData,const QVector3D &gyroData, const QVector3D &magData);
    void jsonDataAvailable(const QByteArray &data);
    void anglesAvailabe(const float &roll, const float &pitch, const float &yaw);
private slots:
    void connectionError(QAbstractSocket::SocketError error);
    void connected();
    void disconnected();
    void parseJsonData(const QByteArray &data);

public slots:
    void connectToHost(QString ipAddress, QString port);
    void disconnectFromHost();
    void sendData(QByteArray data);
    void readData();
};

#endif // TCPCLIENT_H
