#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <spdlog/spdlog.h>

#include "structureReader.h"
#include "phaseCalculator.h"
#include "ArduinoMega.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Levitaion Controller - BscProject - ee@aut - 9423079");
    on_pushButton_reset_clicked();
    moveDiff = ui->doubleSpinBox->value()/1000.0;

    connect(ui->pushButton_Up,      &QPushButton::clicked, this, [this](){this->move( 0, 1, 0);});
    connect(ui->pushButton_Down,    &QPushButton::clicked, this, [this](){this->move( 0,-1, 0);});
    connect(ui->pushButton_Right,   &QPushButton::clicked, this, [this](){this->move( 1, 0, 0);});
    connect(ui->pushButton_Left,    &QPushButton::clicked, this, [this](){this->move(-1, 0, 0);});
    connect(ui->pushButton_Front,   &QPushButton::clicked, this, [this](){this->move( 0, 0, 1);});
    connect(ui->pushButton_Back,    &QPushButton::clicked, this, [this](){this->move( 0, 0,-1);});
}

void MainWindow::move(float x, float y, float z)
{
    Transform diff(x,y,z);
    diff = diff*moveDiff;
    levPoint = levPoint + diff;

    phaseCalculator::focus(m_transducers, levPoint);
    ArduinoMega::sendData(m_transducers, &serial);
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
}

void MainWindow::on_pushButton_setMoveDiff_clicked()
{
    moveDiff = static_cast<float>(ui->doubleSpinBox->value())/1000.0f;
}

void MainWindow::on_actionLoad_Struct_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "select struct json file","", "*.json");
    QJsonObject obj = structureReader::readStruct(fileName);

    QJsonArray transArr = obj["transducers"].toArray();
    m_transducers.clear();

    for(QJsonValue t:transArr){
        m_transducers.push_back({t["x"].toDouble(), t["y"].toDouble(), t["z"].toDouble(),t["pin"].toInt()});
    }
}

void MainWindow::on_pushButton_calcAndSend_clicked()
{
    QStringList pos = ui->lineEdit_position->text().split(",");
    if(pos.size() != 3){
        spdlog::error("please Enter a position in format x, y, z");
        return;
    }
    if(m_transducers.size() == 0){
        spdlog::error("please load a struct first!");
        return;
    }
    levPoint.x = pos[0].toFloat();
    levPoint.y = pos[1].toFloat();
    levPoint.z = pos[2].toFloat();

    phaseCalculator::focus(m_transducers, levPoint);

    ArduinoMega::sendData(m_transducers, &serial);
}
