#include "Utils/ArduinoMega.h"
#include <QByteArray>
#include <spdlog/spdlog.h>

void ArduinoMega::sendData(const std::vector<Transducer> & transducers,  QSerialPort * serial)
{

    int nDivs{10};
    int nPorts{10};

    int bytesNum{nDivs * nPorts};

    std::vector<int8_t> data(static_cast<size_t>(bytesNum),0);
    for(Transducer t:transducers){
        int n{t.getDriverPinNumber()};

        int hardwarePin{PORT_MAPPING.at(static_cast<size_t>(n))};

        int targetByte{hardwarePin / 8};

        int8_t value{static_cast<int8_t>((1 << (hardwarePin % 8)) & 0xFF)};

        int phase{Transducer::calcDiscPhase(t.getPhase(), nDivs)};

        int ampDivs{static_cast<int>(round(t.getAmplitude() * static_cast<float>(nDivs) / 2.0f))};

        for (int i{}; i < ampDivs; i++) {
            int d = (i + phase) % nDivs;
            data[static_cast<size_t>(targetByte + d * nDivs)] |= value;
        }
    }
    QByteArray d;
    for(int i{}; i < bytesNum; i++){
        d.push_back(static_cast<char>((data[static_cast<size_t>(i)] & 0xF0)|1));
        d.push_back(static_cast<char>(((data[static_cast<size_t>(i)] << 4) & 0xF0)|1));
    }

    d.push_back(static_cast<char>(0x00));
    serial->write(d,d.size());
    serial->flush();
}


std::vector<int> ArduinoMega::PORT_MAPPING = {51, 52, 53, 54, 28, 29, 30, 31, 47, 46, 45, 44, 43, 42, 41, 40, 56, 57, 58, 59, 48, 49, 72, 69, 39, 38, 37, 36, 35, 34, 33, 32, 21, 23, 65, 63, 9, 11, 13, 15, 20, 22, 64, 66, 8, 10, 12, 14, 24, 25, 26, 27, 16, 17, 18, 19, 7, 6, 5, 4, 3, 2, 1, 0};
