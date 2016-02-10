#pragma once
#include "initialcondition.h"
//#include <tgmath.h>
#include <cmath>
#include "../atom.h"
#include "../random.h"

class RandomSpherical : public InitialCondition {

public:
    RandomSpherical(int, real);
    void setupInitialCondition();
    std::string getName() { return "Random spherical"; }
private:
    real m_R0;
};

