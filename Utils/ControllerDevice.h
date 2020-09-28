#pragma once

#include <iostream>
#include <vector>
#include "Utils/Transducer.h"
#include <QSerialPort>

class ControllerDevice{
public:
    virtual void sendData(const std::vector<Transducer>&,  QSerialPort *) = 0;
};
