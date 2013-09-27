#include <QDebug>
#include <QJsonDocument>

#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) :
    QObject(parent)
{
    m_tcpSocket = new QTcpSocket(this);

    connect(m_tcpSocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(m_tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(m_tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(connectionError(QAbstractSocket::SocketError)));

    connect(this,SIGNAL(jsonDataAvailable(QByteArray)),this,SLOT(parseJsonData(QByteArray)));
}

void TcpClient::connectionError(QAbstractSocket::SocketError error)
{
    emit connectionStatusChanged(false);
    qDebug() << "Connection ERROR: " << error;
}

void TcpClient::connected()
{
    emit connectionStatusChanged(true);
    qDebug() << "connected to server.";
    connect(m_tcpSocket,SIGNAL(readyRead()),this,SLOT(readData()));

}

void TcpClient::disconnected()
{
    emit connectionStatusChanged(false);
    qDebug() << "disconnected from server.";
}

void TcpClient::parseJsonData(const QByteArray &data)
{
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);

    if(error.error != QJsonParseError::NoError) {
        qDebug() << "failed to parse data" << data << ":" << error.errorString();
        return;
    }

    QVector3D accVector;
    QVector3D gyrVector;
    QVector3D magVector;

    QVariantMap messageMap = jsonDoc.toVariant().toMap();

    // check if we got all 3 sensordata
    if(messageMap.contains("acc")){
        QVariantMap accMap = messageMap.value("acc").toMap();
        accVector.setX(accMap.value("x").toFloat());
        accVector.setY(accMap.value("y").toFloat());
        accVector.setZ(accMap.value("z").toFloat());

        QVariantMap gyrMap = messageMap.value("gyr").toMap();
        gyrVector.setX(gyrMap.value("x").toFloat());
        gyrVector.setY(gyrMap.value("y").toFloat());
        gyrVector.setZ(gyrMap.value("z").toFloat());

        QVariantMap magMap = messageMap.value("mag").toMap();
        magVector.setX(magMap.value("x").toFloat());
        magVector.setY(magMap.value("y").toFloat());
        magVector.setZ(magMap.value("z").toFloat());

        emit imuDataAvailable(accVector,gyrVector,magVector);

    }
    // check if we got all angle data
    if(messageMap.contains("angles")){
        QVariantMap angleMap = messageMap.value("angles").toMap();
        float roll  = angleMap.value("roll").toFloat();
        float pitch = angleMap.value("pitch").toFloat();
        float yaw   = angleMap.value("yaw").toFloat();

        emit anglesAvailabe(roll,pitch,yaw);

    }else{
        qDebug() << "ERROR: message not complete.";
        return;
    }
}

void TcpClient::connectToHost(QString ipAddress, QString port)
{
    m_tcpSocket->connectToHost(QHostAddress(ipAddress), port.toInt());
}

void TcpClient::disconnectFromHost()
{
    m_tcpSocket->close();
}

void TcpClient::sendData(QByteArray data)
{
    m_tcpSocket->write(data + "\n");
}

void TcpClient::readData()
{
    QByteArray message;
    while(m_tcpSocket->canReadLine()){
        QByteArray dataLine = m_tcpSocket->readLine();
        message.append(dataLine);
        if(dataLine == "}\n"){
            //qDebug() << message;
            emit jsonDataAvailable(message);
            message.clear();
        }
    }
}
