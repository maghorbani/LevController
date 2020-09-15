#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <spdlog/spdlog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Levitaion Controller - BscProject - ee@aut - 9423079");
    on_pushButton_reset_clicked();
    moveDiff = ui->doubleSpinBox->value();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_reset_clicked()
{
    ui->comboBox_ports->clear();
    QList<QSerialPortInfo> UsbPorts = QSerialPortInfo::availablePorts();
    for(auto s:UsbPorts){
        ui->comboBox_ports->addItem(s.portName());
    }
}

void MainWindow::on_pushButton_use_clicked()
{
    portName = ui->comboBox_ports->currentText();
    serial.close();
    serial.setPortName(portName);

    if (!serial.open(QIODevice::ReadWrite)) {
        spdlog::error("port: {} error openning serial comunication", portName.toStdString());
        return;
    }

    serial.setBaudRate (QSerialPort::Baud115200);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity (QSerialPort::NoParity);
    serial.setStopBits (QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    spdlog::info("port: {} successfully configured", portName.toStdString());
//    QObject::connect(&serial,SIGNAL(readyRead()), this, SLOT(readSerial()));
}

void MainWindow::on_pushButton_setMoveDiff_clicked()
{
    moveDiff = ui->doubleSpinBox->value();
}
