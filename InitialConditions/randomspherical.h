#pragma once
#include "initialcondition.h"
#include <cmath>
#include "../atom.h"
#include "../random.h"

class RandomSpherical : public InitialCondition {

public:
    RandomSpherical(int, double);
    void setupInitialCondition();
    std::string getName() { return "Random spherical"; }
private:
    double m_R0;
};

