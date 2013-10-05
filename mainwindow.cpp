#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QColor>
#include <QDebug>
#include <QVector>
#include <QVector3D>


#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setWindowTitle("IMU Viewer");

    QGridLayout *mainGridLayout = new QGridLayout(this);
    centralWidget->setLayout(mainGridLayout);

    m_visualization = new Visualization(this);

    mainGridLayout->addWidget(createConnectionGroupbox(),0,0,1,2);
    mainGridLayout->addWidget(createVisualizazionGroupbox(),1,0,4,1);
    mainGridLayout->addWidget(createAccDataGroupbox(),1,1);
    mainGridLayout->addWidget(createGyrDataGroupbox(),2,1);
    mainGridLayout->addWidget(createMagDataGroupbox(),3,1);
    mainGridLayout->addWidget(createAngleGroupbox(),4,1);

    connect(this,SIGNAL(enablePlotting(bool)),m_dataPlot,SLOT(plotting(bool)));
}

MainWindow::~MainWindow()
{
}

QGroupBox *MainWindow::createConnectionGroupbox()
{
    QGroupBox *serverConnectionGroupBox = new QGroupBox(tr("Server connection"),this);
    QHBoxLayout *serverConnectionGridLayout = new QHBoxLayout(serverConnectionGroupBox);

    QPushButton *connectServerButton = new QPushButton("Connect Server",serverConnectionGroupBox);
    QPushButton *disconnectServerButton = new QPushButton("Disconnect Server",serverConnectionGroupBox);

    //Connection Host
    connectionStatusLabel = new QLabel(this);
    connectionStatusLabel->setFixedWidth(25);
    connectionStatusLabel->setFixedHeight(25);
    connectionStatusLabel->setAlignment(Qt::AlignCenter);
    connectionStatusLabel->setText("");
    connectionStatusLabel->setStyleSheet("background-color:red; border-width:1px; border-radius: 12px;");

    hostLineEdit = new QLineEdit();
    hostLineEdit->setFixedWidth(130);
    hostLineEdit->setText("10.10.10.41");

    portLineEdit = new QLineEdit();
    portLineEdit->setFixedWidth(80);
    portLineEdit->setText("55555");

    serverConnectionGridLayout->addWidget(connectionStatusLabel);
    serverConnectionGridLayout->addWidget(connectServerButton);
    serverConnectionGridLayout->addWidget(disconnectServerButton);
    serverConnectionGridLayout->addWidget(hostLineEdit);
    serverConnectionGridLayout->addWidget(portLineEdit);

    serverConnectionGroupBox->setLayout(serverConnectionGridLayout);

    connect(connectServerButton,SIGNAL(clicked()),this,SLOT(connectServerClicked()));
    connect(disconnectServerButton,SIGNAL(clicked()),this,SIGNAL(disconnectServer()));

    serverConnectionGroupBox->setMaximumHeight(80);

    return serverConnectionGroupBox;
}

QGroupBox *MainWindow::createAccDataGroupbox()
{
    QGroupBox *accGroupBox = new QGroupBox(tr("Accelerometer"),this);
    QVBoxLayout *accLayout = new QVBoxLayout(accGroupBox);

    accGroupBox->setLayout(accLayout);

    accLableX = new QLabel(accGroupBox);
    accLableX->setText("0");

    accLableY = new QLabel(accGroupBox);
    accLableY->setText("0");

    accLableZ = new QLabel(accGroupBox);
    accLableZ->setText("0");

    accLayout->addWidget(accLableX);
    accLayout->addWidget(accLableY);
    accLayout->addWidget(accLableZ);

    accGroupBox->setMaximumWidth(150);

    return accGroupBox;
}

QGroupBox *MainWindow::createGyrDataGroupbox()
{
    QGroupBox *gyrGroupBox = new QGroupBox(tr("Gyroscope"),this);
    QVBoxLayout *gyrLayout = new QVBoxLayout(gyrGroupBox);

    gyrGroupBox->setLayout(gyrLayout);

    gyrLableX = new QLabel(gyrGroupBox);
    gyrLableX->setText("0");

    gyrLableY = new QLabel(gyrGroupBox);
    gyrLableY->setText("0");

    gyrLableZ = new QLabel(gyrGroupBox);
    gyrLableZ->setText("0");

    gyrLayout->addWidget(gyrLableX);
    gyrLayout->addWidget(gyrLableY);
    gyrLayout->addWidget(gyrLableZ);

    gyrGroupBox->setMaximumWidth(150);

    return gyrGroupBox;
}

