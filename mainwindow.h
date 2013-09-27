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
