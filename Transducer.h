#pragma once
#include <QString>
#include <cmath>

struct Transform{
    Transform() = default;
    Transform(float _x, float _y, float _z): x(_x),y(_y),z(_z){}
    float x, y, z;
    float distance(Transform other){
        return std::sqrt(std::pow(x-other.x,2)+std::pow(y-other.y,2)+std::pow(z-other.z,2));
    }
    Transform operator*(float num){
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
    Transducer(float, float, float);
    Transducer(double x, double y, double z);
    Transducer(float, float, float, int);
    Transducer(double x, double y, double z, int dpn);

    float frequency = 40e3f;        // Hz
    float apperture = 0.009f;     // apperture (diameter) for directivity calculation
    float power = 2.53f;           // Transducer power (from microphone measurments).

    QString name;
    float amplitude=1; //from 0 to 1
    float phase; //in radians but divided by PI. That is, a phase of 2 means 2PI radians
    float phaseCorrection; //the deviation that this current transducer has in phase due to manufacturing, long wires or polarity.

    int type = 0; //0=circle, 1=square... Unimplemented
    Transform transform() const;
    void setTransform(const Transform &transform);
    int getDriverPinNumber() const;
    void setDriverPinNumber(int value);

    static int calcDiscPhase(float phase, int divs);
};

