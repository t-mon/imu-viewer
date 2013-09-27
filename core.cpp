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
