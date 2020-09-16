#include "ArduinoMega.h"
#include <QByteArray>
ArduinoMega::ArduinoMega()
{

}

void ArduinoMega::sendData(const std::vector<Transducer> & transducers,  QSerialPort * serial)
{

    int signalsNum{64};
    int nDivs{10};
    int nPorts{10};

    int bytesNum{nDivs * nPorts};

    std::vector<uint8_t> data(bytesNum,0);
    for(Transducer t:transducers){
        int n{t.getDriverPinNumber()};

        int hardwarePin{PORT_MAPPING.at(static_cast<size_t>(n))};
        int phaseCompensation{PHASE_COMPENSATION.at(static_cast<size_t>(n))};

        int targetByte{hardwarePin / 8};

        uint8_t value{static_cast<uint8_t>((1 << (hardwarePin % 8)) & 0xFF)};

        int phase{Transducer::calcDiscPhase(t.phase, nDivs)};

        int ampDivs{iclamp(static_cast<int>(round(t.amplitude * static_cast<double>(nDivs) / 2.0)), 0, nDivs)};

        for (int i{}; i < ampDivs; i++) {
            int d = (i + phase + phaseCompensation) % nDivs;
            data[targetByte + d * nDivs] |= value;
        }
    }
    for(int i{}; i < bytesNum; i++){
        QByteArray d;
        d.push_back(static_cast<char>((data[i] & 0xF0)|1));
        d.push_back(static_cast<char>(((data[i] << 4) & 0xF0)|1));
        serial->write(d,2);
    }
}

int ArduinoMega::iclamp(int input, int min, int max) {
    return (input < min) ? min : (input > max) ? max : input;
}


std::vector<int> ArduinoMega::PORT_MAPPING = {51, 52, 53, 54, 28, 29, 30, 31, 47, 46, 45, 44, 43, 42, 41, 40, 56, 57, 58, 59, 48, 49, 72, 69, 39, 38, 37, 36, 35, 34, 33, 32, 21, 23, 65, 63, 9, 11, 13, 15, 20, 22, 64, 66, 8, 10, 12, 14, 24, 25, 26, 27, 16, 17, 18, 19, 7, 6, 5, 4, 3, 2, 1, 0};
std::vector<int> ArduinoMega::PHASE_COMPENSATION = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
