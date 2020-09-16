#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QSerialPort>

#include <iostream>
#include <vector>

#include "Transducer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void move(double, double, double);
    ~MainWindow();

private slots:
    void on_pushButton_reset_clicked();

    void on_pushButton_use_clicked();

    void on_pushButton_setMoveDiff_clicked();

    void on_actionLoad_Struct_triggered();

    void on_pushButton_calcAndSend_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort serial;
    QString portName = "cu.wchusbserial1410";
    double moveDiff;
    Transform levPoint;
    std::vector<Transducer> m_transducers;
};

#endif // MAINWINDOW_H
