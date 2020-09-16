#include "Transducer.h"

int Transducer::getDriverPinNumber() const
{
    return driverPinNumber;
}

void Transducer::setDriverPinNumber(int value)
{
    driverPinNumber = value;
}

int Transducer::calcDiscPhase(double phase, int divs)
{
    int xPhase{static_cast<int>(round(phase*divs/2))};
    xPhase = xPhase%divs;

    while (xPhase < 0) {
        xPhase += divs;
    }

    return xPhase;
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

Transducer::Transducer(double x, double y, double z)
{
    m_transform.x = x;
    m_transform.y = y;
    m_transform.z = z;
}

Transducer::Transducer(double x, double y, double z, int dpn)
{
    m_transform.x = x;
    m_transform.y = y;
    m_transform.z = z;
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