QGroupBox *MainWindow::createMagDataGroupbox()
{
    QGroupBox *magGroupBox = new QGroupBox(tr("Magnetometer"),this);
    QVBoxLayout *magLayout = new QVBoxLayout(magGroupBox);

    magGroupBox->setLayout(magLayout);

    magLableX = new QLabel(magGroupBox);
    magLableX->setText("0");

    magLableY = new QLabel(magGroupBox);
    magLableY->setText("0");

    magLableZ = new QLabel(magGroupBox);
    magLableZ->setText("0");

    magLayout->addWidget(magLableX);
    magLayout->addWidget(magLableY);
    magLayout->addWidget(magLableZ);

    magGroupBox->setMaximumWidth(150);

    return magGroupBox;
}

QGroupBox *MainWindow::createAngleGroupbox()
{
    QGroupBox *angleGroupBox = new QGroupBox(tr("Angles"),this);
    QVBoxLayout *angleLayout = new QVBoxLayout(angleGroupBox);

    angleGroupBox->setLayout(angleLayout);

    rollLabel = new QLabel(angleGroupBox);
    rollLabel->setText("0");

    pitchLabel = new QLabel(angleGroupBox);
    pitchLabel->setText("0");

    yawLabel = new QLabel(angleGroupBox);
    yawLabel->setText("0");

    angleLayout->addWidget(rollLabel);
    angleLayout->addWidget(pitchLabel);
    angleLayout->addWidget(yawLabel);

    angleGroupBox->setMaximumWidth(150);

    return angleGroupBox;
}

QGroupBox *MainWindow::createVisualizazionGroupbox()
{
    QGroupBox *groupBox = new QGroupBox(tr("Vislualize Data"),this);
    QTabWidget *tabWidget = new QTabWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_dataPlot = new DataPlot(groupBox);

    tabWidget->addTab(m_visualization,"  3D  ");
    tabWidget->addTab(m_dataPlot->createAnglePlot(),"Angles");
    tabWidget->addTab(m_dataPlot->createAccPlot()," Acc  ");
    tabWidget->addTab(m_dataPlot->createGyrPlot()," Gyr  ");
    tabWidget->addTab(m_dataPlot->createMagPlot()," Mag  ");

    layout->setSizeConstraint(QLayout::SetNoConstraint);

    layout->addWidget(tabWidget);

    groupBox->setLayout(layout);
    return groupBox;
}

void MainWindow::connectServerClicked()
{
    emit connectServer(hostLineEdit->text(),portLineEdit->text());
}

void MainWindow::connectionStatusChanged(const bool &connectionState)
{
    if(connectionState){
        connectionStatusLabel->setStyleSheet("background-color:green; border-width:1px; border-radius: 12px;");
    }
    if(!connectionState){
        connectionStatusLabel->setStyleSheet("background-color:red; border-width:1px; border-radius: 12px;");
    }
    emit enablePlotting(connectionState);
}

void MainWindow::updateSensorData(const QVector3D &accData, const QVector3D &gyroData, const QVector3D &magData)
{
    accLableX->setText(QString::number(accData.x()));
    accLableY->setText(QString::number(accData.y()));
    accLableZ->setText(QString::number(accData.z()));

    gyrLableX->setText(QString::number(gyroData.x()));
    gyrLableY->setText(QString::number(gyroData.y()));
    gyrLableZ->setText(QString::number(gyroData.z()));

    magLableX->setText(QString::number(magData.x()));
    magLableY->setText(QString::number(magData.y()));
    magLableZ->setText(QString::number(magData.z()));

    m_dataPlot->updateSensorData(accData,gyroData,magData);
}

void MainWindow::updateAngleData(const float &roll, const float &pitch, const float &yaw)
{
    rollLabel->setText(QString::number(roll));
    pitchLabel->setText(QString::number(pitch));
    yawLabel->setText(QString::number(yaw));

    m_visualization->updateAngles(roll+180,pitch+180,yaw+180);
    m_dataPlot->updateAngleData(QVector3D(roll,pitch,yaw));

}
