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
