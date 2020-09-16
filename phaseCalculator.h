#ifndef PHASECALCULATOR_H
#define PHASECALCULATOR_H

#include <iostream>
#include <vector>

#include "Transducer.h"

class phaseCalculator
{
    static float soundSpeed;
public:
    phaseCalculator();

    static void focus(std::vector<Transducer> &, Transform target);
};

#endif // PHASECALCULATOR_H
