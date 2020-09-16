#include "Utils/phaseCalculator.h"
#include <spdlog/spdlog.h>

float phaseCalculator::soundSpeed = 346.0f;

phaseCalculator::phaseCalculator()
{

}

void phaseCalculator::focus(std::vector<Transducer> & transducers, Transform target)
{
    for(Transducer &t:transducers){
        float distance{t.transform().distance(target)};
        float waveLength{soundSpeed/t.frequency};
        float div{distance/waveLength};
        float decPart{div - floor(div)};
        t.phase = (1.0f - decPart) * 2.0f;
    }
}
