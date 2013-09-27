#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <mainwindow.h>
#include <tcpclient.h>

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = 0);

private:
    MainWindow *m_window;
    TcpClient *m_client;
signals:

public slots:

};

#endif // CORE_H
