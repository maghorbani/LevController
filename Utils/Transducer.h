#pragma once
#include <QString>
#include <cmath>
#include "Utils/Transform.h"

class Transducer
{
    int driverPinNumber; //in the driver board
    Transform m_transform;
    float frequency = 40e3f;        // Hz
    float amplitude=1; //from 0 to 1
    float phase; //in radians but divided by PI. That is, a phase of 2 means 2PI radians

public:
    Transducer();
    Transducer(Transform);
    Transducer(float, float, float);
    Transducer(double x, double y, double z);
    Transducer(float, float, float, int);
    Transducer(double x, double y, double z, int dpn);

    Transform transform() const;
    void setTransform(const Transform &transform);
    int getDriverPinNumber() const;
    void setDriverPinNumber(int value);

    static int calcDiscPhase(float phase, int divs);
    float getFrequency() const;
    void setFrequency(float value);
    float getAmplitude() const;
    void setAmplitude(float value);
    float getPhase() const;
    void setPhase(float value);

    void addPhase(float);
};

