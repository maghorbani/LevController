#include "Utils/Transducer.h"

int Transducer::getDriverPinNumber() const
{
    return driverPinNumber;
}

void Transducer::setDriverPinNumber(int value)
{
    driverPinNumber = value;
}

int Transducer::calcDiscPhase(float phase, int divs)
{
    int xPhase{static_cast<int>(round(phase*divs/2))};
    xPhase = xPhase%divs;

    while (xPhase < 0) {
        xPhase += divs;
    }

    return xPhase;
}

float Transducer::getFrequency() const
{
    return frequency;
}

void Transducer::setFrequency(float value)
{
    frequency = value;
}

float Transducer::getAmplitude() const
{
    return amplitude;
}

void Transducer::setAmplitude(float value)
{
    amplitude = value;
}

float Transducer::getPhase() const
{
    return phase;
}

void Transducer::setPhase(float value)
{
    phase = value;
}

void Transducer::addPhase(float val)
{
    phase += val;
}

Transducer::Transducer()
{

}

Transducer::Transducer(Transform trans)
{
    m_transform.x = trans.x;
    m_transform.y = trans.y;
    m_transform.z = trans.z;
}

Transducer::Transducer(float x, float y, float z)
{
    m_transform.x = x;
    m_transform.y = y;
    m_transform.z = z;
}

Transducer::Transducer(double x, double y, double z){
    m_transform.x = static_cast<float>(x);
    m_transform.y = static_cast<float>(y);
    m_transform.z = static_cast<float>(z);
}

Transducer::Transducer(float x, float y, float z, int dpn)
{
    m_transform.x = x;
    m_transform.y = y;
    m_transform.z = z;
    driverPinNumber = dpn;
}

Transducer::Transducer(double x, double y, double z, int dpn){
    m_transform.x = static_cast<float>(x);
    m_transform.y = static_cast<float>(y);
    m_transform.z = static_cast<float>(z);
    driverPinNumber = dpn;
}

Transform Transducer::transform() const
{
    return m_transform;
}

void Transducer::setTransform(const Transform &trans)
{
    m_transform.x = trans.x;
    m_transform.y = trans.y;
    m_transform.z = trans.z;
}
