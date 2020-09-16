#ifndef ARDUINOMEGA_H
#define ARDUINOMEGA_H

#include <iostream>
#include <vector>
#include "Transducer.h"
#include <QSerialPort>

class ArduinoMega
{
    static std::vector<int> PORT_MAPPING;
    static std::vector<int> PHASE_COMPENSATION;
    public:
    ArduinoMega();

    static void sendData(const std::vector<Transducer>&,  QSerialPort *);
    static int iclamp(int input, int min, int max);
};

#endif // ARDUINOMEGA_H
