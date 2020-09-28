#pragma once

#include <iostream>
#include <vector>
#include "Utils/Transducer.h"
#include "Utils/ControllerDevice.h"
#include <QSerialPort>

class ArduinoMega : ControllerDevice
{
    static std::vector<int> PORT_MAPPING;
public:
    virtual void sendData(const std::vector<Transducer>&,  QSerialPort *);
};
