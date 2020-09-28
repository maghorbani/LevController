#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "Utils/Transducer.h"

enum StructType{
    oneSide,
    twoSide
};

class phaseCalculator
{
    static float soundSpeed;
public:
    phaseCalculator();

    static void focus(std::vector<Transducer> &, Transform target);
    static void addTwinSignature(std::vector<Transducer> &, float angle = M_PI_2);
    static std::tuple<Transform, Transform, Transform> findBoundaries(std::vector<Transducer> &);
    static StructType detectStructType(std::vector<Transducer> &);
};
