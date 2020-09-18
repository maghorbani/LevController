#pragma once
#include <iostream>
#include <cmath>
#include <spdlog/spdlog.h>

struct Transform{
    Transform() = default;
    Transform(float _x, float _y, float _z): x(_x),y(_y),z(_z){}
    Transform(float _n): x(_n),y(_n),z(_n){}
    float x, y, z;
    float distance(Transform other){
        return static_cast<float>(std::sqrt(std::pow(x-other.x,2)+std::pow(y-other.y,2)+std::pow(z-other.z,2)));
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
    Transform operator-(Transform other){
        other.x = x - other.x;
        other.y = y - other.y;
        other.z = z - other.z;
        return other;
    }
    float angleXY(){
        return atan2(y,x);
    }
    float angleXZ(){
        return atan2(z,x);
    }
    void divTo(Transform other){
        if(other.x != 0.0f)
            x /= other.x;
        if(other.y != 0.0f)
            y /= other.y;
        if(other.z != 0.0f)
            z /= other.z;
    }
    void divTo(float num){
        x/=num;
        y/=num;
        z/=num;
    }
    void setMin(Transform  other){
        x = std::min(x, other.x);
        y = std::min(y, other.y);
        z = std::min(z, other.z);
    }
    void setMax(Transform  other){
        x = std::max(x, other.x);
        y = std::max(y, other.y);
        z = std::max(z, other.z);
    }
    static Transform min(Transform & first, Transform & second){
        Transform mini{std::min(first.x, second.x),
                      std::min(first.y, second.y),
                      std::min(first.z, second.z)};
        return mini;
    }
    static Transform max(Transform & first, Transform & second){
        Transform maxi{std::max(first.x, second.x),
                      std::max(first.y, second.y),
                      std::max(first.z, second.z)};
        return maxi;
    }
};
