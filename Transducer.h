#pragma once
#include <QString>
#include <cmath>

struct Transform{
    Transform() = default;
    Transform(double _x, double _y, double _z): x(_x),y(_y),z(_z){}
    double x, y, z;
    double distance(Transform other){
        return std::sqrt(std::pow(x-other.x,2)+std::pow(y-other.y,2)+std::pow(z-other.z,2));
    }
    Transform operator*(double num){
        Transform other(*this);
        other.x *= num;
        other.y *= num;
        other.z *= num;
        return other;
    }
    Transform operator+(Transform other){
        other.x += x;
        other.y += y;
        other.z += z;
        return other;
    }
//        float phi, rho;
};

class Transducer
{

    int orderNumber;
    int driverPinNumber; //in the driver board
    Transform m_transform;

public:
    Transducer();
    Transducer(Transform);
    Transducer(double, double, double);
    Transducer(double, double, double, int);

    double frequency = 40e3f;        // Hz
    double apperture = 0.009f;     // apperture (diameter) for directivity calculation
    double power = 2.53f;           // Transducer power (from microphone measurments).

    QString name;
    double amplitude=1; //from 0 to 1
    double phase; //in radians but divided by PI. That is, a phase of 2 means 2PI radians
    double phaseCorrection; //the deviation that this current transducer has in phase due to manufacturing, long wires or polarity.

    int type = 0; //0=circle, 1=square... Unimplemented
    Transform transform() const;
    void setTransform(const Transform &transform);
    int getDriverPinNumber() const;
    void setDriverPinNumber(int value);

    static int calcDiscPhase(double phase, int divs);
};

