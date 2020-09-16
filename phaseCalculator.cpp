#include "phaseCalculator.h"


double phaseCalculator::soundSpeed = 346.0;

phaseCalculator::phaseCalculator()
{

}

void phaseCalculator::focus(std::vector<Transducer> & transducers, Transform target)
{
    for(Transducer &t:transducers){
        double distance{t.transform().distance(target)};
        double waveLength{soundSpeed/t.frequency};
        double div{distance/waveLength};
        double decPart{div - floor(div)};
        t.phase = (1.0 - decPart) * 2.0;
    }
}
