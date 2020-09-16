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
};

