#include "Utils/phaseCalculator.h"
#include <spdlog/spdlog.h>
#include <limits>

float phaseCalculator::soundSpeed = 346.0f;

phaseCalculator::phaseCalculator()
{

}

void phaseCalculator::focus(std::vector<Transducer> & transducers, Transform target)
{
    for(Transducer &t:transducers){
        float distance{t.transform().distance(target)};
        float waveLength{soundSpeed/t.getFrequency()};
        float div{distance/waveLength};
        float decPart{div - floor(div)};
        t.setPhase((1.0f - decPart) * 2.0f);
    }
}

void phaseCalculator::addTwinSignature(std::vector<Transducer> & transducers, float angle)
{
    auto [min, max, center] = findBoundaries(transducers);
    Transform size{max-min};
    for(Transducer &t: transducers){
        Transform npos{t.transform() - center};
        npos.divTo(size);

        float value{(npos.angleXZ() + angle)/static_cast<float>(M_PI)};
        value = fmod(value, 2.0f);

        if(!(value >= 0.0f && value <= 1.0f))
            t.addPhase(1.0f);
    }
}

std::tuple<Transform, Transform, Transform> phaseCalculator::findBoundaries(std::vector<Transducer> & transducers)
{
    float minFloat{std::numeric_limits<float>::max()};
    float maxFloat{-std::numeric_limits<float>::min()};
    Transform min{minFloat};
    Transform max{maxFloat};

    for( Transducer t: transducers){
        min.setMin(t.transform());
        max.setMax(t.transform());
    }

    Transform center{max + min};
    center.divTo(2);

    return {min, max, center};
}

StructType phaseCalculator::detectStructType(std::vector<Transducer> &transducers)
{
    float y{transducers.at(0).transform().y};
    for(Transducer &t: transducers){
        if(std::abs(static_cast<float>(t.transform().y - y)) > 0.001f){
            return StructType::twoSide;
        }
    }
    return StructType::oneSide;
}
