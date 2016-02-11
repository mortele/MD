#pragma once
#include <cmath>
#include <vector>
#include "initialcondition.h"
#include "../atom.h"
#include "../vec.h"
#include "../random.h"

class Uniform : public InitialCondition {
public:
    Uniform(int n, std::vector<real> boxSize, real temperature);
    void setupInitialCondition();
    std::string getName() { return "Uniform random"; }

private:
    std::vector<real> m_boxSize;
    real              m_temperature;
};

