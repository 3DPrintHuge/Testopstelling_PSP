#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <math.h>
#include <fstream>
#include <iostream>

#include <QMainWindow>
#include <QString>
#include <QDebug>

#include <QLabel>

#include <QTimer>
#include <QDateTime>
#include <QTimerEvent>

#include <QTextStream>
#include <QFile>
#include <QList>
#include <QStringList>
#include <QDir>

#include <QFileDialog>



extern "C"{
#include "ljackuw.h"
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool initialized=false;
    bool endSwitch=false;

    //public parameters for controlling IO on CB25 extrension module
    long int ID=0;
    long int trisD=0;
    long int trisIO=0;
    long int stateD=0;
    long int stateIO=0;
    long int outputD=0;

    //public parameters for platform movement
    long int timeB;
    long int timeC;
    float platformPPS;
    float platformPeriod;
    float platRPM;
    int asPlatPos=0;    //assumed platform position
    bool platDir= true;
    bool platEnable = true;

    //public parameters for vertical movement
    long int timeB1;
    long int timeC1;
    float verticalPPS;
    float verticalPeriod;
    int asVertPos=0;
    bool vertDir= true;
    bool vertEnable= true;

    QString logDir = "C:/Qt/logs/";



    // public functions
    float rpmtopps(float rpm, int spr);
    float mmstopps(float mmr, int spr);


signals:

    //timer timeout signals
    void atimeout();
    void globalTimeout();
    void platformTimeout();
    void verticalTimeout();


private slots:

    void movePlatform();
    void incrementPlatform();
    void directionPlatform(bool dir);

    void moveVertical();
    void incrementVertical();
    void directionVertical(bool dir);

    void writeDataTxt(QString fileName, QString writeData);

    void readButton();

    //standard slots
    void on_getButton_clicked();
    void on_ledBox_toggled(bool checked);
    void on_stopSpeedButton_clicked();
    void on_controlTab_currentChanged(int index);
    void on_logDirButton_clicked();

    void on_incButton_clicked();

private:
    Ui::MainWindow *ui;

    QBasicTimer timer;
    QBasicTimer globalTimer;
    QBasicTimer platformTimer;
    QBasicTimer verticalTimer;

    QDateTime dateTime;

    QLabel buttonLabel;

protected:
    void timerEvent(QTimerEvent *event) override ;


};

#endif // MAINWINDOW_H
