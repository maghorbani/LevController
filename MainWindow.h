#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_reset_clicked();

    void on_pushButton_use_clicked();

    void on_pushButton_setMoveDiff_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort serial;
    QString portName = "cu.wchusbserial1410";
    double moveDiff;
};

#endif // MAINWINDOW_H
