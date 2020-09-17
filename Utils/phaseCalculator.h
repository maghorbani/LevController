#ifndef PHASECALCULATOR_H
#define PHASECALCULATOR_H

#include <iostream>
#include <vector>
#include <cmath>

#include "Utils/Transducer.h"

class phaseCalculator
{
    static float soundSpeed;
public:
    phaseCalculator();

    static void focus(std::vector<Transducer> &, Transform target);
    static void addTwinSignature(std::vector<Transducer> &, float angle = M_PI_2);
    static std::tuple<Transform, Transform, Transform> findBoundaries(std::vector<Transducer> &);
};

#endif // PHASECALCULATOR_H
